//
//  Danmaku_3.h
//  StarCowboy
//
//  Created by match5 on 15/9/9.
//
//

#ifndef __Danmaku_3_h__
#define __Danmaku_3_h__

#include "Weapon.h"

class Danmaku_3 : public Weapon
{
    
public:
    
    static Danmaku_3* create() {
        Danmaku_3* weapon = New(Danmaku_3);
        return weapon;
    }
    
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity) override;
    
    virtual void update(float dt) override;
    
    Danmaku_3* setDamage(int d) {
        _damage = d;
        return this;
    }
    
    Danmaku_3* setBulletSpeed(float s) {
        _bulletSpeed = s;
        return this;
    }
    
    Danmaku_3* setRange(float r) {
        _range = r;
        return this;
    }
    
    Danmaku_3* setShotInterval(float t) {
        _shotTimer.reset(t);
        return this;
    }
    
    Danmaku_3* setBulletNum(int n) {
        _bulletNum.reset(n);
        return this;
    }
    
    Danmaku_3* setCoolDown(float cd) {
        _coolDownTimer.reset(cd);
        return this;
    }
    
    Danmaku_3* setShotAngle(float a) {
        _shotAngle = std::abs(a);
        return this;
    }
    
    Danmaku_3* setReverse(bool b) {
        _isReverse = b;
        return this;
    }
    
protected:
    
    int     _damage = 0;
    float   _bulletSpeed = 200;
    float   _range = 500;
    
    Counter<float>  _coolDownTimer = 1;
    Counter<float>  _shotTimer = 0.25;  //time interval between waves
    Counter<int>    _bulletNum = 5; //how many bullet per wave
    
    float   _shotAngle = 45;
    
    cc::Vec2    _shootDirection = {0, 0};
    bool        _isShooting = false;
    bool        _isReverse = false;
};



#endif
