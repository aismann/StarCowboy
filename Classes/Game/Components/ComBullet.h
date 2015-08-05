
#ifndef __ComBullet_h__
#define __ComBullet_h__

#include "ComEntity.h"

class ComBullet : public ComEntity {
    
    ComBullet(cc::Node *node)
    :_ndoe(node){}
    
public:
    
    static ComBullet *create(cc::Node *node) {
        ComBullet *com = New(ComBullet, node);
        return com;
    }
    
    ComBullet* setVelocity(const cc::Vec2& v);
    
    ComBullet* setHeading(const cc::Vec2& v);
    
    ComBullet* setHitTestMask(Tag::Bit m) {
        _hitTestMask = m;
        return this;
    }
    
    ComBullet* setDamage(int d) {
        _damage = d;
        return this;
    }
    
protected:
    
    virtual void start() override;
    
    virtual void update(float dt) override;
    
    virtual void onUnload() override;
    
    virtual void onOwnerDead() override;
    
    void onHit();
    
    int _damage = 0;
    
    cc::Vec2 _velocity;
    
    Tag::Bit          _hitTestMask;
    
    cc::RefPtr<cc::Node> _ndoe = nullptr;
};
#endif