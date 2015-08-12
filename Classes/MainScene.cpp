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
    



    // and we are out of here
    return true;
}

// -----------------------------------------------------------------------














