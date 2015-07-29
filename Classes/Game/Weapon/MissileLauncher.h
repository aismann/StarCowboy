//
//  MissileLauncher.h
//  StarCowboy
//
//  Created by match5 on 15/2/27.
//
//

#ifndef __MissileLauncher_h__
#define __MissileLauncher_h__


#include "Weapon.h"

class MissileLauncher : public Weapon
{
    
public:
    
    static MissileLauncher* create() {
        MissileLauncher* weapon = New(MissileLauncher);
        return weapon;
    }
    
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity) override;
    
    virtual void update(float dt) override;
    
    MissileLauncher* setDamage(int d) {
        _damage = d;
        return this;
    }
    
    MissileLauncher* setMissileSpeed(float s) {
        _missileSpeed = s;
        return this;
    }
    
    MissileLauncher* setFlyingTime(float t) {
        _flyingTime = t;
        return this;
    }
    
    MissileLauncher* setMaxAmmoNum(float n) {
        _maxAmmoNum = n;
        _ammoNum = _maxAmmoNum;
        return this;
    }
    
    MissileLauncher* setReloadTime(float t) {
        _reloadTimer.reset(t);
        return this;
    }
    
    
    MissileLauncher* setCoolDown(float cd) {
        _coolDownTimer.reset(cd);
        return this;
    }
    
    MissileLauncher* setSearchAngular(float a) {
        _searchAngular = a;
        return this;
    }
    
    MissileLauncher* setAngularSpeed(float s) {
        _angularSpeed = s;
        return this;
    }
    
protected:
    
    int     _damage = 0;
    float   _missileSpeed = 50;
    float   _flyingTime = 5;
    
    float   _searchAngular = 30;
    float   _angularSpeed = 180;
    
    int     _ammoNum = 2;
    int     _maxAmmoNum = 2;
    
    bool    _isLeftLaunche = true;
    
    Timer   _reloadTimer = 2;
    
    Timer   _coolDownTimer = 0.5;
};

#endif
