
#ifndef __ComAiEnemyController_h__
#define __ComAiEnemyController_h__

#include "Component.h"
#include "GameObjectHandle.h"

class ComWeaponSystem;
class ComEngine;
class ComPhysicsEntity;
class ComAiEnemyController : public ComponentBace {
    
    ComAiEnemyController() {}
    
public:
    
    static ComAiEnemyController *create() {
        ComAiEnemyController *com = New(ComAiEnemyController);
        return com;
    }
    
protected:
    
    virtual void onLoad() override;
    virtual void onUnload() override;
    
    virtual void start() override;
    virtual void update(float dt) override;
    
    ComPhysicsEntity*           _entity = nullptr;
    ComWeaponSystem*            _weapon = nullptr;
    ComEngine*                  _engine = nullptr;
    
    GameObjectHandle            _player;
    ComPhysicsEntity*           _playerEntity = nullptr;
    
    Tag::Bit              _enemyMask;
};

#endif
