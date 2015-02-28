
#include "ComPhysicsEntity.h"
#include "GameObjectManager.h"
#include "MathUtils.h"

void ComPhysicsEntity::start() {
    _physicsEntityMask = TagSet::getBit("physics_entity");
}

void ComPhysicsEntity::update(float dt) {
    
    if (_isFixed) {
        return;
    }
    
    _force = calculateForce(dt);
    
    _velocity += (_force / _mass) * dt;
    if (_velocity.lengthSquared() > 0.01) {
        setLocation(_location + _velocity * dt);
    }
    
    //Collision Detection
    getWorld()->getObjectManager()->enumerateObject(_physicsEntityMask, [this](GameObject* obj){
        if (_owner && obj != _owner && obj->isActive()) {
            ComPhysicsEntity *he = obj->getComponent<ComPhysicsEntity>("physics_entity");
            ComPhysicsEntity *me = getOwner()->getComponent<ComPhysicsEntity>("physics_entity");
            if (!(he && me)) {
                return;
            }
            cc::Vec2 d = me->getLocation() - he->getLocation();
            float limit = me->getRadius() + he->getRadius();
            float distance = d.length();
            if (distance <= limit) {
                CollisionTargetInfo his = { he->getVelocity(), he->getLocation(), he->getMass()};
                CollisionTargetInfo my = { me->getVelocity(), me->getLocation(), me->getMass()};
				me->getOwner()->sendMessage(GAME_MSG::ON_COLLISION_WITH, 0, &his, he->getOwner());
                obj->sendMessage(GAME_MSG::ON_COLLISION_WITH, 0, &my, me->getOwner());                
                d.normalize();
                if (!me->getIsFixed()) {
                    me->setLocation(me->getLocation() + d * (limit - distance + constants::MinDistance));
                } else if (!he->getIsFixed()) {
                    he->setLocation(he->getLocation() - d * (limit - distance + constants::MinDistance));
                }
            }
        }
    });
}

cc::Vec2 ComPhysicsEntity::calculateForce(float dt) {
    
    cc::Vec2 result = {0, 0};
    
    //Constant Force
    std::vector<ForceTimePair>::iterator newEnd = std::remove_if(_constantForces.begin(), _constantForces.end(), [&result, dt](ForceTimePair &pair){
        if (pair.second <= 0) {
            return true;
        }
        result += pair.first;
        pair.second -= dt;
        return false;
    });
    _constantForces.erase(newEnd, _constantForces.end());
    
    //Sliding Resistance
    //result -= _mass * constants::DefaultGravity * _resistance * _velocity.getNormalized();
    
    //Air Resistance
    result -= _resistance * _radius * _radius * _velocity.lengthSquared() * _velocity.getNormalized();
    
    return result;
}

void ComPhysicsEntity::onMessage(const GameMessage& msg)
{
    if (msg.id == GAME_MSG::ON_COLLISION_WITH) {
        if (_isFixed) {
            return;
        }
        CollisionTargetInfo *target = static_cast<CollisionTargetInfo*>(msg.pParam);
        cc::Vec2 normal = target->location - getLocation();
        normal.normalize();
        cc::Vec2 v1 = getVelocity().project(normal);
        cc::Vec2 v2 = target->velocity.project(normal);
        cc::Vec2 v1_2 = ((_mass - target->mass) * v1 + 2 * target->mass * v2) / (_mass + target->mass);
        v1_2 *= 1 - _collisionResistance;
        _velocity -= v1;
        _velocity += v1_2;
    }
}
