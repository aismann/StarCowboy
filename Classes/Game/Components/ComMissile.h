//
//  ComMissile.h
//  StarCowboy
//
//  Created by match5 on 15/2/28.
//
//

#ifndef __ComMissile_h__
#define __ComMissile_h__

#include "ComEntity.h"
#include "MathUtils.h"

class ComPhysicsEntity;
class ComMissile : public ComEntity
{
    
    ComMissile(cc::Node *node)
    :_ndoe(node){}
    
public:
    
    static ComMissile *create(cc::Node *node) {
        ComMissile *com = new ComMissile(node);
        com->autorelease();
        return com;
    }
    
    ComMissile* setDirection(const cc::Vec2& d);
    
    ComMissile* setVelocity(const cc::Vec2& v) {
        _velocity = v;
        return this;
    }
    
    ComMissile* setMaxSpeed(float s) {
        _maxSpeed = s;
        return this;
    }
    
    ComMissile* setTargetMask(TagSet::TagBit m) {
        _targetMask = m;
        return this;
    }
    
    ComMissile* setHitTestMask(TagSet::TagBit m) {
        _hitTestMask |= m;
        return this;
    }
    
    ComMissile* setDamage(int d) {
        _damage = d;
        return this;
    }
    
    ComMissile* setSearchAngular(float a) {
        _searchRadian = math::angle2Radian(a);
        return this;
    }
    
    ComMissile* setAngularSpeed(float s) {
        _angularSpeed = s;
        return this;
    }
    
protected:
    
    virtual void start() override;
    
    virtual void update(float dt) override;
    
    virtual void onLoad() override;
    virtual void onUnload() override;
    
    virtual void onOwnerDestroy() override;
    
    int             _damage = 0;
    
    TagSet::TagBit  _targetMask;
    TagSet::TagBit  _hitTestMask;
    
    cc::Vec2        _direction;
    
    cc::Vec2        _velocity;
    float           _maxSpeed;
    float           _accelerationTime = 0.25;
    float           _acceleratFinished = false;
    
    float           _angularSpeed = 0;
    
    float           _searchRadian = 0;
    
    cc::RefPtr<ComPhysicsEntity> _targetEntity;
    
    cc::RefPtr<cc::Node> _ndoe = nullptr;
};

#endif
