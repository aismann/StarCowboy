
#include "ComParticleEmiter.h"
#include "ComPhysicsEntity.h"

void ComParticleEmiter::onLoad() {
    getOwner()->getWorld()->getGameBackground()->addChild(_emiter);
}

void ComParticleEmiter::onUnload() {
    _emiter->removeFromParent();
}

void ComParticleEmiter::start() {
    _entity = getOwner()->getComponent<ComEntity>("entity");
}

void ComParticleEmiter::update(float dt) {
    
    if (_entity) {
        _emiter->setPosition(_entity->getLocation() * constants::Ptm);
    }
}
