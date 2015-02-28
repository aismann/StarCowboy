#include "GameScene.h"
#include "GameWorld.h"
#include "GameObjectManager.h"

//fortest
#include "GameObject.h"
#include "ComShipBody.h"
#include "ComShipController.h"
#include "ComPhysicsEntity.h"
#include "ComEngine.h"
#include "ComWeaponSystem.h"
#include "ComParticleEmiter.h"
#include "ComAiEnemyController.h"
#include "ComHitPoint.h"
#include "Cannon.h"
#include "Laser.h"
#include "MissileLauncher.h"
//=======

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    addChild(GameWorld::getInstance()->getGameLayer());
    addChild(GameWorld::getInstance()->getUiLayer());
    
    GameObject *playerShip = GameWorld::getInstance()->getObjectManager()->createObject("player");
    playerShip->setTagBits(TagSet::getBit("player") | TagSet::getBit("physics_entity"));
    playerShip->addComponent(ComShipBody::create(Sprite::create("ship.png")), "body");
    playerShip->addComponent(ComParticleEmiter::create(cc::ParticleSystemQuad::create("particles/cosmic_particle.plist")));
    playerShip->addComponent(ComParticleEmiter::create(cc::ParticleSystemQuad::create("particles/particle_wake.plist")));
    playerShip->addComponent(ComShipController::create(), "controller");
    playerShip->addComponent(ComPhysicsEntity::create(5, 400), "physics_entity");
    playerShip->addComponent(ComEngine::create(25000, 50), "engine");
    playerShip->addComponent(ComWeaponSystem::create()->setTargetMask(TagSet::getBit("enemy"))
                             ->addWeapon(Cannon::create()
                                         ->setDamage(40)
                                         ->setCoolDown(0.15f)
                                         ->setRange(200)
                                         ->setErrorAngle(2.5)
                                         ->addHitTestMask(TagSet::getBit("rock")))
                             ->addWeapon(MissileLauncher::create()
                                         ->setDamage(50)
                                         ->setMaxAmmoNum(4)
                                         ->setMissileSpeed(100)
                                         ->setCoolDown(0.25)
                                         ->setSearchAngular(60)
                                         ->setAngularSpeed(180)
                                         ->addHitTestMask(TagSet::getBit("rock")))
                             ->addWeapon(Laser::create(Sprite::create("bullet.png"))
                                         ->setDPS(200)
                                         ->addHitTestMask(TagSet::getBit("rock")))
, "weapon");
    playerShip->addComponent(ComHitPoint::create(200));
    playerShip->awake();
    
    int maxEnemyNum = 10;
    int waveEnemyNum = 5;
    std::function<void(float)> addEnemy = [=](float){
        GameObject *player = GameWorld::getInstance()->getObjectManager()->getObject("player");
        if (player == nullptr || !player->isActive()) {
            this->unschedule("add_enemy");
            return;
        }
        int num = 0;
        GameWorld::getInstance()->getObjectManager()->enumerateObject(TagSet::getBit("enemy"), [&num](GameObject*){
            ++num;
        });
        num = std::min(maxEnemyNum - num, waveEnemyNum);
        for (int i = 0; i < num; ++i) {
            GameObject *enemy = GameWorld::getInstance()->getObjectManager()->createObject();
            enemy->setTagBits(TagSet::getBit("enemy") | TagSet::getBit("physics_entity"));
            enemy->addComponent(ComShipBody::create(Sprite::create("enemy.png")), "body");
            enemy->addComponent(ComParticleEmiter::create(cc::ParticleSystemQuad::create("particles/particle_wake.plist")));
            enemy->addComponent(ComPhysicsEntity::create(5, 200), "physics_entity");
            cc::Vec2 locate(random(-100, 100), random(-100, 100));
            enemy->getComponent<ComPhysicsEntity>("physics_entity")->setLocation(player->getComponent<ComPhysicsEntity>("physics_entity")->getLocation() + locate.getNormalized() * random(300, 500));
            enemy->addComponent(ComEngine::create(2000, 45), "engine");
            if (i == 0) {
                enemy->addComponent(ComWeaponSystem::create()->setTargetMask(TagSet::getBit("player"))
                                    ->addWeapon(MissileLauncher::create()
                                                ->setDamage(10)
                                                ->setMaxAmmoNum(2)
                                                ->setReloadTime(3)
                                                ->setMissileSpeed(75)
                                                ->setCoolDown(0.25)
                                                ->setSearchAngular(30)
                                                ->setAngularSpeed(90)
                                                ->addHitTestMask(TagSet::getBit("rock"))), "weapon");
            } else {
                enemy->addComponent(ComWeaponSystem::create()->setTargetMask(TagSet::getBit("player"))
                                    ->addWeapon(Cannon::create()
                                                ->setDamage(10)
                                                ->setCoolDown(1.0)
                                                ->setRange(150)
                                                ->setErrorAngle(2.5)
                                                ->addHitTestMask(TagSet::getBit("rock"))), "weapon");
            }
            
            enemy->addComponent(ComAiEnemyController::create());
            enemy->addComponent(ComHitPoint::create(100));
            enemy->awake();
        }
    };
    addEnemy(0);
    schedule(addEnemy, 10, "add_enemy");

    scheduleUpdate();
    return true;
}

void GameScene::update(float dt) {
    GameWorld::getInstance()->update(dt);
}
