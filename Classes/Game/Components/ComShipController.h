
#ifndef __ComShipController_h__
#define __ComShipController_h__

#include "Component.h"

class ComShipBody;
class ComEngine;
class ComWeaponSystem;
class Joystick;
class ComShipController : public ComponentBace {
    
    ComShipController() {}
    
public:
    
    virtual ~ComShipController() override {}
    
    static ComShipController*  create() {
        ComShipController *com = new ComShipController;
        com->autorelease();
        return com;
    }
    
protected:
    
    virtual void onLoad() override;
    virtual void onUnload() override;
    
    virtual void start() override;
    virtual void update(float dt) override;
    
    void onKeyPressed(cc::EventKeyboard::KeyCode code, cc::Event*);
    void onKeyReleased(cc::EventKeyboard::KeyCode code, cc::Event*);
    
    void onMouseMove(cc::Event* event);
    void onMouseDown(cc::Event* event);
    void onMouseUp(cc::Event* event);
    
    void onWeaponButtonClicked(int index, cc::Ref*);
    
    cc::RefPtr<cc::EventDispatcher>        _eventDispatcher;
    cc::RefPtr<cc::EventListenerKeyboard>  _keyboardListener;
    cc::RefPtr<cc::EventListenerMouse>     _mouseListener;
    cc::Vec2                    _keyboardOutput;
    cc::Vec2                    _mouseOutput;
    
    cc::RefPtr<Joystick>        _joystickLeft;
    cc::RefPtr<Joystick>        _joystickRight;
    
    cc::Layer*                  _gameLayer = nullptr;
    cc::Layer*                  _uiLayer = nullptr;
    
    cc::Vec2                    _vMove;
    cc::Vec2                    _vAim;
    
    ComShipBody*                _body = nullptr;
    
    ComWeaponSystem*            _weapon = nullptr;
    
    ComEngine*                  _engine = nullptr;
};


#endif
