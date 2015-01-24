
#ifndef __GameObject_h__
#define __GameObject_h__


#include "Component.h"
#include "TagSet.h"
#include "GameMessage.h"
#include "Constants.h"

#include <vector>

class GameWorld;
class GameObjectManager;
class ComponentBace;
class GameObject : public cc::Ref, public GameMessageHandler {
    
    friend class GameObjectManager;
    
    typedef std::vector<cc::RefPtr<ComponentBace>> ComVecType;
    
    struct CompareById {
        bool operator()(const GameObject* lhs, const GameObject* rhs) const {
            return lhs->getID() < lhs->getID();
        }
    };
    
public:
    
    virtual ~GameObject()   final;
    
    const long              getID() const { return _id; }
    
    const std::string&      getName() const;
    
    bool                    setName(const std::string& name);
    
    const TagSet::TagBit&   getTagBits() const { return _tagBits; }
    
    void                    setTagBits(const TagSet::TagBit& tb) { _tagBits = tb; }
    
    template<class ReturnType>
    ReturnType*             getComponent(const std::string& name) const {
        static_assert(std::is_convertible<ReturnType*, ComponentBace*>::value, "Invalid Type");
        if (_components) {
            auto it = findComByName(name);
            if (it != _components->end()) {
                return dynamic_cast<ReturnType*>(it->get());
            }
        }
        return nullptr;
    }
    
    void                    addComponent(ComponentBace* com, const std::string& name = "");
    
    void                    removeComponent(const std::string& name);
    
    void                    removeAllComponents();
    
    void                    sendMessage(const GameMessage& msg);
    
    void                    sendMessage(const GAME_MSG msg, long nParam = 0, void* pParam = nullptr, GameObject* objParam = nullptr);
    
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
    virtual void            destroy();
    
protected:
    
    GameObject();
    
    static GameObject*      create(const std::string& name = constants::EmptyString);
    
    
    virtual void            update(float dt);
    
    virtual void            onMessage(const GameMessage& msg) override;
    
    long                    _id;
    
    static long             _nextValidId;
    
    std::string*            _name;
    
    GameWorld*              _world;
    
    TagSet::TagBit          _tagBits;
    
    LifeState               _lifeState = LifeState::Sleep;
    
    ComVecType*             _components = nullptr;
    
    ComVecType::iterator    findComByType(const std::type_info& type) const;
    
    ComVecType::iterator    findComByName(const std::string& name) const;
    
    void                    removeComponentIterator(ComVecType::iterator it);
};

#endif
