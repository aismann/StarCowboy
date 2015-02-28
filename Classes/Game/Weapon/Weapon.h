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
#include "TagSet.h"

class Weapon : public cc::Ref
{
public:
    virtual bool fire(const cc::Vec2& from,
                      const cc::Vec2& direction,
                      const cc::Vec2& shipVelocity) = 0;
    
    virtual void stopFire() {};
    
    virtual void update(float dt) {};
    
    Weapon* setTargetMask(const TagSet::TagBit& m) {
        _targetMask = m;
        return this;
    }
    
    Weapon* addHitTestMask(const TagSet::TagBit& m) {
        _hitTestMask |= m;
        return this;
    }
    
protected:
    
    TagSet::TagBit _targetMask;
    TagSet::TagBit _hitTestMask;
};

#endif
