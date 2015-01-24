#include "ComBullet.h"
#include "ComPhysicsEntity.h"

void ComBullet::onLoad() {
}

void ComBullet::onUnload() {
    getOwner()->getWorld()->getGameForeground()->removeChild(_ndoe);
}

void ComBullet::start() {
    
    if (!_ndoe->getParent()) {
        getOwner()->getWorld()->getGameForeground()->addChild(_ndoe);
    }
    
    _entity = getOwner()->getComponent<ComPhysicsEntity>("physics_entity");
    if (_entity) {
        _ndoe->setPosition(_entity->getLocation() * constants::Ptm);
    }
}

void ComBullet::update(float dt) {
    
    if (_entity) {
        _ndoe->setPosition(_entity->getLocation() * constants::Ptm);
    }
}
void ComBullet::onMessage(const GameMessage& msg)
{
    if (msg.id == GAME_MSG::ON_COLLISION_WITH) {
        msg.objParam->sendMessage(GAME_MSG::TAKE_DAMEGE, 1, nullptr, getOwner());
    }
}