
#include "ComShipController.h"
#include "MathUtils.h"

#include "ComShipBody.h"
#include "ComPhysicsEntity.h"
#include "ComEngine.h"
#include "ComWeaponSystem.h"

#include "Joystick.h"

void ComShipController::onLoad() {
    
    _gameLayer = getOwner()->getWorld()->getGameLayer();
    _uiLayer = getOwner()->getWorld()->getUiLayer();
    _eventDispatcher = cc::Director::getInstance()->getEventDispatcher();
    
#if PLATFORM_IS_PC
    _keyboardListener = cc::EventListenerKeyboard::create();
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(ComShipController::onKeyPressed, this);
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(ComShipController::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, _uiLayer);
    
    _mouseListener = cc::EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(ComShipController::onMouseMove, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(ComShipController::onMouseDown, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(ComShipController::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, _uiLayer);
#endif
    
    _joystickLeft = static_cast<Joystick*>(getWorld()->getUiLayer()->getChildByName("left_joystick"));
    _joystickRight = static_cast<Joystick*>(getWorld()->getUiLayer()->getChildByName("right_joystick"));
    
    auto menu = static_cast<cc::Menu*>(getWorld()->getInstance()->getUiLayer()->getChildByName("menu"));
    auto weaponButton0 = static_cast<cc::MenuItem*>(menu->getChildByName("weapon_button_0"));
    weaponButton0->setCallback(std::bind(&ComShipController::onWeaponButtonClicked, this, 0, std::placeholders::_1));
    auto weaponButton1 = static_cast<cc::MenuItem*>(menu->getChildByName("weapon_button_1"));
    weaponButton1->setCallback(std::bind(&ComShipController::onWeaponButtonClicked, this, 1, std::placeholders::_1));
    auto weaponButton2 = static_cast<cc::MenuItem*>(menu->getChildByName("weapon_button_2"));
    weaponButton2->setCallback(std::bind(&ComShipController::onWeaponButtonClicked, this, 2, std::placeholders::_1));
}

void ComShipController::onUnload() {
    
    _eventDispatcher->removeEventListener(_keyboardListener);
    _eventDispatcher->removeEventListener(_mouseListener);
    
    auto menu = static_cast<cc::Menu*>(getWorld()->getInstance()->getUiLayer()->getChildByName("menu"));
    auto weaponButton0 = static_cast<cc::MenuItem*>(menu->getChildByName("weapon_button_0"));
    weaponButton0->setCallback(nullptr);
    auto weaponButton1 = static_cast<cc::MenuItem*>(menu->getChildByName("weapon_button_1"));
    weaponButton1->setCallback(nullptr);
    auto weaponButton2 = static_cast<cc::MenuItem*>(menu->getChildByName("weapon_button_2"));
    weaponButton2->setCallback(nullptr);
}

void ComShipController::start() {
    
    _body = getOwner()->getComponent<ComShipBody>("body");
    _gameLayer->runAction(cc::Follow::create(_body->getNode()));
    
    _engine = getOwner()->getComponent<ComEngine>("engine");
    _weapon = getOwner()->getComponent<ComWeaponSystem>("weapon");
}

void ComShipController::update(float dt) {
    
#if PLATFORM_IS_PC
    if (_engine) {
        _vMove = _keyboardOutput;
        _joystickLeft->setOutputVec(_keyboardOutput);
        _engine->setDirection(_vMove);
    }
    
    if (_weapon) {
        _vAim = _mouseOutput;
        _joystickRight->setOutputVec(_mouseOutput);
        _weapon->setAim(_vAim);
    }
#else
    if (_engine) {;
        _vMove = _joystickLeft->getOutputVec();
        _engine->setDirection(_vMove);
    }
    
    if (_weapon) {
        _vAim = _joystickRight->getOutputVec();
        _weapon->setAim(_vAim);
        if (_vAim.lengthSquared() > 0) {
            _weapon->startFire();
        } else {
            _weapon->endFire();
        }
    }
#endif
}
void ComShipController::onKeyPressed(cc::EventKeyboard::KeyCode code, cc::Event*) {
    
    switch (code) {
        case cc::EventKeyboard::KeyCode::KEY_W:
            _keyboardOutput += {0, 1};
            break;
        case cc::EventKeyboard::KeyCode::KEY_A:
            _keyboardOutput += {-1, 0};
            break;
        case cc::EventKeyboard::KeyCode::KEY_S:
            _keyboardOutput += {0, -1};
            break;
        case cc::EventKeyboard::KeyCode::KEY_D:
            _keyboardOutput += {1, 0};
            break;
            
        default:
            break;
    }
}

void ComShipController::onKeyReleased(cc::EventKeyboard::KeyCode code, cc::Event*) {
    
    switch (code) {
        case cc::EventKeyboard::KeyCode::KEY_W:
            _keyboardOutput -= {0, 1};
            break;
        case cc::EventKeyboard::KeyCode::KEY_A:
            _keyboardOutput -= {-1, 0};
            break;
        case cc::EventKeyboard::KeyCode::KEY_S:
            _keyboardOutput -= {0, -1};
            break;
        case cc::EventKeyboard::KeyCode::KEY_D:
            _keyboardOutput -= {1, 0};
            break;
        case cc::EventKeyboard::KeyCode::KEY_1:
            _weapon->switchWeapon(0);
            break;
        case cc::EventKeyboard::KeyCode::KEY_2:
            _weapon->switchWeapon(1);
            break;
        case cc::EventKeyboard::KeyCode::KEY_3:
            _weapon->switchWeapon(2);
            break;
            
        default:
            break;
    }
}

void ComShipController::onMouseMove(cc::Event* event) {

    if (_body) {
        cc::EventMouse* em = static_cast<cc::EventMouse*>(event);
        cc::Vec2 origin = cc::Director::getInstance()->getVisibleOrigin();
        float scaleX = cc::Director::getInstance()->getOpenGLView()->getScaleX();
        float scaleY = cc::Director::getInstance()->getOpenGLView()->getScaleY();
        cc::Vec2 cursorInView = {em->getCursorX() / scaleX - origin.x, em->getCursorY() / scaleY - origin.y};
        cc::Vec2 cursorInNode = _gameLayer->convertToNodeSpace(cursorInView);
        _mouseOutput = cursorInNode - _body->getNode()->getPosition();
    }
}

void ComShipController::onMouseDown(cc::Event* event) {
    
    _weapon->startFire();
}

void ComShipController::onMouseUp(cc::Event* event) {
    
    _weapon->endFire();
}

void ComShipController::onWeaponButtonClicked(int index, cc::Ref*) {
    _weapon->switchWeapon(index);
}
