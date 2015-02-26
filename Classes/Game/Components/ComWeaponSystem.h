
#ifndef __ComWeaponSystem_h__
#define __ComWeaponSystem_h__

#include "Component.h"
#include <vector>

class ComShipBody;
class ComPhysicsEntity;
class Weapon;
class ComWeaponSystem : public ComponentBace {
    
    ComWeaponSystem();
    
public:
    
    virtual ~ComWeaponSystem() override {}
    
    static ComWeaponSystem*  create() {
        ComWeaponSystem *com = new ComWeaponSystem;
        com->autorelease();
        return com;
    }
    
    ComWeaponSystem* addWeapon(Weapon* weapon);
    
    ComWeaponSystem* setAim(const cc::Vec2& at) {
        _aim = at;
        return this;
    }
    
    ComWeaponSystem* setTargetMask(const TagSet::TagBit& mask) {
        _targetMask = mask;
        return this;
    }
    
    void startFire() {
        _isFire = true;
    }
    void endFire() {
        _isFire = false;
    }
    
protected:
    
    virtual void start() override;
    
    virtual void update(float dt) override;

    cc::RefPtr<cc::Node>    _node = nullptr;
    
    ComShipBody*            _body = nullptr;
    
    ComPhysicsEntity*       _shipEntity = nullptr;
    
    cc::Vec2                _aim = {1, 0};
    
    bool                    _isFire = false;
    
    std::vector<cc::RefPtr<Weapon>> _weapens;
    Weapon*                         _currentWeapen = nullptr;
    
    TagSet::TagBit          _targetMask;
    
};

#endif
