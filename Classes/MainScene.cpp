//
//  MainScene.cpp
//  demo-x
//
//  Created by Lars Birkemose on 07/08/15.
//
//

#include "MainScene.h"

USING_NS_CC;

// -----------------------------------------------------------------------
#pragma mark - MainLayer Implementation
// -----------------------------------------------------------------------

bool MainLayer::init()
{
    if (!Layer::init()) CCASSERT(false, "You don't need to see my identification!");
 
    _loading = cocos2d::Sprite::createWithSpriteFrameName("loading.png");
    _loading->setNormalizedPosition((Vec2){0.5, 0.5});
    this->addChild(_loading);

    return true;
}

// -----------------------------------------------------------------------

void MainLayer::onEnter()
{
    CCLayer::onEnter();
    
    // Add your custom onEnter code here (if needed)
    
}

void MainLayer::onExit()
{
    
    // Add your custom onExit code here (if needed)
    
    CCLayer::onExit();
}


// -----------------------------------------------------------------------
#pragma mark - MainScene Implementation
// -----------------------------------------------------------------------

bool MainScene::init()
{
    if (!Scene::init()) CCASSERT(false, "We don't need to see his identification.");
    
    _layer = MainLayer::create();
    this->addChild(_layer);
    
    return true;
}

// -----------------------------------------------------------------------


