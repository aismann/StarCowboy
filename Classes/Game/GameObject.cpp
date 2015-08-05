
#include "GameObject.h"
#include "GameWorld.h"
#include "GameObjectManager.h"
#include "Component.h"
#include "GameMessageDefine.h"
#include "Allocator.h"

GameObject::GameObject(IDType oid)
:_id(oid)
,_handleIndex(-1)
,_name(nullptr)
,_world(nullptr)
,_tagBits(Tag::null.bit()) {
    _world = GameWorld::getInstance();
}
 
GameObject::~GameObject() {
    destroy();
}

const std::string& GameObject::getName() const {
    if (_name) {
        return *_name;
    }
    return constants::EmptyString;
}

void GameObject::setName(const std::string& name) {
    if (_name) {
        *_name = name;
    } else {
        _name = New(std::string, name);
    }
}

void GameObject::addComponent(ComponentBace* com, const std::string& name) {
    if (_components == nullptr) {
        _components = New(ComVecType);
    }
    _components->push_back(com);
    com->setOwner(this);
    com->setName(name);
    com->onLoad();
}

void GameObject::removeComponent(const std::string& name) {
    auto it = findComByName(name);
    if (it != _components->end()) {
        removeComponentIterator(it);
    }
}

void GameObject::removeAllComponents() {
    for (auto it : *_components) {
        if (it) {
            it->onUnload();
            it->setOwner(nullptr);
            Delete(it);
        }
    }
    _components->clear();
}

void GameObject::removeComponentIterator(ComVecType::iterator it) {
    (*it)->onUnload();
    (*it)->setOwner(nullptr);
    Delete(*it);
    _components->erase(it);
}

void GameObject::awake() {
    if (_lifeState != LifeState::Active) {
        _lifeState = LifeState::Active;
        for (auto it : *_components) {
            if (it) {
                it->onOwnerAwake();
            }
        }
    }
}

void GameObject::sleep() {
    if (_lifeState != LifeState::Sleep) {
        _lifeState = LifeState::Sleep;
        for (auto it : *_components) {
            if (it) {
                it->onOwnerSleep();
            }
        }
    }
}

void GameObject::kill() {
    if (_lifeState != LifeState::Deaded) {
        _lifeState = LifeState::Deaded;
        for (auto it : *_components) {
            if (it) {
                it->onOwnerDead();
            }
        }
    }
}

void GameObject::destroy() {
    removeAllComponents();
    Delete(_components);
    Delete(_name);
}

void GameObject::update(float dt) {
    for (auto it : *_components) {
        if (it && it->isEnabled()) {
            it->doUpdate(dt);
        }
    }
}

void GameObject::sendMessage(const GameMessage& msg) {
    if (onMessage(msg)) {
        return;
    }
    for (auto com : *_components) {
        if (com && com->onMessage(msg)) {
            break;
        }
    }
}

void GameObject::sendMessage(const GAME_MSG msg, long nParam, void* pParam, long objParam) {
    sendMessage({msg, _id, nParam, pParam, objParam});
}

bool GameObject::onMessage(const GameMessage& msg) {
    switch (msg.id) {
        case GAME_MSG::AWAK_OBJECT:
            awake();
            return true;
		case GAME_MSG::KILL_OBJECT:
            destroy();
            return true;
        default:
            break;
    }
    return false;
}

GameObject::ComVecType::iterator GameObject::findComByName(const std::string& name) const {
    auto it = std::find_if(_components->begin(), _components->end(), [&name](const ComponentBace* com) {
        return com->getName() == name;
    });
    return it;
}

GameWorld* GameObject::getWorld() {
    return _world;
}
