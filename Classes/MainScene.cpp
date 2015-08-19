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

#include "MainScene.h"
#include "UIScale9Sprite.h"
#include "UIButton.h"
#include "GameScene.h"
#include "SetupScene.h"
#include "GameTypes.h"
#include "Credits.h"

// -----------------------------------------------------------------------
/*
 This is how the templates normally creates a scene
 If you wonder why scene is based on cocos2d::Layer, and why you cant use create(), here is the explanation
 
 While a Layer is technically not needed, it is often used as the base parent for nodes, because layers
 amongst other things handles touches. In order to avoid creating two classes for the templates, scene and layer is simply wrapped in one.
 
 So why not base it on cocos2d::Scene you ask?
 
 The reason is as stated above, that because touch handling goes through layers, adding nodes to a scene will inhibit
 touch handling on them. Because of that, if the class was based on Scene, you could not use the syntax this->addChild in myScene::init.
 You would have to create a cocos2d::Layer, and add the nodes to that, so you would end up with this->_layer->addChild,
 which would be very error prone and nasty looking.
 
 The final thing needed is a constructor / factory method, since you can not use default MyScene::create, as it would return a cocos2d::Layer.
 Because of that, we use createScene to build the scene + layer hierarchy, and then return the scene.
 
 To see how to build a scene without a layer, have a look at loadScene (where touches are not needed)
 To see how to build an "easier to understand" scene / layer hierachy, have a look at GameScene
 */

cocos2d::Scene* MainScene::createScene()
{    
    // create the scene, which we will later return
    auto scene = cocos2d::Scene::create();
    
    // create the layer, and add it to the scene
    auto layer = MainScene::create();
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// -----------------------------------------------------------------------

bool MainScene::init()
{
    if (!cocos2d::Layer::init()) CCASSERT(false, "I find your lack of faith disturbing");

    // initalize the main scene
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    // add a solid colored node
    cocos2d::ui::Scale9Sprite *background = cocos2d::ui::Scale9Sprite::create("white_square.png");
    background->setAnchorPoint(cocos2d::Vec2(0, 0));
    background->setPosition(origin);
    background->setContentSize(size);
    background->setColor(kGameMainSceneColor);
    this->addChild(background);
    
    // start button
    cocos2d::ui::Button *startButton = cocos2d::ui::Button::create("start.png", "start.png", "start.png", cocos2d::ui::Button::TextureResType::PLIST);
    startButton->setNormalizedPosition(cocos2d::Vec2(0.5, 0.6));
    startButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                       {
                                           // Here you can check if the button was pressed or released
                                           // For now we are just happy that something happened ...
                                           // Launch the game scene
                                           cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInT::create(0.5, GameScene::create()));
                                       });
    this->addChild(startButton);
    
    // setup button
    cocos2d::ui::Button *setupButton = cocos2d::ui::Button::create("setup.png", "setup.png", "setup.png", cocos2d::ui::Button::TextureResType::PLIST);
    setupButton->setNormalizedPosition(cocos2d::Vec2(0.5, 0.4));
    setupButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                       {
                                           // Launch setup screen
                                           cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInB::create(0.5, SetupScene::createScene()));
                                       });
    this->addChild(setupButton);
    
    // info button
    cocos2d::ui::Button *infoButton = cocos2d::ui::Button::create("info.png", "info.png", "info.png", cocos2d::ui::Button::TextureResType::PLIST);
    infoButton->setNormalizedPosition(cocos2d::Vec2(0.88, 0.14));
    infoButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                      {
                                          // to make sure credits is not called repeatedly, we check for the event type
                                          switch (type)
                                          {
                                              case cocos2d::ui::Widget::TouchEventType::ENDED:
                                                  // launch credits overlay
                                                  this->infoPressed();
                                                  break;
                                                  
                                              case cocos2d::ui::Widget::TouchEventType::BEGAN:
                                              case cocos2d::ui::Widget::TouchEventType::MOVED:
                                              case cocos2d::ui::Widget::TouchEventType::CANCELED:
                                              default:
                                                  break;
                                          }
                                      });
    this->addChild(infoButton);
    
    // no credits shown
    _credits = nullptr;
    
    // and we are out of here
    return true;
}

// -----------------------------------------------------------------------

void MainScene::infoPressed()
{
    _credits = Credits::createWithScene(cocos2d::Director::getInstance()->getRunningScene(), "credits-x.plist");
    this->addChild(_credits);
}

// -----------------------------------------------------------------------














