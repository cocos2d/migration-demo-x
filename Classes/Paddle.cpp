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

#include "Paddle.h"
#include "GameTypes.h"

// -----------------------------------------------------------------------

Paddle::Paddle()
: _side(Side::INVALID)
, _destination(0)
, _gameSize(cocos2d::Vec2(0, 0))
, _touch(nullptr)
{
    // default constructor
}

Paddle::~Paddle()
{
    // destructor
}

// -----------------------------------------------------------------------

Paddle* Paddle::createWithSide(Paddle::Side side)
{
    Paddle *paddle = new (std::nothrow) Paddle();
    CCASSERT(paddle, "You must unlearn, what you have learned");
    
    if (paddle->initWithSide(side))
    {
        paddle->autorelease();
        return paddle;
    }
    CC_SAFE_DELETE(paddle);
    return nullptr;
}

// -----------------------------------------------------------------------

bool Paddle::initWithSide(Paddle::Side side)
{
    if (!Sprite::initWithSpriteFrameName("paddle.png")) CCASSERT(false, "The force is strong with this one");

    // get origin and size of game area
    _gameOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
    _gameSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    _side = side;

    float x = (side == Paddle::Side::LEFT) ? kGamePaddleInset * _gameSize.width : (1 - kGamePaddleInset) * _gameSize.width;
    _destination = _gameSize.height * 0.5;
    this->setPosition(_gameOrigin + cocos2d::Vec2(x, _destination));
    
    this->scheduleUpdate();

    return true;
}

// -----------------------------------------------------------------------

Paddle::Side Paddle::getSide()
{
    return _side;
}

// -----------------------------------------------------------------------

float Paddle::getDestination()
{
    return _destination;
}

void Paddle::setDestination(float destination)
{
    float limit = this->getContentSize().height * 0.5;
    if (destination < limit) destination = limit;
    if (destination > (_gameSize.height - limit)) destination = _gameSize.height - limit;
    _destination = destination;
}

// -----------------------------------------------------------------------

cocos2d::Touch* Paddle::getTouch()
{
    return _touch;
}

void Paddle::setTouch(cocos2d::Touch *touch)
{
    _touch = touch;
}

// -----------------------------------------------------------------------

bool Paddle::validTouchPosition(cocos2d::Vec2 position)
{
    if (_side == Paddle::Side::LEFT) return (position.x < (kGamePaddleTouchArea * _gameSize.width));
    if (_side == Paddle::Side::RIGHT) return (position.x > ((1 - kGamePaddleTouchArea) * _gameSize.width));
    return false;
}

// -----------------------------------------------------------------------

void Paddle::update(float delta)
{
    // move to destination at light speed
    // calculate remaining distance and step
    float remainingDistance = fabs(this->getPosition().y - _destination);
    float step = kGamePaddleSpeed * _gameSize.height * delta;
    
    if (step > remainingDistance)
    {
        // if close enough, complete move to destination
        this->setPosition(this->getPosition().x, _destination);
    }
    else
    {
        // else step towards desination
        if (_destination > this->getPosition().y)
        {
            this->setPosition(this->getPosition() + cocos2d::Vec2(0, step));
        }
        else
        {
            this->setPosition(this->getPosition() - cocos2d::Vec2(0, step));
        }
    }
}

// -----------------------------------------------------------------------











