//
//  GameObjectFactory.h
//  StarCowboy
//
//  Created by match5 on 15/4/22.
//
//

#ifndef __GameObjectFactory_h__
#define __GameObjectFactory_h__

#include "cocos.h"

class GameObject;

class GameObjectFactory
{
public:
    
    static GameObject* createRandomRock(const cc::Vec2 location);
};

#endif
