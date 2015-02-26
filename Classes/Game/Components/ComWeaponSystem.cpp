
#include "ComWeaponSystem.h"
#include "ComShipBody.h"
#include "MathUtils.h"
#include "Weapon.h"
#include "ComPhysicsEntity.h"

ComWeaponSystem::ComWeaponSystem()
:_node(nullptr){
    
    _node = cc::Node::create();
    cc::Sprite* sp = cc::Sprite::create("weapon.png");
    _node->addChild(sp);
}

ComWeaponSystem* ComWeaponSystem::addWeapon(Weapon* weapon) {
    _weapens.push_back(weapon);
    if (!_currentWeapen) {
        _currentWeapen = weapon;
    }
    return this;
}

void ComWeaponSystem::start() {
    
    _body = getOwner()->getComponent<ComShipBody>("body");
    _body->getNode()->addChild(_node);
    cc::Size sz = _body->getNode()->getContentSize();
    _node->setPosition(cc::Vec2(sz.width * 0.5, sz.height * 0.5));
    
    _shipEntity = getOwner()->getComponent<ComPhysicsEntity>("physics_entity");
}

void ComWeaponSystem::update(float dt) {
    
    for (auto weapon : _weapens) {
        weapon->update(dt);
    }
    
    if (_aim.lengthSquared() > 0.01) {
        _node->setRotation(-math::radian2Angle(_aim.getAngle()) - _body->getNode()->getRotation());
    }
    
    if (_isFire && _currentWeapen && _shipEntity) {
        _currentWeapen->fire(_shipEntity->getLocation(), _aim, _shipEntity->getVelocity(), _targetMask);
    }
}
