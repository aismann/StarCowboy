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

#include "GameObjectHandle.h"
#include "TagSet.h"

#include <list>

class GameObjectManager : public Singleton<GameObjectManager> {
    
public:
    
    typedef std::vector<GameObject*> ObjectListType;
    
    GameObjectManager();
    ~GameObjectManager();
    
    GameObjectHandle createObject(const std::string& name = "");
    
    GameObjectHandle getObjectHandle(long oid) const;
    
    GameObjectHandle getObjectHandle(const std::string& name) const;
    
    GameObject* getObject(const long handleIndex) const;
    
    long        getObjectHandleIndex(const std::string& name) const;
    
    void        update(float dt);
    
    void        clear();
    
    void        enumerateObject(std::function<void(GameObject*)> callback);
    void        enumerateObject(TagSet::TagBit tagMask, std::function<void(GameObject*)> callback);
    
    void        enumerateObjectAfter(long index, std::function<void(GameObject*)> callback);
    void        enumerateObjectAfter(long index, TagSet::TagBit tagMask, std::function<void(GameObject*)> callback);
    
    const size_t getObjectNum() const {
        return _id2Index.size();
    }
    
    const size_t getObjectVecSize() const {
        return _objects.size();
    }

protected:
    
    ObjectListType                                          _objects;
    std::unordered_map<std::string, long>                   _name2Index;
    std::unordered_map<long, long>                          _id2Index;
    std::list<long>                                         _availableHandles;
    
    static  long                                            _nextValidID;
};

#endif
