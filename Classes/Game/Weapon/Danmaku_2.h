//
//  Danmaku_2.h
//  StarCowboy
//
//  Created by match5 on 15/9/9.
//
//

#ifndef __Danmaku_2_h__
#define __Danmaku_2_h__

#include "Weapon.h"

class Danmaku_2 : public Weapon
{
    
public:
    
    static Danmaku_2* create() {
        Danmaku_2* weapon = New(Danmaku_2);
        return weapon;
    }
    
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity) override;
    
    virtual void update(float dt) override;
    
    Danmaku_2* setDamage(int d) {
        _damage = d;
        return this;
    }
    
    Danmaku_2* setBulletSpeed(float s) {
        _bulletSpeed = s;
        return this;
    }
    
    Danmaku_2* setRange(float r) {
        _range = r;
        return this;
    }
    
    Danmaku_2* setShotInterval(float t) {
        _shotTimer.reset(t);
        return this;
    }
    
    Danmaku_2* setWaveNum(int n) {
        _waveNum.reset(n);
        return this;
    }
    
    Danmaku_2* setBulletNum(int n) {
        _bulletNum = n;
        return this;
    }
    
    Danmaku_2* setCoolDown(float cd) {
        _coolDownTimer.reset(cd);
        return this;
    }
    
    Danmaku_2* setShotAngle(float a) {
        _shotAngle = a;
        return this;
    }
    
protected:
    
    int     _damage = 0;
    float   _bulletSpeed = 200;
    float   _range = 500;
    
    Counter<float>  _coolDownTimer = 1;
    Counter<float>  _shotTimer = 0.25;  //time interval between waves
    Counter<int>    _waveNum = 1;
    int             _bulletNum = 3; //how many bullet per wave
    
    float   _shotAngle = 45;
};



#endif
