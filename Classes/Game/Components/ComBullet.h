
#ifndef __ComBullet_h__
#define __ComBullet_h__

#include "ComEntity.h"

class ComBullet : public ComEntity {
    
    ComBullet(cc::Node *node)
    :_ndoe(node){}
    
public:
    
    static ComBullet *create(cc::Node *node) {
        ComBullet *com = new ComBullet(node);
        com->autorelease();
        return com;
    }
    
    ComBullet* setVelocity(const cc::Vec2& v);
    
    ComBullet* setHitTestMask(TagSet::TagBit mask) {
        _hitTestMask = mask;
        return this;
    }
    
    ComBullet* setDamage(int damage) {
        _damage = damage;
        return this;
    }
    
protected:
    
    virtual void start() override;
    
    virtual void update(float dt) override;
    
    virtual void onLoad() override;
    virtual void onUnload() override;
    
    virtual void onOwnerDestroy() override;
    
    int _damage = 0;
    
    cc::Vec2 _velocity;
    
    cc::RefPtr<cc::Node> _ndoe = nullptr;
    
    TagSet::TagBit  _hitTestMask;
};
#endif