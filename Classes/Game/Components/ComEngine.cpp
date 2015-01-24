
#include "ComEngine.h"
#include "ComPhysicsEntity.h"

void ComEngine::start() {
    
    _entity = getOwner()->getComponent<ComPhysicsEntity>("physics_entity");
}

void ComEngine::update(float dt) {
    
    _force.set(0, 0);
    if (_direction.lengthSquared() > 0.01) {
        _direction.normalize();
        cc::Vec2 v = _entity->getVelocity().project(_direction);
        
        if (1 + v.length() > (_direction + v).length()) {
            _force = _maxForce * _direction;
        } else {
            _force = _direction * ((_maxSpeed - v.length()) / _maxSpeed) *_maxForce;
        }
        _entity->appliedInstantaneousForce(_force);
    }
}