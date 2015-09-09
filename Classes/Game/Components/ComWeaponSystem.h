
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
    
    virtual ~ComWeaponSystem() override;
    
    static ComWeaponSystem*  create() {
        ComWeaponSystem *com = New(ComWeaponSystem);
        return com;
    }
    
    ComWeaponSystem* addWeapon(Weapon* weapon);
    
    ComWeaponSystem* setAim(const cc::Vec2& at) {
        _aim = at;
        return this;
    }
    
    ComWeaponSystem* setTargetMask(const Tag::Bit& mask) {
        _targetMask = mask;
        return this;
    }
    
    void switchWeapon(int index) {
        if (0 <= index && index < _weapens.size()) {
            _currentWeapen = _weapens.at(index);
        }
    }
    
    void switchToNext() {
        if (!_weapens.empty()) {
            auto it = std::find(_weapens.begin(), _weapens.end(), _currentWeapen);
            if (it != _weapens.end() && ++it != _weapens.end()) {
                _currentWeapen = *it;
                return;
            }
            _currentWeapen = *_weapens.begin();
        }
    }
    
    void startFire();
    void endFire();
    
protected:
    
    virtual void start() override;
    
    virtual void update(float dt) override;
    virtual void onUnload() override;

    cc::RefPtr<cc::Node>    _node = nullptr;
    
    ComShipBody*            _body = nullptr;
    
    ComPhysicsEntity*       _shipEntity = nullptr;
    
    cc::Vec2                _aim = {1, 0};
    
    bool                    _isFire = false;
    
    std::vector<Weapon*>    _weapens;
    Weapon*                 _currentWeapen = nullptr;
    
    Tag::Bit          _targetMask;
    
};

#endif
