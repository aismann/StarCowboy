//
//  Radar.cpp
//  StarCowboy
//
//  Created by match5 on 15/8/5.
//
//

#include "Radar.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ComPhysicsEntity.h"

Radar* Radar::create()
{
    Radar *ret = new Radar();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        ret = nullptr;
        return ret;
    }
}

bool Radar::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!cc::Node::init());
        
        setAnchorPoint({0.5, 0.5});
        
        _drawNode = cc::DrawNode::create();
        CC_BREAK_IF(!_drawNode);
        _drawNode->setAnchorPoint({0.5, 0.5});
        addChild(_drawNode);
        
        _maskEnemy = Tag::getBit("enemy");
        _maskRock = Tag::getBit("rock");
        _mask = _maskEnemy | _maskRock;
        
        bRet = true;
    } while (0);
    return bRet;
}

void Radar::update(float dt)
{
    ComEntity* entity = nullptr;
    if (!_player) {
        _player = GameWorld::getInstance()->getObjectManager()->getObjectHandle("player");
    }
    if (_player && _player.get()->isActive()) {
        ComEntity* playerEntity = _player.get()->getComponent<ComEntity>("entity");
        if (playerEntity) {
            _drawNode->clear();
            float factor = constants::Ptm * _zoom;
            _drawNode->drawCircle({0, 0}, 100 * factor, 360, 32, false, 1, 1, {0.2, 0.2, 0.2, 0.5});
            _drawNode->drawCircle({0, 0}, 200 * factor, 360, 32, false, 1, 1, {0.2, 0.2, 0.2, 0.5});
            _drawNode->drawCircle({0, 0}, 300 * factor, 360, 64, false, 1, 1, {0.2, 0.2, 0.2, 0.5});
            _drawNode->drawCircle({0, 0}, 400 * factor, 360, 64, false, 1, 1, {0.2, 0.2, 0.2, 0.5});
            _drawNode->drawCircle({0, 0}, 500 * factor, 360, 96, false, 1, 1, {0.4, 0.4, 0.4, 0.5});
            GameWorld::getInstance()->getObjectManager()->enumerateObject(_mask, [&](GameObject* obj) {
                if (obj->isActive()) {
                    entity = obj->getComponent<ComEntity>("entity");
                    if (entity) {
                        cc::Vec2 pos = (entity->getLocation() - playerEntity->getLocation());
                        if ((obj->getTagBits() & _maskEnemy).any()) {
                            pos = truncate(pos, 500);
                            _drawNode->drawDot(pos * factor, 2, {1, 0, 0, 1});
                        } else if ((obj->getTagBits() & _maskRock).any()) {
                            if (!longer(pos, 500)) {
                                _drawNode->drawDot(pos * factor, 2, {0.4, 0.4, 0.4, 0.5});
                            }
                        }
                    }
                }
            });
        }
    }
}
