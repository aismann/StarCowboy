
#include "ComAiEnemyController.h"
#include "ComPhysicsEntity.h"
#include "ComEngine.h"
#include "ComWeaponSystem.h"
#include "GameWorld.h"
#include "GameObjectManager.h"
#include "ComPhysicsEntity.h"

void ComAiEnemyController::onLoad() {
    _enemyMask = TagSet::getBit("enemy");
}

void ComAiEnemyController::onUnload() {
    
}

void ComAiEnemyController::start() {
    
    _entity = getOwner()->getComponent<ComPhysicsEntity>("physics_entity");
    _engine = getOwner()->getComponent<ComEngine>("engine");
    _weapon = getOwner()->getComponent<ComWeaponSystem>("weapon");
    _player = GameWorld::getInstance()->getObjectManager()->getObjectHandle("player");
    GameObject *player = _player.get();
    if (player) {
        _playerEntity = player->getComponent<ComPhysicsEntity>("physics_entity");
    }
}

void ComAiEnemyController::update(float dt) {
    GameObject *player = _player.get();
    if (player && player->isActive()) {
        cc::Vec2 dis2palyer = _playerEntity->getLocation() - _entity->getLocation();
        float distance = dis2palyer.length();
        if (_engine) {
            cc::Vec2 vMove = {0, 0};
            if (distance > 50) {
                vMove += dis2palyer;
                vMove -= _entity->getVelocity().getNormalized();
                vMove.normalize();
            }
            GameWorld::getInstance()->getObjectManager()->enumerateObject(_enemyMask, [&](GameObject* obj){
                if (obj->isActive() && obj != getOwner()) {
                    cc::Vec2 dis2enemy = obj->getComponent<ComPhysicsEntity>("physics_entity")->getLocation() - _entity->getLocation();
                    if (dis2enemy.length() < 20) {
                        dis2enemy.normalize();
                        vMove -= dis2enemy;
                    }
                }
            });
            _engine->setDirection(vMove);
        }
        
        if (_weapon) {
            _weapon->setAim(dis2palyer);
            if (distance < 100) {
                _weapon->startFire();
            } else {
                _weapon->endFire();
            }
        }
    } else {
        _player.reset();
        _playerEntity = nullptr;
        _weapon->endFire();
        _engine->setDirection({0, 0});
    }
}
