
#ifndef __ComEngine_h__
#define __ComEngine_h__

#include "Component.h"


class ComPhysicsEntity;
class ComEngine : public ComponentBace {
    
    ComEngine() {}
    
public:
    
    virtual ~ComEngine() override {}
    
    static ComEngine*  create(float maxForce, float maxSpeed) {
        ComEngine *com = new ComEngine;
        com->setMaxForce(maxForce);
        com->setMaxSpeed(maxSpeed);
        com->autorelease();
        return com;
    }
    
    const cc::Vec2& getForce() const {
        return _force;
    }
    
    void setDirection(const cc::Vec2& direction) {
        _direction = direction;
    }
    
    void setMaxForce(float force) {
        _maxForce = force;
    }
    
    void setMaxSpeed(float speed) {
        _maxSpeed = speed;
    }
    
    float getMaxForce() const {
        return _maxForce;
    }
    
    float getMaxSpeed() const {
        return _maxSpeed;
    }
    
protected:
    
    virtual void start() override;
    
    virtual void update(float dt) override;
    
    float       _maxSpeed = 0;
    float       _maxForce = 0;
    
    cc::Vec2    _direction;
    cc::Vec2    _force;
    
    ComPhysicsEntity*           _entity = nullptr;
};

#endif
