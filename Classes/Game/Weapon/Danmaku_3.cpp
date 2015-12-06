//
//  Danmaku_3.cpp
//  StarCowboy
//
//  Created by match5 on 15/9/9.
//
//

#include "Danmaku_3.h"
#include "MathUtils.h"
#include "ComBullet.h"
#include "ComLifeTimeLimit.h"
#include "GameWorld.h"
#include "GameObjectManager.h"

bool Danmaku_3::fire(const cc::Vec2& from,
                  const cc::Vec2& direction,
                  const cc::Vec2& shipVelocity)
{
    if (_coolDownTimer.isFinish()) {
        if (!_isShooting) {
            _shootDirection = direction;
            _isShooting = true;
        }
        float angelOffset = _shotAngle / _bulletNum.getTotal();
        if (_shotTimer.isFinish()) {
            if (!_bulletNum.isFinish()) {
                _shootDirection.normalize();
                GameObject* bullet = GameWorld::getInstance()->getObjectManager()->createObject().get();
                bullet->setTagBits(Tag::getBit("bullet"));
                bullet->addComponent(ComBullet::create(CREATE_SPRITE("bullet0.png"))
                                     ->setHitTestMask(_targetMask | _hitTestMask)->setDamage(_damage)
                                     ->setVelocity(_shootDirection * _bulletSpeed + shipVelocity)
                                     ->setHeading(_shootDirection)
                                     ->setLocation(from));
                bullet->addComponent(ComLifeTimeLimit::create(_range / _bulletSpeed));
                bullet->awake();
                _shotTimer.reset();
                _shootDirection = _shootDirection.rotateByAngle(cc::Vec2::ZERO, _isReverse ? -angelOffset : angelOffset);
            }
            if (_bulletNum.increase(1)) {
                _coolDownTimer.reset();
                _bulletNum.reset();
            }
        }
        return true;
    }
    _isShooting = false;
    return false;
}

void Danmaku_3::update(float dt)
{
    _coolDownTimer.increase(dt);
    _shotTimer.increase(dt);
}
