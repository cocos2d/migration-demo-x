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
#include "UIButton.h"
#include "MainScene.h"
#include "GameTypes.h"

// -----------------------------------------------------------------------
#pragma mark - GameLayer Implementation
// -----------------------------------------------------------------------

bool GameLayer::init()
{
    if (!cocos2d::Layer::init()) CCASSERT(false, "You don't need to see my identification!");
    
    // get origin and size of game area
    _gameOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
    _gameSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    // create paddles
    _paddleLeft = Paddle::createWithSide(Paddle::Side::LEFT);
    this->addChild(_paddleLeft);
    
    _paddleRight = Paddle::createWithSide(Paddle::Side::RIGHT);
    this->addChild(_paddleRight);
    
    // create the ball
    _ball = cocos2d::Sprite::createWithSpriteFrameName("ball.png");
    this->addChild(_ball);
    
    // create a back button
    cocos2d::ui::Button *backButton = cocos2d::ui::Button::create("back.png", "back.png", "back.png", cocos2d::ui::Button::TextureResType::PLIST);
    backButton->setNormalizedPosition(cocos2d::Vec2(0.5, 0.1));
    backButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                      {
                                          // Send us back to main screen
                                          cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInB::create(0.5, MainScene::createScene()));
                                      });
    this->addChild(backButton);
    
    // draw touch area markers
    
    
    
    
    
    
    
    
    
    
    
    return true;
}

// -----------------------------------------------------------------------

void GameLayer::onEnter()
{
    cocos2d::Layer::onEnter();
    
    // Add your custom onEnter code here (if needed)
    
}

void GameLayer::onExit()
{
    
    // Add your custom onExit code here (if needed)
    
    cocos2d::Layer::onExit();
}


// -----------------------------------------------------------------------
#pragma mark - GameScene Implementation
// -----------------------------------------------------------------------

bool GameScene::init()
{
    if (!cocos2d::Scene::init()) CCASSERT(false, "We don't need to see his identification.");
    
    _layer = GameLayer::create();
    this->addChild(_layer);
    
    return true;
}

// -----------------------------------------------------------------------
