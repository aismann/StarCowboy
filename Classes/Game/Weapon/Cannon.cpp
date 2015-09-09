//
//  Cannon.cpp
//  StarCowboy
//
//  Created by match5 on 15/2/26.
//
//

#include "Cannon.h"
#include "MathUtils.h"
#include "ComBullet.h"
#include "ComLifeTimeLimit.h"
#include "GameWorld.h"
#include "GameObjectManager.h"

bool Cannon::fire(const cc::Vec2& from,
                  const cc::Vec2& direction,
                  const cc::Vec2& shipVelocity)
{
    if (_coolDownTimer.isFinish()) {
        float errorAngle = math::angle2Radian(cc::random<float>(-_errorAngle, _errorAngle));
        cc::Vec2 shootDirection = direction.rotateByAngle(cc::Vec2::ZERO, errorAngle);
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
        
        _coolDownTimer.reset();
        return true;
    }
    return false;
}

void Cannon::update(float dt)
{
    _coolDownTimer.increase(dt);
}
