
#ifndef __ComPhysicsNote_h__
#define __ComPhysicsNote_h__

#include "Component.h"

class ComPhysicsEntity;
class ComPhysicsNote : public ComponentBace {
    
    ComPhysicsNote() {}
    
public:
    
    virtual ~ComPhysicsNote() override {}
    
    static ComPhysicsNote*  create(cc::Node *node) {
        ComPhysicsNote *com = new ComPhysicsNote;
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
    
    cc::RefPtr<cc::Node>    _ndoe = nullptr;
    ComPhysicsEntity*       _entity = nullptr;
};

#endif