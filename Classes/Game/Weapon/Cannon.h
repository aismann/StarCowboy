//
//  Cannon.h
//  StarCowboy
//
//  Created by match5 on 15/2/26.
//
//

#ifndef __Cannon_h__
#define __Cannon_h__

#include "Weapon.h"

class Cannon : public Weapon
{
    
public:
    
    static Cannon* create() {
        Cannon* weapon = new Cannon;
        weapon->autorelease();
        return weapon;
    }
    
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity,
                      const TagSet::TagBit& targetTag) override;
    
    virtual void update(float dt) override;
    
    Cannon* setDamage(int damage) {
        _damage = damage;
        return this;
    }
    
    Cannon* setBulletSpeed(float s) {
        _bulletSpeed = s;
        return this;
    }
    
    Cannon* setCoolDown(float cd) {
        _coolDown = cd;
        return this;
    }
    
    Cannon* setErrorAngle(float angle) {
        _errorAngle = angle;
        return this;
    }
    
protected:
    
    int     _damage = 0;
    float   _bulletSpeed = 200;
    
    float   _coolDown = 0.5;
    float   _coolDownTimer = 0;
    
    float   _errorAngle = 0;
};

#endif
