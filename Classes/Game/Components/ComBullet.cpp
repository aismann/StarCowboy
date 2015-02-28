#include "ComBullet.h"
#include "ComEntity.h"
#include "ComPhysicsEntity.h"
#include "MathUtils.h"
#include "GameObjectManager.h"
#include "ComLifeTimeLimit.h"
#include "ComParticleEmiter.h"

void ComBullet::onLoad() {
}

void ComBullet::onUnload() {
    getOwner()->getWorld()->getGameForeground()->removeChild(_ndoe);
}

void ComBullet::start() {
    
    if (!_ndoe->getParent()) {
        getOwner()->getWorld()->getGameForeground()->addChild(_ndoe);
    }
    
    _ndoe->setPosition(_location * constants::Ptm);
}

void ComBullet::update(float dt) {
    
    if (_velocity.lengthSquared() > 0.01) {
        setLocation(_location + _velocity * dt);
    }
    
    _ndoe->setPosition(_location * constants::Ptm);
    
    getWorld()->getObjectManager()->enumerateObject(_hitTestMask, [this](GameObject* obj){
        if (obj->isActive()) {
            ComPhysicsEntity *t = obj->getComponent<ComPhysicsEntity>("physics_entity");
            if (!t) {
                return;
            }
            cc::Vec2 d = _location - t->getLocation();
            if (d.lengthSquared() <= t->getRadius() * t->getRadius()) {
                getOwner()->destroy();
                obj->sendMessage(GAME_MSG::TAKE_DAMEGE, _damage);
            }
        }
    });
}

void ComBullet::onOwnerDestroy() {
    GameObject* explode = getWorld()->getObjectManager()->createObject();
    explode->addComponent(ComLifeTimeLimit::create(0.2));
    cc::ParticleSystem* emiter = cc::ParticleSystemQuad::create("particles/bullet_hit.plist");
    emiter->setPosition(_location * constants::Ptm);
    explode->addComponent(ComParticleEmiter::create(emiter));
    explode->awake();
}

ComBullet* ComBullet::setVelocity(const cc::Vec2& v) {
    _velocity = v;
    _ndoe->setRotation(math::radian2Angle(-_velocity.getAngle()));
    return this;
}