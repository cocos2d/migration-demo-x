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

// -----------------------------------------------------------------------

Paddle::Paddle()
: _side(Side::INVALID)
, _destination(cocos2d::Vec2(0, 0))
{
    // create anything here which should last for the entire lifespan of the paddle
}

Paddle::~Paddle()
{
    // clean up
    
}

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

    _side = side;

    return true;
}

// -----------------------------------------------------------------------

Paddle::Side Paddle::getSide()
{
    return _side;
}

// -----------------------------------------------------------------------

cocos2d::Vec2 Paddle::getDestination()
{
    return _destination;
}

// -----------------------------------------------------------------------

void Paddle::setDestination(cocos2d::Vec2 destination)
{

    
    
    
    _destination = destination;
}

// -----------------------------------------------------------------------

bool validTouchPosition(cocos2d::Vec2 position)
{
    
    
    
    return false;
}

// -----------------------------------------------------------------------








