//
//  GameObjectFactory.cpp
//  StarCowboy
//
//  Created by match5 on 15/4/22.
//
//

#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "ComPhysicsEntity.h"
#include "ComPhysicsNote.h"


GameObject* GameObjectFactory::createRandomRock(const cc::Vec2 location)
{
    char name[16] = "";
    sprintf(name, "rock%d.png", cc::random(0, 2));
    cc::Sprite *sp = cc::Sprite::create(name);
    GameObject* rock = GameObjectManager::getInstance()->createObject().get();
    rock->setTagBits(Tag::get("rock").bit() | Tag::get("physics_entity").bit());
    rock->addComponent(ComPhysicsEntity::create(3, 1000)
                       ->setCollisionResistance(0.5)
                       ->setVelocity(cc::Vec2(cc::random(-5.f, 5.f), cc::random(-5.f, 5.f)))
                       ->setLocation(location), "entity");
    rock->addComponent(ComPhysicsNote::create(sp));
    sp->runAction(cc::RepeatForever::create(cc::RotateBy::create(1, cc::random(-90.f, 90.f))));
    return rock;
}