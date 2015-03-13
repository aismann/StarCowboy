//
//  GameObjectManager.h
//  ShootGame
//
//  Created by match5 on 14-8-30.
//
//

#ifndef __GameObjectManager_h__
#define __GameObjectManager_h__

#include "Singleton.h"
#include "cocos.h"

#include "TagSet.h"

class GameObject;
class GameObjectManager : public Singleton<GameObjectManager> {
    
public:
    
    GameObjectManager();
    ~GameObjectManager();
    
    GameObject* createObject(const std::string& name = "");
    
    GameObject* getObject(const long oid);
    
    GameObject* getObject(const std::string& name);
    
    long        getObjectId(const std::string& name);
    
    bool        registerObjectName(const std::string& name, long oid);
    
    void        unregisterObjectName(const std::string& name);
    
    void        update(float dt);
    
    void        clear();
    
    void        enumerateObject(std::function<void(GameObject*)> callback);
    void        enumerateObject(TagSet::TagBit tagMask, std::function<void(GameObject*)> callback);
    
    const size_t getObjectNum() const {
        return _objects.size();
    }

protected:
    
    std::vector<cc::RefPtr<GameObject>>         _objects;
    
    std::unordered_map<std::string, long>       _name2id;
};

#endif
