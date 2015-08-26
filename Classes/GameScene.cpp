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
#include "SimpleAudioEngine.h"

// -----------------------------------------------------------------------
#pragma mark - GameLayer Implementation -
// -----------------------------------------------------------------------
#pragma mark Initialization

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
    backButton->setNormalizedPosition(cocos2d::Vec2(0.5, 0.14));
    backButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                      {
                                          // Send us back to main screen
                                          cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInB::create(0.5, MainScene::createScene()));
                                      });
    this->addChild(backButton);
    
    // draw touch area markers
    cocos2d::DrawNode *drawNode = cocos2d::DrawNode::create();
    this->addChild(drawNode);
    
    drawNode->drawLine(_gameOrigin + cocos2d::Vec2(kGamePaddleTouchArea * _gameSize.width, 0),
                       _gameOrigin + cocos2d::Vec2(kGamePaddleTouchArea * _gameSize.width, _gameSize.height),
                       cocos2d::Color4F(kGameColor));
    drawNode->drawLine(_gameOrigin + cocos2d::Vec2((1 - kGamePaddleTouchArea) * _gameSize.width, 0),
                       _gameOrigin + cocos2d::Vec2((1 - kGamePaddleTouchArea) * _gameSize.width, _gameSize.height),
                       cocos2d::Color4F(kGameColor));
    
    // initialize touch handling
    cocos2d::EventListenerTouchAllAtOnce *listener = cocos2d::EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameLayer::onTouchesCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // load sound volume
    cocos2d::UserDefault *defaults = cocos2d::UserDefault::getInstance();
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(defaults->getFloatForKey(kGameKeySoundVolume));

    // serve first ball from random side
    this->serveFromSide(Paddle::Side::INVALID);
    
    return true;
}

// -----------------------------------------------------------------------
#pragma mark Enter & Exit

void GameLayer::onEnterTransitionDidFinish()
{
    this->scheduleUpdate();
}

void GameLayer::onExitTransitionDidStart()
{
    this->unscheduleUpdate();
}

// -----------------------------------------------------------------------
#pragma mark Touch Handling

void GameLayer::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    for (cocos2d::Touch *touch : touches)
    {
        Paddle *paddle = nullptr;
        cocos2d::Vec2 position = touch->getLocation() - _gameOrigin;
        
        // find out if valid paddle position
        if (_paddleLeft->validTouchPosition(position)) paddle = _paddleLeft;
        if (_paddleRight->validTouchPosition(position)) paddle = _paddleRight;
        
        if (paddle != nullptr)
        {
            // if paddle already has a touch assigned, create a game tilt
            if (paddle->getTouch() != nullptr)
            {
                this->gameTilt();
            }
            else
            {
                // paddle touch started
                paddle->setTouch(touch);
                paddle->setDestination(position.y);
            }
        }
    }
}

void GameLayer::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    for (cocos2d::Touch *touch : touches)
    {
        Paddle *paddle = nullptr;
        cocos2d::Vec2 position = touch->getLocation() - _gameOrigin;

        if (touch == _paddleLeft->getTouch()) paddle = _paddleLeft;
        else if (touch == _paddleRight->getTouch()) paddle = _paddleRight;
        
        if (paddle != nullptr)
        {
            if (paddle->validTouchPosition(position))
            {
                paddle->setDestination(position.y);
            }
            else
            {
                paddle->setTouch(nullptr);
            }
        }
    }
}

void GameLayer::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    for (cocos2d::Touch *touch : touches)
    {
        if (touch == _paddleLeft->getTouch()) _paddleLeft->setTouch(nullptr);
        else if (touch == _paddleRight->getTouch()) _paddleRight->setTouch(nullptr);
    }
}

void GameLayer::onTouchesCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    // treat cancelled touches as ended touches
    this->onTouchesEnded(touches, event);
}

// -----------------------------------------------------------------------
#pragma mark Scheduled update

