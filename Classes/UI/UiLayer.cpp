
#include "UiLayer.h"
#include "Joystick.h"
#include "Radar.h"

bool UiLayer::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!cc::Layer::init());
        
        cc::Vec2 origin = cc::Director::getInstance()->getVisibleOrigin();
        cc::Size size = cc::Director::getInstance()->getVisibleSize();
        
        auto joystickLeft = Joystick::create(cc::Sprite::create("joystick_bg.png"), cc::Sprite::create("joystick_button.png"));
        joystickLeft->setPosition(origin + cc::Vec2(125, 125));
        joystickLeft->setName("left_joystick");
        addChild(joystickLeft);
        
        auto joystickRight = Joystick::create(cc::Sprite::create("joystick_bg.png"), cc::Sprite::create("joystick_button.png"));
        joystickRight->setPosition(origin + cc::Vec2(size.width - 125, 125));
        joystickRight->setName("right_joystick");
        addChild(joystickRight);
        
        auto weapon0 = cc::MenuItemImage::create("CloseNormal.png", "CloseSelected.png");
        weapon0->setPosition(joystickRight->getPosition() + cc::Vec2(-50, 150));
        weapon0->setName("weapon_button_0");
        
        auto weapon1 = cc::MenuItemImage::create("CloseNormal.png", "CloseSelected.png");
        weapon1->setPosition(joystickRight->getPosition() + cc::Vec2(0, 150));
        weapon1->setName("weapon_button_1");
        
        auto weapon2 = cc::MenuItemImage::create("CloseNormal.png", "CloseSelected.png");
        weapon2->setPosition(joystickRight->getPosition() + cc::Vec2(50, 150));
        weapon2->setName("weapon_button_2");
        
        auto radar = cc::MenuItemImage::create("CloseNormal.png", "CloseSelected.png");
        radar->setPosition(joystickLeft->getPosition() + cc::Vec2(-50, 150));
        radar->setName("radar_button");
        radar->setCallback(CC_CALLBACK_1(UiLayer::onRadarButtonClicked, this));
        
        auto menu = cc::Menu::create(weapon0, weapon1, weapon2, radar, NULL);
        menu->setPosition(cc::Vec2::ZERO);
        menu->setName("menu");
        addChild(menu);
        
        ret = true;
    } while (0);
    return ret;
}

void UiLayer::onRadarButtonClicked(cc::Ref*)
{
    if (!_radar) {
        cc::Vec2 origin = cc::Director::getInstance()->getVisibleOrigin();
        cc::Size size = cc::Director::getInstance()->getVisibleSize();
        _radar = Radar::create();
        _radar->setPosition(origin + size / 2);
    }
    if (_radar->getParent()) {
        _radar->unscheduleUpdate();
        _radar->removeFromParent();
    } else {
        addChild(_radar);
        _radar->scheduleUpdate();
    }
}
