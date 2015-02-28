
#ifndef __MessagHandler_h__
#define __MessagHandler_h__

#include "GameMessageDefine.h"

class GameObject;

typedef std::function<bool(GameObject*)> MsgPred;

struct GameMessage {
    GameMessage() = default;
    GameMessage(GAME_MSG i, long s, long n, void* p, GameObject* o)
    :id(i)
    ,sender(s)
    ,nParam(n)
    ,pParam(p)
    ,objParam(o){}
    
    GAME_MSG    id      = GAME_MSG::NONE;
    long        sender  = 0;
    long        nParam  = 0;
    void*       pParam  = nullptr;
    cc::RefPtr<GameObject>  objParam = nullptr;
};

struct GameMessagePack {
    long                                receiver;
    float                               delay;
    MsgPred                             pred;
};

typedef std::pair<GameMessage, GameMessagePack> MsgItem;

class GameMessageHandler {
public:
    virtual void onMessage(const GameMessage& msg) {};
};

#endif
