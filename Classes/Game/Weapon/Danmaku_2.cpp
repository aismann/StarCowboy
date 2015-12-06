//
//  Danmaku_2.cpp
//  StarCowboy
//
//  Created by match5 on 15/9/9.
//
//

#include "Danmaku_2.h"
#include "MathUtils.h"
#include "ComBullet.h"
#include "ComLifeTimeLimit.h"
#include "GameWorld.h"
#include "GameObjectManager.h"

bool Danmaku_2::fire(const cc::Vec2& from,
                  const cc::Vec2& direction,
                  const cc::Vec2& shipVelocity)
{
    if (_coolDownTimer.isFinish()) {
        if (_shotTimer.isFinish()) {
            if (!_waveNum.isFinish()) {
                float angelOffset = _shotAngle / _bulletNum;
                cc::Vec2 shootDirection = direction.rotateByAngle(cc::Vec2::ZERO, -_shotAngle * 0.5);
                for (int i = 0; i < _bulletNum; ++i) {
                    shootDirection.normalize();
                    
                    GameObject* bullet = GameWorld::getInstance()->getObjectManager()->createObject().get();
                    bullet->setTagBits(Tag::getBit("bullet"));
                    bullet->addComponent(ComBullet::create(CREATE_SPRITE("bullet0.png"))
                                         ->setHitTestMask(_targetMask | _hitTestMask)->setDamage(_damage)
                                         ->setVelocity(shootDirection * _bulletSpeed + shipVelocity)
                                         ->setHeading(shootDirection)
                                         ->setLocation(from));
                    bullet->addComponent(ComLifeTimeLimit::create(_range / _bulletSpeed));
                    bullet->awake();
                    shootDirection = shootDirection.rotateByAngle(cc::Vec2::ZERO, angelOffset);
                }
                _shotTimer.reset();
            }
            if (_waveNum.increase(1)) {
                _coolDownTimer.reset();
                _waveNum.reset();
            }
        }
        return true;
    }
    return false;
}

void Danmaku_2::update(float dt)
{
    _coolDownTimer.increase(dt);
    _shotTimer.increase(dt);
}
