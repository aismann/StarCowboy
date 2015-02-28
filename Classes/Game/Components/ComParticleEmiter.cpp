
#include "ComParticleEmiter.h"
#include "ComPhysicsEntity.h"

void ComParticleEmiter::onLoad() {
    getOwner()->getWorld()->getGameBackground()->addChild(_emiter);
}

void ComParticleEmiter::onUnload() {
    getOwner()->getWorld()->getGameBackground()->removeChild(_emiter);
}

void ComParticleEmiter::start() {
    _entity = getOwner()->getComponent<ComEntity>("entity");
    if (!_entity) {
        _entity = getOwner()->getComponent<ComPhysicsEntity>("physics_entity");
    }
}

void ComParticleEmiter::update(float dt) {
    
    if (_entity) {
        _emiter->setPosition(_entity->getLocation() * constants::Ptm);
    }
}