void GameLayer::update(float delta)
{
    // move ball
    _ball->setPosition(_ball->getPosition() + (_ballVector * delta));
    
    // *************************
    // Game Logic
    // *************************

    // a convenient value
    cocos2d::Vec2 offset = cocos2d::Vec2((_paddleLeft->getContentSize().width + _ball->getContentSize().width) * 0.5, 0);

    // check if ball collides with left paddle
    if (_paddleLeft->getBoundingBox().intersectsRect(_ball->getBoundingBox()))
    {
        // play an annoying sound
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("beep.wav");
        // move ball out of paddle
        // in theory, the ball should be moved as much away from the paddle as it has penetrated
        // also, depending on penetration, collision point should be adjusted, but that is for the feinsmeckers out there ...
        _ball->setPosition(cocos2d::Vec2(_paddleLeft->getPosition().x, _ball->getPosition().y) + offset);
        // change direction
        _ballVector.x = -_ballVector.x;
        
        // add some ball spin
        // if ball is hit in upper half, spin the ball upwards, and downwards if hit in lower half
        float spin = (_ball->getPosition().y - _paddleLeft->getPosition().y) / _gameSize.height * kGameSpinFactor;
        // add some randomness
        spin += (CCRANDOM_MINUS1_1() * kGameSpinRandomFactor);
        // adjust vector
        _ballVector.rotate(cocos2d::Vec2(0, 0), spin * M_PI / 180);
    }
    // check if ball collides with right paddle
    else if (_paddleRight->getBoundingBox().intersectsRect(_ball->getBoundingBox()))
    {
        // see above
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("beep.wav");
        _ball->setPosition(cocos2d::Vec2(_paddleRight->getPosition().x, _ball->getPosition().y) - offset);
        _ballVector.x = -_ballVector.x;
        float spin = (_paddleRight->getPosition().y - _ball->getPosition().y) / _gameSize.height * kGameSpinFactor;
        spin += (CCRANDOM_MINUS1_1() * kGameSpinRandomFactor);
        _ballVector.rotate(cocos2d::Vec2(0, 0), spin * M_PI / 180);
    }
    
    // some convenient data
    float halfABallSize = _ball->getContentSize().height * 0.5;
    
    // check for top collision
    if (_ball->getPosition().y > (_gameSize.height - halfABallSize))
    {
        // that annoying sound again
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("beep.wav");
        // adjust ball position (see discussion on hitting game paddle)
        _ball->setPosition(_ball->getPosition().x, _gameSize.height - halfABallSize);
        // change direction
        _ballVector.y = -_ballVector.y;
    }
    // else check for bottom collision
    else if (_ball->getPosition().y < halfABallSize)
    {
        // see above
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("beep.wav");
        _ball->setPosition(_ball->getPosition().x, halfABallSize);
        _ballVector.y = -_ballVector.y;
    }
    
    // check if right paddle scored
    if (_ball->getPosition().x < -halfABallSize)
    {
        // play another deeply disturbing sound, to let the world know a point was gained
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("game.wav");
        // keep track of some scores
        
        
        // new balls please
        this->serveFromSide(Paddle::Side::RIGHT);
    }
    // else check if left paddle scored
    else if (_ball->getPosition().x > (_gameSize.width + halfABallSize))
    {
        // see above
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("game.wav");
        this->serveFromSide(Paddle::Side::LEFT);
    }
}

// -----------------------------------------------------------------------
#pragma mark Game functionality

void GameLayer::gameTilt()
{
    CCLOG("GAME TILT!");
}

void GameLayer::serveFromSide(Paddle::Side side)
{
    // if invalid side, serve random
    if (side == Paddle::Side::INVALID) side = (CCRANDOM_0_1() > 0.5) ? Paddle::Side::LEFT : Paddle::Side::RIGHT;
    
    cocos2d::Vec2 offset = cocos2d::Vec2((_paddleLeft->getContentSize().width + _ball->getContentSize().width) * 0.5, 0);

    if (side == Paddle::Side::LEFT)
    {
        _ball->setPosition(_paddleLeft->getPosition() + offset);
         _ballVector = cocos2d::Vec2(kGameBallSpeed * _gameSize.width, 0);
    }
    else
    {
        _ball->setPosition(_paddleRight->getPosition() - offset);
        _ballVector = cocos2d::Vec2(-kGameBallSpeed * _gameSize.width, 0);
    }
}

// -----------------------------------------------------------------------
#pragma mark - GameScene Implementation -
// -----------------------------------------------------------------------
#pragma mark Initialization

bool GameScene::init()
{
    if (!cocos2d::Scene::init()) CCASSERT(false, "We don't need to see his identification.");
    
    _layer = GameLayer::create();
    this->addChild(_layer);
    
    return true;
}

// -----------------------------------------------------------------------
