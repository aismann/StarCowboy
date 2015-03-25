
#ifndef __GameMessageDispatcher_h__
#define __GameMessageDispatcher_h__
#include "Singleton.h"
#include "cocos.h"
#include "GameMessage.h"

class GameObject;
class GameMessageDispatcher : public Singleton<GameMessageDispatcher> {
    
public:
    
    void        postMessage(long receiver, const GameMessage msg, float delay = 0);
    
    void        postMessage(long receiver, const GAME_MSG msg, long sender, long nParam = 0, void* pParam = nullptr, long objParam = -1, float delay = 0);
    
    void        broadcast(const GameMessage msg, MsgPred &pred, float delay = 0);
    
    void        broadcast(const GAME_MSG msg, long sender, MsgPred &pred, long nParam = 0, void* pParam = nullptr, long objParam = -1, float delay = 0);
    
    void        update(float dt);
    
protected:
    
    std::list<MsgItem>                  _messageQueue;
    
    void                                msgDispatch(const MsgItem& item);
};

#endif
