//
//  Danmaku_1.h
//  StarCowboy
//
//  Created by match5 on 15/9/8.
//
//

#ifndef __Danmaku_1_h__
#define __Danmaku_1_h__

#include "Weapon.h"

class Danmaku_1 : public Weapon
{
    
public:
    
    static Danmaku_1* create() {
        Danmaku_1* weapon = New(Danmaku_1);
        return weapon;
    }
    
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity) override;
    
    virtual void update(float dt) override;
    
    Danmaku_1* setDamage(int d) {
        _damage = d;
        return this;
    }
    
    Danmaku_1* setBulletSpeed(float s) {
        _bulletSpeed = s;
        return this;
    }
    
    Danmaku_1* setRange(float r) {
        _range = r;
        return this;
    }
    
    Danmaku_1* setShotInterval(float t) {
        _shotTimer.reset(t);
        return this;
    }
    
    Danmaku_1* setBulletNum(int n) {
        _bulletNum.reset(n);
        return this;
    }
    
    Danmaku_1* setCoolDown(float cd) {
        _coolDownTimer.reset(cd);
        return this;
    }
    
    Danmaku_1* setErrorAngle(float a) {
        _errorAngle = a;
        return this;
    }
    
protected:
    
    int     _damage = 0;
    float   _bulletSpeed = 200;
    float   _range = 500;
    
    Counter<float>   _coolDownTimer = 1;
    Counter<float>   _shotTimer = 0.25; //time interval between bullets
    Counter<int>     _bulletNum = 3;
    
    float   _errorAngle = 0;
};



#endif
