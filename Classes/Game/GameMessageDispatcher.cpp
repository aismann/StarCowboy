
#include "GameMessageDispatcher.h"
#include "GameObject.h"
#include "GameObjectManager.h"

void GameMessageDispatcher::postMessage(long receiver, const GameMessage msg, float delay) {
    GameMessagePack pack = {receiver, delay, nullptr};
    _messageQueue.push_back(std::make_pair(msg, pack));
}

void GameMessageDispatcher::postMessage(long receiver, const GAME_MSG msg, long sender, long nParam, void* pParam, long objParam, float delay) {
    GameMessage m = {msg, sender, nParam, pParam, objParam};
    GameMessagePack pack = {receiver, delay, nullptr};
    _messageQueue.push_back(std::make_pair(m, pack));
}

void GameMessageDispatcher::broadcast(const GameMessage msg, MsgPred &pred, float delay) {
    GameMessagePack t = {-1, delay, pred};
    _messageQueue.push_back(std::make_pair(msg, t));
    
}
void GameMessageDispatcher::broadcast(const GAME_MSG msg, long sender, MsgPred &pred, long nParam, void* pParam, long objParam, float delay) {
    GameMessage m = {msg, sender, nParam, pParam, objParam};
    GameMessagePack pack = {-1, delay, nullptr};
    _messageQueue.push_back(std::make_pair(m, pack));
}

void GameMessageDispatcher::update(float dt) {
    std::list<MsgItem>::iterator it = _messageQueue.begin();
    while (it != _messageQueue.end()) {
        if (it->second.delay <= 0) {
            msgDispatch(*it);
            it = _messageQueue.erase(it);
        } else {
            it->second.delay -= dt;
            ++it;
        }
    }
}

void GameMessageDispatcher::msgDispatch(const MsgItem& item) {
    if (item.second.receiver >= 0) {
        GameObject *obj = GameObjectManager::getInstance()->getObjectHandle(item.second.receiver).get();
        if (obj) {
            if (item.second.pred) {
                if (item.second.pred(obj)) {
                    obj->sendMessage(item.first);
                }
            } else {
                obj->sendMessage(item.first);
            }
        }
    } else {
        GameObjectManager::getInstance()->enumerateObject([&item](GameObject *obj){
            if (item.second.pred) {
                if (item.second.pred(obj)) {
                    obj->sendMessage(item.first);
                }
            } else {
                obj->sendMessage(item.first);
            }
        });
    }
}
