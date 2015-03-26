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
        Cannon* weapon = NewEx(Cannon);
        return weapon;
    }
    
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity) override;
    
    virtual void update(float dt) override;
    
    Cannon* setDamage(int d) {
        _damage = d;
        return this;
    }
    
    Cannon* setBulletSpeed(float s) {
        _bulletSpeed = s;
        return this;
    }
    
    Cannon* setRange(float r) {
        _range = r;
        return this;
    }
    
    Cannon* setCoolDown(float cd) {
        _coolDownTimer.reset(cd);
        return this;
    }
    
    Cannon* setErrorAngle(float a) {
        _errorAngle = a;
        return this;
    }
    
protected:
    
    int     _damage = 0;
    float   _bulletSpeed = 200;
    float   _range = 500;
    
    Timer   _coolDownTimer = 0.5;
    
    float   _errorAngle = 0;
};

#endif
