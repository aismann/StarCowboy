
#ifndef __ComEngine_h__
#define __ComEngine_h__

#include "Component.h"


class ComPhysicsEntity;
class ComEngine : public ComponentBace {
    
    ComEngine() {}
    
public:
    
    virtual ~ComEngine() override {}
    
    static ComEngine*  create(float maxForce, float maxSpeed) {
        ComEngine *com = NewEx(ComEngine);
        com->setMaxForce(maxForce);
        com->setMaxSpeed(maxSpeed);
        return com;
    }
    
    const cc::Vec2& getForce() const {
        return _force;
    }
    
    const cc::Vec2& getDirection() const {
        return _direction;
    }
    
    ComEngine* setDirection(const cc::Vec2& direction) {
        _direction = direction;
        return this;
    }
    
    ComEngine* setMaxForce(float force) {
        _maxForce = force;
        return this;
    }
    
    ComEngine* setMaxSpeed(float speed) {
        _maxSpeed = speed;
        return this;
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
