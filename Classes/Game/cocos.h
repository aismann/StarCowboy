
#ifndef __Cocos_h__
#define __Cocos_h__

#include "cocos2d.h"

namespace cc = cocos2d;

inline const cc::Vec2 truncate(const cc::Vec2& vec, float len) {
    if (vec.getLengthSq() > len * len) {
        return vec.getNormalized() * len;
    }
    return vec;
}

inline const bool longer(const cc::Vec2& vec, float len) {
    return vec.getLengthSq() > len * len;
}

#define PLATFORM_IS_PC (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)


#define CREATE_SPRITE(name) cc::Sprite::create(name)
//#define CREATE_SPRITE(name) cc::Sprite::createWithSpriteFrameName(name)

#endif
