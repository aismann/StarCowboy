
#ifndef __GameObject_h__
#define __GameObject_h__


#include "Component.h"
#include "Tag.h"
#include "GameMessage.h"
#include "Constants.h"
#include "Allocator.h"
#include "GameObjectHandle.h"

#include <vector>

class GameWorld;
class GameObjectManager;
class ComponentBace;
class GameObject : public GameMessageHandler{
    
    friend class GameObjectManager;
    
    typedef std::vector<ComponentBace*> ComVecType;
    
    struct CompareById {
        bool operator()(const GameObject* lhs, const GameObject* rhs) const {
            return lhs->getID() < lhs->getID();
        }
    };
    
public:
    
    typedef long IDType;
    
    virtual ~GameObject()   final;
    
    const IDType            getID() const { return _id; }
    const long              getHandleIndex() const { return _handleIndex; }
    void                    setHandleIndex(long index) { _handleIndex = index; }
    
    GameObjectHandle        handle() { return GameObjectHandle(_handleIndex, _id); }
    
    const std::string&      getName() const;
    void                    setName(const std::string& name);
    
    const Tag::Bit&   getTagBits() const { return _tagBits; }
    
    void                    setTagBits(const Tag::Bit& tb) { _tagBits = tb; }
    
    template<class ReturnType>
    ReturnType*             getComponent(const std::string& name) const {
        static_assert(std::is_convertible<ReturnType*, ComponentBace*>::value, "Invalid Type");
        if (_components) {
            auto it = findComByName(name);
            if (it != _components->end()) {
                return dynamic_cast<ReturnType*>(*it);
            }
        }
        return nullptr;
    }
    
    void                    addComponent(ComponentBace* com, const std::string& name = "");
    
    void                    removeComponent(const std::string& name);
    
    void                    removeAllComponents();
    
    void                    sendMessage(const GameMessage& msg);
    
    void                    sendMessage(const GAME_MSG msg, long nParam = 0, void* pParam = nullptr, long objParam = -1);
    
    GameWorld*              getWorld();
    
    enum class LifeState {
        Sleep,
        Active,
        Deaded,
    };
    
    LifeState               getLifeState() { return _lifeState; }
    
    void                    setLifeState(LifeState ls) { _lifeState = ls; }
    
    bool                    isActive() {
        return _lifeState == LifeState::Active;
    }
    
    virtual void            awake();
    virtual void            sleep();
    virtual void            kill();
    
protected:
    
    GameObject(IDType oid);
    virtual void            destroy();
    
    virtual void            update(float dt);
    
    virtual bool            onMessage(const GameMessage& msg) override;
    
    IDType                  _id;
    long                    _handleIndex;
    
    std::string*            _name;
    
    GameWorld*              _world;
    
    Tag::Bit          _tagBits;
    
    LifeState               _lifeState = LifeState::Sleep;
    
    ComVecType*             _components = nullptr;
    
    ComVecType::iterator    findComByType(const std::type_info& type) const;
    
    ComVecType::iterator    findComByName(const std::string& name) const;
    
    void                    removeComponentIterator(ComVecType::iterator it);
};

#endif
