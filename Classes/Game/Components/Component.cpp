
#include "Component.h"

ComponentBace::~ComponentBace() {
}

GameWorld* ComponentBace::getWorld() const {
    return _owner->getWorld();
}


void ComponentBace::doUpdate(float dt)
{
    if (_isStarted == false) {
        start();
        _isStarted = true;
    }
    
    if (_updateTimer.increase(dt)) {
        update(_updateTimer.getCurrent());
        _updateTimer.reset();
    }
}