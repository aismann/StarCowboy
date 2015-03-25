//
//  ComMissile.cpp
//  StarCowboy
//
//  Created by match5 on 15/2/28.
//
//

#include "ComMissile.h"
#include "ComEntity.h"
#include "ComPhysicsEntity.h"
#include "GameObjectManager.h"
#include "ComLifeTimeLimit.h"
#include "ComParticleEmiter.h"

void ComMissile::onLoad() {
}

void ComMissile::onUnload() {
    getOwner()->getWorld()->getGameForeground()->removeChild(_ndoe);
}

void ComMissile::start() {
    
    if (!_ndoe->getParent()) {
        getOwner()->getWorld()->getGameForeground()->addChild(_ndoe);
    }
    
    _ndoe->setPosition(_location * constants::Ptm);
}

void ComMissile::update(float dt) {
    
    //find target
    GameObject *target = _target.get();
    if (target && target->isActive()) {
        //do nothing
        cc::Vec2 left = _direction.rotateByAngle({0, 0}, -_searchRadian * 0.5);
        cc::Vec2 right = _direction.rotateByAngle({0, 0}, _searchRadian * 0.5);
        cc::Vec2 dis = _targetEntity->getLocation() - _location;
        
        if (left.cross(dis) > 0 && right.cross(dis) < 0) {
            
        } else {
            //target lost
            _target.reset();
            _targetEntity = nullptr;
        }
    } else if (_searchTargetTimer.increase(dt)) {
        GameObjectManager::getInstance()->enumerateObject(_targetMask, [this](GameObject* obj){
            if (obj->isActive()) {
                ComPhysicsEntity *t = obj->getComponent<ComPhysicsEntity>("physics_entity");
                if (!t) {
                    return;
                }
                
                cc::Vec2 left = _direction.rotateByAngle({0, 0}, -_searchRadian * 0.5);
                cc::Vec2 right = _direction.rotateByAngle({0, 0}, _searchRadian * 0.5);
                cc::Vec2 dis = t->getLocation() - _location;
                
                if (left.cross(dis) > 0 && right.cross(dis) < 0) {
                    if (_target) {
                        if (dis.lengthSquared() < _targetEntity->getLocation().distanceSquared(_location)) {
                            _target = *obj;
                            _targetEntity = t;
                        }
                    } else {
                        _target = *obj;
                        _targetEntity = t;
                    }
                }
            }
        });
        _searchTargetTimer.reset();
    }
    
    //track
    if (_acceleratFinished && _target) {
        
        float aim = (_targetEntity->getLocation() - _location).getAngle();
        float curr = _direction.getAngle();
        float dif = aim - curr;
        if (dif > constants::Pi) {
            dif = - (2 * constants::Pi - dif);
        } else if (dif < -constants::Pi) {
            dif += 2 * constants::Pi;
        }

        float step = math::angle2Radian(_angularSpeed) * dt;
        cc::Vec2 dir = _direction;
        if (dif > step) {
            dir.rotate({0, 0}, step);
            setDirection(dir);
        } else if (dif < -step) {
            dir.rotate({0, 0}, -step);
            setDirection(dir);
        } else {
            setDirection(cc::Vec2::forAngle(aim));
        }
    }
    _ndoe->setRotation(math::radian2Angle(-_direction.getAngle()));
    
    //movement
    _direction.normalize();
    if (!_acceleratFinished) {
        if (_velocity.lengthSquared() < _maxSpeed * _maxSpeed) {
            float acc;
            acc = _maxSpeed / _accelerationTime;
            _velocity += _direction * acc * dt;
        } else {
            _acceleratFinished = true;
        }
    } else {
        _velocity = _direction * _maxSpeed;
    }
    setLocation(_location + _velocity * dt);
    _ndoe->setPosition(_location * constants::Ptm);
    
    //hit test
    GameObjectManager::getInstance()->enumerateObject(_targetMask | _hitTestMask, [this](GameObject* obj){
        if (obj->isActive()) {
            ComPhysicsEntity *t = obj->getComponent<ComPhysicsEntity>("physics_entity");
            if (!t) {
                return;
            }
            cc::Vec2 d = _location - t->getLocation();
            if (d.lengthSquared() <= t->getRadius() * t->getRadius()) {
                getOwner()->kill();
                obj->sendMessage(GAME_MSG::TAKE_DAMEGE, _damage);
            }
        }
    });
}

void ComMissile::onOwnerDead() {
    GameObject* explode = GameObjectManager::getInstance()->createObject().get();
    explode->addComponent(ComLifeTimeLimit::create(0.2));
    cc::ParticleSystem* emiter = cc::ParticleSystemQuad::create("particles/bullet_hit.plist");
    emiter->setPosition(_location * constants::Ptm);
    explode->addComponent(ComParticleEmiter::create(emiter));
    explode->awake();
}

ComMissile* ComMissile::setDirection(const cc::Vec2& d) {
    _direction = d;
    return this;
}
