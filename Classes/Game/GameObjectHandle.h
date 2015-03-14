//
//  GameObjectHandle.h
//  StarCowboy
//
//  Created by match5 on 15/3/13.
//
//

#ifndef __GameObjectHandle_h__
#define __GameObjectHandle_h__

#include "GameObject.h"

class GameObjectHandle
{
public:
    
    GameObjectHandle() = default;
    
    GameObjectHandle(long index, GameObject::IDType oid)
    :_handleIndex(index)
    ,_id(oid){
    }
    
    GameObject* get() const;
    
    long  getIndex() const { return _handleIndex; }
    GameObject::IDType  getID() const { return _id; }
    
    void reset() {
        _handleIndex = -1;
        _id = -1;
    }
    
    operator bool() const {
        return get() != nullptr;
    }
    
protected:
    
    long                _handleIndex = -1;
    GameObject::IDType  _id = -1;
};

#endif
