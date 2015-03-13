
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
        
        auto menuItem0 = cc::MenuItemImage::create("CloseNormal.png", "CloseSelected.png");
        menuItem0->setPosition(joystickRight->getPosition() + cc::Vec2(-50, 150));
        menuItem0->setName("weapon_button_0");
        
        auto menuItem1 = cc::MenuItemImage::create("CloseNormal.png", "CloseSelected.png");
        menuItem1->setPosition(joystickRight->getPosition() + cc::Vec2(0, 150));
        menuItem1->setName("weapon_button_1");
        
        auto menuItem2 = cc::MenuItemImage::create("CloseNormal.png", "CloseSelected.png");
        menuItem2->setPosition(joystickRight->getPosition() + cc::Vec2(50, 150));
        menuItem2->setName("weapon_button_2");
        
        auto menu = cc::Menu::create(menuItem0, menuItem1, menuItem2, NULL);
        menu->setPosition(cc::Vec2::ZERO);
        menu->setName("menu");
        addChild(menu);
        
        ret = true;
    } while (0);
    return ret;
}