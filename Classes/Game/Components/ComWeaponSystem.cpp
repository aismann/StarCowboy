
#include "ComWeaponSystem.h"
#include "ComShipBody.h"
#include "MathUtils.h"
#include "Weapon.h"
#include "ComPhysicsEntity.h"

ComWeaponSystem::ComWeaponSystem()
:_node(nullptr){
    
    _node = cc::Node::create();
//    cc::Sprite* sp = cc::Sprite::create("weapon.png");
//    _node->addChild(sp);
}

ComWeaponSystem::~ComWeaponSystem() {
    for (auto& w : _weapens) {
        DelEx(Weapon, w);
    }
    _weapens.clear();
}

ComWeaponSystem* ComWeaponSystem::addWeapon(Weapon* weapon) {
    _weapens.push_back(weapon);
    weapon->setTargetMask(_targetMask);
    if (!_currentWeapen) {
        _currentWeapen = weapon;
    }
    return this;
}

void ComWeaponSystem::onUnload() {
    if (_currentWeapen) {
        _currentWeapen->stopFire();
    }
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
        _currentWeapen->fire(_shipEntity->getLocation(), _aim, _shipEntity->getVelocity());
    }
}

void ComWeaponSystem::startFire() {
    _isFire = true;
}

void ComWeaponSystem::endFire() {
    if (_isFire) {
        _isFire = false;
        if (_currentWeapen) {
            _currentWeapen->stopFire();
        }
    }
}
