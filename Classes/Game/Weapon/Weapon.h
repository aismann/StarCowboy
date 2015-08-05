//
//  Weapon.h
//  StarCowboy
//
//  Created by match5 on 15/2/26.
//
//

#ifndef __Weapon_h__
#define __Weapon_h__

#include "cocos.h"
#include "Tag.h"
#include "Timer.h"
#include "Allocator.h"

class Weapon
{
public:
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity) = 0;
    
    virtual void stopFire() {};
    
    virtual void update(float dt) {};
    
    Weapon* setTargetMask(const Tag::Bit& m) {
        _targetMask = m;
        return this;
    }
    
    Weapon* addHitTestMask(const Tag::Bit& m) {
        _hitTestMask |= m;
        return this;
    }
    
protected:
    
    Tag::Bit _targetMask;
    Tag::Bit _hitTestMask;
};

#endif
