//
//  GameObjectHandle.h
//  StarCowboy
//
//  Created by match5 on 15/3/13.
//
//

#ifndef __GameObjectHandle_h__
#define __GameObjectHandle_h__

class GameObject;

class GameObjectHandle
{
public:
    
    GameObjectHandle() = default;
    
    GameObjectHandle(const GameObject& obj);
    
    GameObjectHandle(long index, long oid)
    :_handleIndex(index)
    ,_id(oid){
    }
    
    GameObject* get() const;
    
    long  getIndex() const { return _handleIndex; }
    long  getID() const { return _id; }
    
    void reset() {
        _handleIndex = -1;
        _id = -1;
    }
    
    operator bool() const {
        return get() != nullptr;
    }
    
protected:
    
    long                _handleIndex = -1;
    long                _id = -1;
};

#endif
