#include "Joystick.h"

Joystick::Joystick() {
}

Joystick::~Joystick() {
}

Joystick* Joystick::create(cc::Sprite* bg, cc::Sprite* button) {
    Joystick *ret = new Joystick();
    if (ret && ret->init(bg, button))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        ret = nullptr;
        return ret;
    }
}

bool Joystick::init(cc::Sprite* bg, cc::Sprite* button) {
    bool bRet = false;
	do {
        CC_BREAK_IF(!cc::Node::init());
        
        setAnchorPoint({0.5, 0.5});
        
        _spBg = bg;
        _spButton = button;
        
        if (_spBg) {
            addChild(_spBg);
        }
        
        if (_spButton) {
            addChild(_spButton);
        }
        
#if !PLATFORM_IS_PC
        auto dispatcher = cc::Director::getInstance()->getEventDispatcher();
        auto listener = cc::EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(Joystick::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Joystick::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Joystick::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(Joystick::onTouchCancelled, this);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
        
        scheduleUpdate();
        
		bRet = true;
	} while (0);
	return bRet;
}


const cc::Point& Joystick::getOutputVec() const {
    return _output;
}


void Joystick::setOutputVec(const cc::Vec2& value) {
    _output = truncate(value, 1);
}

bool Joystick::onTouchBegan(cc::Touch *touch, cc::Event *event) {
    
    cc::Vec2 offset = touch->getLocation() - getPosition();
    float len = offset.getLength();
    
    if (len > _radius) {
        return false;
    }
    _isTouched = true;
    
    _output = offset.getNormalized();
    _output *= len / _radius;
    _output = truncate(_output, 1);
    return true;
}

void Joystick::onTouchMoved(cc::Touch *touch, cc::Event *event) {
    
    cc::Vec2 offset = touch->getLocation() - getPosition();
    _output = offset.getNormalized();
    _output *= offset.getLength() / _radius;
    _output = truncate(_output, 1);
}

void Joystick::onTouchEnded(cc::Touch *touch, cc::Event *event) {
    _isTouched = false;
    _output.set(0, 0);
}

void Joystick::onTouchCancelled(cc::Touch *touch, cc::Event *event) {
    
    _isTouched = false;
    _output.set(0, 0);
}

void Joystick::update(float dt) {
    if (_spButton) {
        _spButton->setPosition(_output * _radius);
    }
}


