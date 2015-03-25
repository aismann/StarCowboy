
#ifndef __MessagHandler_h__
#define __MessagHandler_h__

#include "GameMessageDefine.h"
#include "GameObjectHandle.h"

typedef std::function<bool(GameObject*)> MsgPred;

struct GameMessage {
    GameMessage() = default;
    GameMessage(GAME_MSG i, long s, long n, void* p, long oid)
    :id(i)
    ,sender(s)
    ,nParam(n)
    ,pParam(p)
    ,objParam(oid){
    }
    
    GAME_MSG    id      = GAME_MSG::NONE;
    long        sender  = 0;
    long        nParam  = 0;
    void*       pParam  = nullptr;
    long        objParam;
};

struct GameMessagePack {
    long                                receiver;
    float                               delay;
    MsgPred                             pred;
};

typedef std::pair<GameMessage, GameMessagePack> MsgItem;

class GameMessageHandler {
public:
    virtual ~GameMessageHandler() {};
    virtual void onMessage(const GameMessage& msg) {};
};

#endif
