
#include "ComWeaponSystem.h"
#include "ComShipBody.h"
#include "MathUtils.h"
#include "GameObjectManager.h"
#include "ComPhysicsEntity.h"
#include "ComLifeTimeLimit.h"
#include "ComPhysicsNote.h"
#include "ComBullet.h"

ComWeaponSystem::ComWeaponSystem()
:_node(nullptr){
    
    _node = cc::Node::create();
    cc::Sprite* sp = cc::Sprite::create("weapon.png");
    _node->addChild(sp);
}

void ComWeaponSystem::start() {
    
    _body = getOwner()->getComponent<ComShipBody>("body");
    _body->getNode()->addChild(_node);
    cc::Size sz = _body->getNode()->getContentSize();
    _node->setPosition(cc::Vec2(sz.width * 0.5, sz.height * 0.5));
}

void ComWeaponSystem::update(float dt) {
    
    if (_aim.lengthSquared() > 0.01) {
        _node->setRotation(-math::radian2Angle(_aim.getAngle()) - _body->getNode()->getRotation());
    }
    
    if (_isFire && _coolDownTimer >= _coolDown) {
        fireOnce();
    }
    _coolDownTimer += dt;
}

void ComWeaponSystem::fireOnce() {
    
    float errorAngle = math::angle2Radian(cc::random<float>(-_errorAngle, _errorAngle));
    cc::Vec2 shootAim = _aim.rotateByAngle(cc::Vec2::ZERO, errorAngle);
    shootAim.normalize();
    
    GameObject* bullet = getWorld()->getObjectManager()->createObject();
    bullet->setTagBits(TagSet::getBit("bullet") | TagSet::getBit("physics_entity"));
    bullet->addComponent(ComBullet::create(1, cc::Sprite::create("bullet.png")));
    ComPhysicsEntity *physics = ComPhysicsEntity::create(1, 1, 0.004);
    physics->setCollisionResistance(0.25);
    ComPhysicsEntity *ship = getOwner()->getComponent<ComPhysicsEntity>("physics_entity");
    physics->setLocation(ship->getLocation() + shootAim * (ship->getRadius() + physics->getRadius() + 1));
    physics->setVelocity(ship->getVelocity() + shootAim * 200);
    bullet->addComponent(physics, "physics_entity");
    bullet->addComponent(ComLifeTimeLimit::create(5.f));
    bullet->awake();
    
    _coolDownTimer = 0;
}
