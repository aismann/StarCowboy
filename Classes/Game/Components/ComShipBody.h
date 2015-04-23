
#ifndef __ComShipBody_h__
#define __ComShipBody_h__

#include "Component.h"

class ComPhysicsEntity;
class ComEngine;
class ComParticleEmiter;
class ComShipBody : public ComponentBace {
    
    ComShipBody() {}
    
public:
    
    virtual ~ComShipBody() override {}
    
    static ComShipBody*  create(cc::Node *node) {
        ComShipBody *com = NewEx(ComShipBody);
        com->_ndoe = node;
        return com;
    }
    
    cc::Node* getNode() const {
        return _ndoe;
    }
    
protected:
    
    virtual void start() override;
    virtual void update(float dt) override;
    
    virtual void onLoad() override;
    virtual void onUnload() override;
    
    virtual void onOwnerDead() override;

    cc::RefPtr<cc::Node>    _ndoe = nullptr;
    
    ComPhysicsEntity*       _entity = nullptr;
    ComEngine*              _engine = nullptr;
    ComParticleEmiter*      _emiter = nullptr;
};

#endif
