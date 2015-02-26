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
                      const cc::Vec2& shipVelocity,
                      const TagSet::TagBit& targetTag) = 0;
    
    virtual void update(float dt) {};
};

#endif
