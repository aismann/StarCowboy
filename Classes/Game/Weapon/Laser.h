//
//  Laser.h
//  StarCowboy
//
//  Created by match5 on 15/2/27.
//
//

#ifndef __Laser_h__
#define __Laser_h__

#include "Weapon.h"

class Laser : public Weapon
{
public:
    
    static Laser* create(cc::Node* light) {
        Laser* weapon = NewEx(Laser);
        weapon->_light = light;
        return weapon;
    }
    
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity) override;
    
    virtual void stopFire() override;
    
    virtual void update(float dt) override;
    
    Laser* setDPS(int dps) {
        _dps = dps;
        return this;
    }

protected:
    
    float                   _energy = 100;
    float                   _maxEnergy = 100;
    float                   _energySpendTime = 5;
    float                   _energyRechargeTime = 10;
    
    int                     _dps = 0;
    
    float                   _range = 100;
    
    cc::Vec2                _from;
    cc::Vec2                _direction;
    
    bool                    _isFire = false;
    
    cc::RefPtr<cc::Node>    _light;
};

#endif
