
#ifndef __ComShipBody_h__
#define __ComShipBody_h__

#include "Component.h"

class ComPhysicsEntity;
class ComEngine;
class ComShipBody : public ComponentBace {
    
    ComShipBody() {}
    
public:
    
    virtual ~ComShipBody() override {}
    
    static ComShipBody*  create(cc::Node *node) {
        ComShipBody *com = new ComShipBody;
        com->autorelease();
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
    
    virtual void onOwnerDestroy() override;

    cc::RefPtr<cc::Node>    _ndoe = nullptr;
    
    ComPhysicsEntity*       _entity = nullptr;
    ComEngine*              _engine = nullptr;
};

#endif
