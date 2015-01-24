
#include "UiLayer.h"
#include "Joystick.h"

bool UiLayer::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!cc::Layer::init());
        
        cc::Vec2 origin = cc::Director::getInstance()->getVisibleOrigin();
        cc::Size size = cc::Director::getInstance()->getVisibleSize();
        
        auto joystickLeft = Joystick::create(cc::Sprite::create("joystick_bg.png"), cc::Sprite::create("joystick_button.png"));
        joystickLeft->setPosition(cc::Director::getInstance()->getVisibleOrigin() + cc::Vec2(125, 125));
        joystickLeft->setName("left_joystick");
        addChild(joystickLeft);
        
        auto joystickRight = Joystick::create(cc::Sprite::create("joystick_bg.png"), cc::Sprite::create("joystick_button.png"));
        joystickRight->setPosition(origin + cc::Vec2(size.width - 125, 125));
        joystickRight->setName("right_joystick");
        addChild(joystickRight);
        
        ret = true;
    } while (0);
    return ret;
}