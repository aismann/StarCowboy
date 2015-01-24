
#ifndef __ComAiEnemyController_h__
#define __ComAiEnemyController_h__

#include "Component.h"

class ComWeaponSystem;
class ComEngine;
class ComPhysicsEntity;
class ComAiEnemyController : public ComponentBace {
    
    ComAiEnemyController() {}
    
public:
    
    static ComAiEnemyController *create() {
        ComAiEnemyController *com = new ComAiEnemyController;
        com->autorelease();
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
    
    cc::RefPtr<GameObject>      _player = nullptr;
    ComPhysicsEntity*           _playerEntity = nullptr;
    
    TagSet::TagBit              _enemyMask;
};

#endif
