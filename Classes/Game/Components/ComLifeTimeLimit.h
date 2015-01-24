
#ifndef __ComLifeTimeLimit_h__
#define __ComLifeTimeLimit_h__
#include "Component.h"

class ComLifeTimeLimit : public ComponentBace {
    
    ComLifeTimeLimit(float time) : _limit(time) {}
    
public:
    
    static ComLifeTimeLimit *create(float time) {
        ComLifeTimeLimit *com = new ComLifeTimeLimit(time);
        com->autorelease();
        return com;
    }

    
protected:
    
    virtual void update(float dt) override {
        _timer += dt;
        if (_timer >= _limit) {
            getOwner()->destroy();
        }
    }
    
    float _limit = 0;
    float _timer = 0;
};
#endif
