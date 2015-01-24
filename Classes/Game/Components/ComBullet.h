
#ifndef __ComBullet_h__
#define __ComBullet_h__

#include "Component.h"

class ComPhysicsEntity;
class ComBullet : public ComponentBace {
    
    ComBullet(int damage, cc::Node *node)
    : _damage(damage)
    ,_ndoe(node){}
    
public:
    
    static ComBullet *create(int damage, cc::Node *node = nullptr) {
        ComBullet *com = new ComBullet(damage, node);
        com->autorelease();
        return com;
    }
    
protected:
    
    virtual void start() override;
    
    virtual void update(float dt) override;
    
    virtual void onLoad() override;
    virtual void onUnload() override;
    
    virtual void onMessage(const GameMessage& msg);
    
    float _damage = 0;
    
    cc::RefPtr<cc::Node>    _ndoe = nullptr;
    
    ComPhysicsEntity*       _entity = nullptr;
};
#endif