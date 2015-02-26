
#ifndef __ComEntity_h__
#define __ComEntity_h__

#include "Component.h"

class ComEntity : public ComponentBace
{
public:
    
    ComEntity*    setLocation(const cc::Vec2& location)  {
        _location = location;
        return this;
    }
    
    const cc::Vec2& getLocation() const {
        return _location;
    }
    
protected:
    
    cc::Vec2    _location;
};

#endif
