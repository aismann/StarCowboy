
#include "Component.h"

ComponentBace::~ComponentBace() {
}

GameWorld* ComponentBace::getWorld() const {
    return _owner->getWorld();
}