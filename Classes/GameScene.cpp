// ****************************************************************************
//
// http://www.cocos2d-x.org
//
// Copyright (c) 2015 Lars Birkemose
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// ****************************************************************************

#include "GameScene.h"

USING_NS_CC;

// -----------------------------------------------------------------------
#pragma mark - GameLayer Implementation
// -----------------------------------------------------------------------

bool GameLayer::init()
{
    if (!Layer::init()) CCASSERT(false, "You don't need to see my identification!");
    
    _loading = cocos2d::Sprite::createWithSpriteFrameName("loading.png");
    _loading->setNormalizedPosition((Vec2){0.5, 0.5});
    this->addChild(_loading);
    
    return true;
}

// -----------------------------------------------------------------------

void GameLayer::onEnter()
{
    CCLayer::onEnter();
    
    // Add your custom onEnter code here (if needed)
    
}

void GameLayer::onExit()
{
    
    // Add your custom onExit code here (if needed)
    
    CCLayer::onExit();
}


// -----------------------------------------------------------------------
#pragma mark - GameScene Implementation
// -----------------------------------------------------------------------

bool GameScene::init()
{
    if (!Scene::init()) CCASSERT(false, "We don't need to see his identification.");
    
    _layer = GameLayer::create();
    this->addChild(_layer);
    
    return true;
}

// -----------------------------------------------------------------------
