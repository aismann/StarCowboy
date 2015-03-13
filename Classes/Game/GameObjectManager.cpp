
#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager::GameObjectManager() {
    _objects.reserve(512);
}

GameObjectManager::~GameObjectManager() {
    _objects.clear();
}

void GameObjectManager::update(float dt) {
    
    for (auto &obj : _objects) {
        if (obj && obj->isActive()) {
            obj->update(dt);
        }
    }
    
    auto newEnd = std::remove_if(_objects.begin(), _objects.end(), [](GameObject *obj){
        return obj->getLifeState() == GameObject::LifeState::Deaded;
    });
    _objects.erase(newEnd, _objects.end());
}

GameObject* GameObjectManager::createObject(const std::string& name) {
    
    GameObject *obj = GameObject::create(name);
    _objects.push_back(obj);
    return obj;
}

GameObject* GameObjectManager::getObject(const long oid) {
    
    if (_objects.empty() || oid < _objects.front()->getID() || _objects.back()->getID() < oid) {
        CCLOG("invalid objetc id [%ld]", oid);
        return nullptr;
    }
    
    auto first = _objects.begin();
    auto last = _objects.end();
    size_t len = (last - first);
    while (len != 0) {
        size_t l2 = len / 2;
        auto mid = first + l2;
        if (mid->get()->getID() < oid) {
            first = ++mid;
            len -= l2 + 1;
        } else {
            len = l2;
        }
    }
    if (first->get()->getID() == oid) {
        return first->get();
    }
    return nullptr;
}

GameObject* GameObjectManager::getObject(const std::string& name) {
    long oid = getObjectId(name);
    if (oid >= 0) {
        return getObject(oid);
    }
    return nullptr;
}

long GameObjectManager::getObjectId(const std::string& name) {
    auto it = _name2id.find(name);
    if (it != _name2id.end()) {
        return it->second;
    }
    return -1;
}

bool GameObjectManager::registerObjectName(const std::string &name, long oid) {
    if (name.size() > 0) {
        auto it = _name2id.find(name);
        if (it != _name2id.end()) {
            CCLOG("exsisted object name [%s]", name.c_str());
            return false;
        }
        _name2id[name] = oid;
        return true;
    }
    return false;
}

void GameObjectManager::unregisterObjectName(const std::string& name) {
    if (name.empty()) return;
    _name2id.erase(name);
}

void GameObjectManager::clear() {
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


