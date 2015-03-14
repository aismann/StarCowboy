
#include "GameWorld.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GameMessageDispatcher.h"
#include "UiLayer.h"

GameWorld::GameWorld() {
    _foreground = cc::Node::create();
    _background = cc::Node::create();
    
    _gameLayer = cc::Layer::create();
    _gameLayer->addChild(_background);
    _gameLayer->addChild(_foreground);
    
    _uiLayer = UiLayer::create();
        
    _objectManager = GameObjectManager::getInstance();
    _messageDisoatcher = GameMessageDispatcher::getInstance();
    
    
    cc::Vec2 origin = cc::Director::getInstance()->getVisibleOrigin();
    cc::Vec2 size = cc::Director::getInstance()->getVisibleSize();
    
    _objNumLabel = cc::LabelAtlas::create();
    _objNumLabel->initWithString("0", cc::Director::getInstance()->getTextureCache()->getTextureForKey("/cc_fps_images"), 12, 32 , '.');
    _uiLayer->addChild(_objNumLabel);
    _objNumLabel->setPosition(origin + cc::Vec2(size.x / 2, size.y /3));
}

GameWorld::~GameWorld() {
}

void GameWorld::reset() {
    _objectManager->clear();
}

void GameWorld::update(float dt)
{
    _objectManager->update(dt);
    _messageDisoatcher->update(dt);
    
    static char text[16] = "";
    sprintf(text, "%zu/%zu", getObjectManager()->getObjectNum(), getObjectManager()->getObjectVecSize());
    _objNumLabel->setString(text);
}
