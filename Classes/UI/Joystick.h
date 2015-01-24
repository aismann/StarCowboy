#ifndef __UIWheel_h__
#define __UIWheel_h__

#include "cocos.h"

#include <functional>
using std::function;

class Joystick : public cc::Node
{
public:
    Joystick();
    virtual ~Joystick();
    
    virtual bool init(cc::Sprite* bg, cc::Sprite* button);
    
    static Joystick* create(cc::Sprite* bg, cc::Sprite* button);
    
    void setRadius(float radius);
    
    virtual bool onTouchBegan(cc::Touch *touch, cc::Event *event);
	virtual void onTouchMoved(cc::Touch *touch, cc::Event *event);
	virtual void onTouchEnded(cc::Touch *touch, cc::Event *event);
	virtual void onTouchCancelled(cc::Touch *touch, cc::Event *event);
    
    virtual void update(float dt);
    
    const cc::Vec2& getOutputVec() const;
    
    void setOutputVec(const cc::Vec2& value);
    
    const bool isTouched() const {
        return _isTouched;
    }
    
protected:
    
    cc::RefPtr<cc::Sprite> _spBg;
    cc::RefPtr<cc::Sprite> _spButton;
    
    cc::Vec2    _output;
    
    bool        _isTouched = false;
    
    float       _radius = 100;
};

#endif