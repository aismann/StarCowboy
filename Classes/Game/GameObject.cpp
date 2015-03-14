
#include "GameObject.h"
#include "GameWorld.h"
#include "GameObjectManager.h"
#include "Component.h"
#include "GameMessageDefine.h"

GameObject::GameObject(IDType oid)
:_id(oid)
,_handleIndex(-1)
,_name(nullptr)
,_tagBits(TagSet::null.bit()) {
    _world = GameWorld::getInstance();
}

GameObject::~GameObject() {
    CCLOG("~GameObject %ld", _id);
    destroy();
}

GameObject*	GameObject::create(IDType oid) {
    GameObject	*obj = new GameObject(oid);
    obj->autorelease();
    return obj;
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
        _name = new std::string(name);
    }
}

void GameObject::addComponent(ComponentBace* com, const std::string& name) {
    if (_components == nullptr) {
        _components = new ComVecType;
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
        }
    }
    _components->clear();
}

void GameObject::removeComponentIterator(ComVecType::iterator it) {
    it->get()->onUnload();
    it->get()->setOwner(nullptr);
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

void GameObject::destroy() {
    if (_lifeState != LifeState::Deaded) {
        _lifeState = LifeState::Deaded;
        for (auto it : *_components) {
            if (it) {
                it->onOwnerDestroy();
            }
        }
        for (auto it : *_components) {
            if (it) {
                it->onUnload();
                it->setOwner(nullptr);
            }
        }
        _components->clear();
        
        if (_name) {
            delete _name;
            _name = nullptr;
        }
        
        CCLOG("destroy %ld", _id);
    }
}

void GameObject::update(float dt) {
    for (auto it : *_components) {
        if (it && it->isEnabled()) {
            if (it->isStared() == false) {
                it->start();
                it->setStared();
            }
            it->update(dt);
        }
    }
}

void GameObject::sendMessage(const GameMessage& msg) {
    onMessage(msg);
    for (auto com : *_components) {
        if (com) {
            com->onMessage(msg);
        }
    }
}

void GameObject::sendMessage(const GAME_MSG msg, long nParam, void* pParam, GameObject* objParam) {
    sendMessage({msg, _id, nParam, pParam, objParam});
}

void GameObject::onMessage(const GameMessage& msg) {
    switch (msg.id) {
        case GAME_MSG::AWAK_OBJECT:
            awake();
            break;
		case GAME_MSG::KILL_OBJECT:
            destroy();
            break;
        default:
            break;
    }
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
