#ifndef __Constant_h__
#define __Constant_h__

#include <string>

namespace constants {
    
    static const float Ptm = 4.8f;   //how many points per meter

    static const float DefaultSlidingResistanceFactor = 0.5f;
    
    static const float DefaultAirResistanceFactor = 0.05f;
    
    static const float DefaultCollisionResistanceFactor = 0.5f;
    
    static const float DefaultGravity = 9.8f;
    
    static const float Pi = 3.14159f;
    
    static const float MinDistance = 0.01;
    
    static const float MaxMass = 1000000000;
    
    static const std::string EmptyString = "";
}

#endif