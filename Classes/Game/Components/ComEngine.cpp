
#include "ComEngine.h"
#include "ComPhysicsEntity.h"

void ComEngine::start() {
    
    _entity = getOwner()->getComponent<ComPhysicsEntity>("entity");
}

void ComEngine::update(float dt) {
    
    _force.set(0, 0);
    if (_direction.lengthSquared() > 0.01) {
        _direction.normalize();
        
        cc::Vec2 v = _entity->getVelocity();
        
        if (v.length() < _maxSpeed) {
            _force = _maxForce * _direction;
        } else {
            _force = _maxForce * _direction;
            _force -= _force.project(v);
        }
        
        _entity->appliedInstantaneousForce(_force);
    }
}