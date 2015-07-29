
#ifndef __ComHitPoint_h__
#define __ComHitPoint_h__
#include "Component.h"

class ComHitPoint : public ComponentBace {
    
    ComHitPoint(int hp) : _hp(hp) {}
    
public:
    
    static ComHitPoint *create(int hp) {
        ComHitPoint *com = New(ComHitPoint, hp);
        return com;
    }
    
    
protected:
    
    bool onMessage(const GameMessage& msg)
    {
        if (msg.id == GAME_MSG::TAKE_DAMEGE) {
            _hp -= msg.nParam;
            if (_hp<=0) {
                getOwner()->kill();
                return true;
            }
        }
        return false;
    }
    
    float _hp = 0;
};
#endif