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

#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"

// -----------------------------------------------------------------------

class Paddle : public cocos2d::Sprite
{
public:
    enum class Side
    {
        LEFT,
        RIGHT,
        INVALID
    };
    Paddle();
    ~Paddle();
    
    static Paddle* createWithSide(Paddle::Side side);
    virtual bool initWithSide(Paddle::Side side);
    
    Paddle::Side getSide();
    float getDestination();
    void setDestination(float destination);
    bool validTouchPosition(cocos2d::Vec2 position);
    cocos2d::Touch* getTouch();
    void setTouch(cocos2d::Touch *touch);
    void update(float delta);
protected:
private:
    Paddle::Side _side;
    float _destination;
    cocos2d::Vec2 _gameOrigin;
    cocos2d::Size _gameSize;
    cocos2d::Touch *_touch;
};

// -----------------------------------------------------------------------

#endif // __PADDLE_H__










