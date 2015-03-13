
#ifndef __GameWorld_h__
#define __GameWorld_h__

#include "cocos.h"

#include "Singleton.h"

#include <vector>
#include <unordered_map>
#include <memory>

class GameObject;
class GameObjectManager;
class GameMessageDispatcher;
class GameWorld : public Singleton<GameWorld>  {

public:
    
    GameWorld();
    ~GameWorld();
    
    void        reset();
    
    void        update(float dt);
    
    GameObjectManager*  getObjectManager() const {
        return _objectManager;
    }
    
    GameMessageDispatcher* getMessageDispatcher() const {
        return _messageDisoatcher;
    }
    
    cc::Node*  getGameForeground() const {
        return _foreground;
    }
    
    cc::Node*  getGameBackground() const {
        return _background;
    }
    
    cc::Layer*  getGameLayer() const {
        return _gameLayer;
    }
    
    cc::Layer*  getUiLayer() const {
        return _uiLayer;
    }
    
protected:
    
    GameObjectManager*                  _objectManager;
    GameMessageDispatcher*              _messageDisoatcher;
    
    cc::RefPtr<cc::Node>                _foreground;
    cc::RefPtr<cc::Node>                _background;
    
    cc::RefPtr<cc::Layer>               _gameLayer;
    
    cc::RefPtr<cc::Layer>               _uiLayer;
    
    
    cocos2d::RefPtr<cocos2d::LabelAtlas> _objNumLabel;
};

#endif
