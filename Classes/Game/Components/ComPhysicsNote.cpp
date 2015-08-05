
#include "ComPhysicsNote.h"
#include "ComPhysicsEntity.h"


void ComPhysicsNote::onLoad() {
}

void ComPhysicsNote::onUnload() {
    getOwner()->getWorld()->getGameForeground()->removeChild(_ndoe);
}

void ComPhysicsNote::start() {
    
    if (!_ndoe->getParent()) {
        getOwner()->getWorld()->getGameForeground()->addChild(_ndoe);
    }
    
    _entity = getOwner()->getComponent<ComPhysicsEntity>("entity");
    if (_entity) {
        _ndoe->setPosition(_entity->getLocation() * constants::Ptm);
    }
}

void ComPhysicsNote::update(float dt) {
    
    if (_entity) {
        _ndoe->setPosition(_entity->getLocation() * constants::Ptm);
    }
}