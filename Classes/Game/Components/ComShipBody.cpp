
#include "ComShipBody.h"
#include "ComPhysicsEntity.h"
#include "ComEngine.h"
#include "MathUtils.h"
#include "GameObjectManager.h"
#include "ComLifeTimeLimit.h"
#include "ComParticleEmiter.h"

const static float kAngularSpeed = 360.f;

void ComShipBody::onLoad() {
}

void ComShipBody::onUnload() {
    getOwner()->getWorld()->getGameForeground()->removeChild(_ndoe);
}

void ComShipBody::start() {
    _entity = getOwner()->getComponent<ComPhysicsEntity>("physics_entity");
    _engine = getOwner()->getComponent<ComEngine>("engine");
    
    if (!_ndoe->getParent()) {
        getOwner()->getWorld()->getGameForeground()->addChild(_ndoe);
    }
    
    if (_entity) {
        _ndoe->setPosition(_entity->getLocation() * constants::Ptm);
    }
}

void ComShipBody::update(float dt) {

    if (_entity) {
        _ndoe->setPosition(_entity->getLocation() * constants::Ptm);
    }
    
    if (_engine) {
        if (_engine->getForce().lengthSquared() > 0.01) {
            float aim = math::radian2Angle(-_engine->getDirection().getAngle());
            float curr = _ndoe->getRotation();
            
            float dis = aim - curr;
            if (dis > 180) {
                dis = -(360 - dis);
            } else if (dis < -180) {
                dis += 360;
            }

            float step = kAngularSpeed * dt;
            if (dis > step) {
                _ndoe->setRotation(curr + step);
            } else if (dis < -step) {
                _ndoe->setRotation(curr - step);
            } else {
                _ndoe->setRotation(aim);
            }
        }
    }
}

void ComShipBody::onOwnerDestroy() {
    GameObject* explode = getWorld()->getObjectManager()->createObject().get();
    explode->addComponent(ComLifeTimeLimit::create(2));
    cc::ParticleSystem* emiter = cc::ParticleSystemQuad::create("particles/exploding_ring.plist");
    emiter->setPosition(_entity->getLocation() * constants::Ptm);
    explode->addComponent(ComParticleEmiter::create(emiter));
    explode->awake();
}
