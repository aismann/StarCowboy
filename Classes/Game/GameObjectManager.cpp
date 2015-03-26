
#include "GameObjectManager.h"
#include "GameObject.h"

GameObject::IDType GameObjectManager::_nextValidID = 0;

GameObjectManager::GameObjectManager() {
    _objects.reserve(512);
}

GameObjectManager::~GameObjectManager() {
    clear();
}

void GameObjectManager::update(float dt) {
    
    for (auto &obj : _objects) {
        if (obj) {
            if (obj->isActive()) {
                obj->update(dt);
            } else if (obj->getLifeState() == GameObject::LifeState::Deaded) {
                _availableHandles.push_back(obj->getHandleIndex());
                _id2Index.erase(obj->getID());
                if (!obj->getName().empty()) {
                    _name2Index.erase(obj->getName());
                }
                DelEx(GameObject, obj);
            }
        }
    }
}

GameObjectHandle GameObjectManager::createObject(const std::string& name) {
    
    GameObject* obj = NewEx(GameObject, _nextValidID++);
    long index = _objects.size();
    if (!_availableHandles.empty()) {
        index = *_availableHandles.begin();
        _availableHandles.pop_front();
        _objects[index] = obj;
    } else {
        _objects.push_back(obj);
    }
    obj->setHandleIndex(index);
    _id2Index[obj->getID()] = index;
    if (!name.empty()) {
        _name2Index[name] = index;
        obj->setName(name);
    }
    return {index, obj->getID()};
}

GameObjectHandle GameObjectManager::getObjectHandle(GameObject::IDType oid) const {
    
    auto it = _id2Index.find(oid);
    if (it != _id2Index.end()) {
        GameObject* obj = _objects[it->second];
        if (obj && obj->getID() == oid) {
            return {it->second, oid};
        }
    }
    return {-1, -1};
}

GameObjectHandle GameObjectManager::getObjectHandle(const std::string& name) const {
    long index = getObjectHandleIndex(name);
    if (index >= 0) {
        GameObject *obj = _objects[index];
        if (obj) {
            return {obj->getHandleIndex(), obj->getID()};
        }
    }
    return {-1, -1};
}

GameObject* GameObjectManager::getObject(const long handleIndex) const {
    return _objects[handleIndex];
}

long GameObjectManager::getObjectHandleIndex(const std::string& name) const {
    auto it = _name2Index.find(name);
    if (it != _name2Index.end()) {
        return it->second;
    }
    return -1;
}

void GameObjectManager::clear() {
    for (auto& obj : _objects) {
        if (obj) {
            DelEx(GameObject, obj);
        }
    }
    _objects.clear();
}

void GameObjectManager::enumerateObject(std::function<void(GameObject*)> callback)
{
    for (auto obj : _objects) {
        if (obj) {
            callback(obj);
        }
    }
}

void GameObjectManager::enumerateObject(TagSet::TagBit tagMask, std::function<void(GameObject*)> callback) {

    for (auto obj : _objects) {
        if (obj && (obj->getTagBits() & tagMask) != 0) {
            callback(obj);
        }
    }
}


