//
//  GameObjectHandle.cpp
//  StarCowboy
//
//  Created by match5 on 15/3/13.
//
//

#include "GameObjectHandle.h"
#include "GameObject.h"
#include "GameObjectManager.h"


GameObjectHandle::GameObjectHandle(const GameObject& obj)
:_handleIndex(obj.getHandleIndex())
,_id(obj.getID()){
}

GameObject* GameObjectHandle::get() const {
    if (_handleIndex >= 0) {
        GameObject* obj = GameObjectManager::getInstance()->getObject(_handleIndex);
        if (obj && obj->getID() == _id) {
            return obj;
        }
    }
    return nullptr;
}