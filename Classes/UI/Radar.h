//
//  Radar.h
//  StarCowboy
//
//  Created by match5 on 15/8/5.
//
//

#ifndef __Radar_h__
#define __Radar_h__

#include "cocos.h"
#include "Tag.h"
#include "GameObject.h"

class Radar : public cc::Node
{
public:
    
    static Radar* create();
    bool init();
    
    
    virtual void update(float dt);
    
protected:
    
    float   _zoom = 0.1;
    
    cc::RefPtr<cc::DrawNode> _drawNode;
    Tag::Bit                _mask;
    Tag::Bit                _maskEnemy;
    Tag::Bit                _maskRock;
    
    GameObjectHandle        _player;
};

#endif
