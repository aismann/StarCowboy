
#ifndef __ComHitPoint_h__
#define __ComHitPoint_h__
#include "Component.h"

class ComHitPoint : public ComponentBace {
    
    ComHitPoint(int hp) : _hp(hp) {}
    
public:
    
    static ComHitPoint *create(int hp) {
        ComHitPoint *com = new ComHitPoint(hp);
        com->autorelease();
        return com;
    }
    
    
protected:
    
    void onMessage(const GameMessage& msg)
    {
        if (msg.id == GAME_MSG::TAKE_DAMEGE) {
            _hp -= msg.nParam;
            if (_hp<=0) {
                getOwner()->destroy();
            }
        }
    }
    
    float _hp = 0;
};
#endif