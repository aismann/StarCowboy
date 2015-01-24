
#ifndef __ComWeaponSystem_h__
#define __ComWeaponSystem_h__

#include "Component.h"

class ComShipBody;
class ComWeaponSystem : public ComponentBace {
    
    ComWeaponSystem();
    
public:
    
    virtual ~ComWeaponSystem() override {}
    
    static ComWeaponSystem*  create() {
        ComWeaponSystem *com = new ComWeaponSystem;
        com->autorelease();
        return com;
    }
    
    ComWeaponSystem* setAim(const cc::Vec2& at) {
        _aim = at;
        return this;
    }
    
    ComWeaponSystem*  setCoolDown(float cd) {
        _coolDown = cd;
        return this;
    }
    
    ComWeaponSystem* setErrorAngle(float angle) {
        _errorAngle = angle;
        return this;
    }
    
    void startFire() {
        _isFire = true;
    }
    void endFire() {
        _isFire = false;
    }
    
    void fireOnce();
    
    
protected:
    
    virtual void start() override;
    
    virtual void update(float dt) override;

    cc::RefPtr<cc::Node>    _node = nullptr;
    
    ComShipBody*            _body = nullptr;
    
    cc::Vec2                _aim = {1, 0};
    
    bool                    _isFire = false;
    
    float                   _coolDown = 0.5;
    float                   _coolDownTimer = 0;
    
    float                   _errorAngle = 0;
};

#endif
