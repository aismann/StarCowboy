//
//  MissileLauncher.cpp
//  StarCowboy
//
//  Created by match5 on 15/2/27.
//
//

#include "MissileLauncher.h"
#include "MathUtils.h"
#include "ComMissile.h"
#include "ComLifeTimeLimit.h"
#include "GameWorld.h"
#include "GameObjectManager.h"
#include "ComParticleEmiter.h"

bool MissileLauncher::fire(const cc::Vec2& from,
                           const cc::Vec2& direction,
                           const cc::Vec2& shipVelocity)
{
    if (_coolDownTimer >= _coolDown && _ammoNum > 0) {
        
        GameObject* missile = GameWorld::getInstance()->getObjectManager()->createObject().get();
        missile->setTagBits(TagSet::getBit("missile"));
        missile->addComponent(ComMissile::create(cc::Sprite::create("missile.png"))
                              ->setTargetMask(_targetMask)
                              ->setHitTestMask(_hitTestMask)
                              ->setDamage(_damage)
                              ->setDirection(direction)
                              ->setVelocity((_isLeftLaunche? direction.getPerp().getNormalized() : -direction.getPerp().getNormalized())  * _missileSpeed / 2 + shipVelocity)
                              ->setMaxSpeed(_missileSpeed)
                              ->setSearchAngular(_searchAngular)
                              ->setAngularSpeed(_angularSpeed)
                              ->setLocation(from), "entity");
        missile->addComponent(ComLifeTimeLimit::create(_flyingTime));
        missile->addComponent(ComParticleEmiter::create(cc::ParticleSystemQuad::create("particles/missile_wake.plist")));
        missile->awake();
        
        --_ammoNum;
        _coolDownTimer = 0;
        _isLeftLaunche = !_isLeftLaunche;
        return true;
    }
    return false;
}

void MissileLauncher::update(float dt)
{
    _coolDownTimer += dt;
    
    if (_ammoNum < _maxAmmoNum) {
        _reloadTimer += dt;
        if (_reloadTimer >= _reloadTime) {
            _reloadTimer = 0;
            ++_ammoNum;
        }
    }
}
