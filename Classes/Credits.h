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

#ifndef __CREDITS_H
#define __CREDITS_H

#include "cocos2d.h"
#include "UIButton.h"

// -----------------------------------------------------------------------

class Credits : public cocos2d::Layer
{
private:
    cocos2d::Scene *_scene;
    float _yPos;
    bool _isScrolling;
    bool _endGame;
    float _spacing;
    bool _useGreyScale;
    float _scrollSpeed;
    cocos2d::Node *_scrollNode;
    cocos2d::ui::Button *_back;
    std::vector<std::string> _endGameList;
public:
    Credits();
    ~Credits();
    
    static Credits* createWithScene(cocos2d::Scene *scene, const std::string& plist);
    virtual bool initWithScene(cocos2d::Scene *scene, const std::string& plist);

    void loadSectionWithValueMap(cocos2d::ValueMap dictionary);
    void update(float delta);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    void replaceShaderWithGreayScaleShader(cocos2d::Node *node);
    void restoreShader(cocos2d::Node node);
};

// -----------------------------------------------------------------------

#endif // __CREDITS_H











