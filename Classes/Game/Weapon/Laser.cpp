//
//  Laser.cpp
//  StarCowboy
//
//  Created by match5 on 15/2/27.
//
//

#include "Laser.h"
#include "Constants.h"
#include "GameWorld.h"
#include "MathUtils.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ComPhysicsEntity.h"
#include "ComParticleEmiter.h"
#include "ComLifeTimeLimit.h"

bool Laser::fire(const cc::Vec2& from,
                 const cc::Vec2& direction,
                 const cc::Vec2& shipVelocity)
{
    if (!_isFire) {
        if (_energy > _maxEnergy / _energySpendTime) {
            _isFire = true;
            if (_light) {
                _light->setAnchorPoint({0, 0.5});
                _light->setScaleX(100);
                _light->setPosition(from * constants::Ptm);
                _light->setRotation(math::radian2Angle(-direction.getAngle()));
                GameWorld::getInstance()->getGameForeground()->addChild(_light);
            }
        } else {
            return false;
        }
    }
    _from = from;
    _direction = direction;
    return true;
}

void Laser::stopFire() {
    _isFire = false;
    _light->removeFromParent();
}

void Laser::update(float dt)
{
    if (_isFire) {
        _energy -= _maxEnergy / _energySpendTime * dt;
        if (_energy < 0) {
            _energy = 0;
            stopFire();
        } else {
            cc::Vec2 td;
            ComPhysicsEntity *t = nullptr;
            GameObject* explode = nullptr;
            cc::ParticleSystem* emiter = nullptr;
            GameWorld* world = GameWorld::getInstance();
            world->getObjectManager()->enumerateObject(_targetMask | _hitTestMask, [&](GameObject *obj) {
                if (obj->isActive()) {
                    t = obj->getComponent<ComPhysicsEntity>("entity");
                    if (!t) {
                        return ;
                    }
                    td = t->getLocation() - _from;
                    if (td.distanceSquared(td.project(_direction)) < t->getRadius() * t->getRadius()
                        && td.getPerp().cross(_direction) < 0) {
                        t->getOwner()->sendMessage(GAME_MSG::TAKE_DAMEGE, _dps * dt);
                        explode = world->getObjectManager()->createObject().get();
                        explode->addComponent(ComLifeTimeLimit::create(0.2));
                        emiter = cc::ParticleSystemQuad::create("particles/bullet_hit.plist");
                        emiter->setPosition(t->getLocation() * constants::Ptm);
                        explode->addComponent(ComParticleEmiter::create(emiter));
                        explode->awake();
                    }
                }
            });
            
            _light->setPosition(_from * constants::Ptm);
            _light->setRotation(math::radian2Angle(-_direction.getAngle()));
        }
    } else {
        if (_energy < _maxEnergy) {
            _energy += _maxEnergy / _energyRechargeTime * dt;
        }
        if (_energy > _maxEnergy) {
            _energy = _maxEnergy;
        }
    }
}