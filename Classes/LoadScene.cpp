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

#include "LoadScene.h"
#include "MainScene.h"
#include "UIScale9Sprite.h"
#include <unistd.h>

// -----------------------------------------------------------------------
// This scene is created without a layer, as it requires no touch handling

bool LoadScene::init()
{
    // ******************
    // create the base class
    
    // ** cocos2d-objc **
    // self = [super init];
    // NSAssert(self, @"Whoops");
    
    // ** cocos2d-x *****
    if (!Scene::init()) CCASSERT(false, "The Kessel Run in 12 parsecs? O'rly?");
    
    // ******************
    // preload artwork needed for load scene
    
    // ** cocos2d-objc **
    // [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"demo.plist"];

    // ** cocos2d-x *****
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("demo.plist");
    
    // ******************
    // get some screen dimensions
    
    // ** cocos2d-objc **
    // CGSize size = [CCDirector sharedDirector].viewSize;
    
    // ** cocos2d-x *****
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
    
    // ******************
    // create background
    
    // ** cocos2d-objc **
    // CCSprite9Slice *background = [CCSprite9Slice spriteWithImageNamed:@"white_square.png"];
    // background.anchorPoint = CGPointZero;
    // background.position = CGPointZero;
    // background.contentSize = size;
    // background.color = [CCColor grayColor];
    // [self addChild:background];
    
    // ** cocos2d-x *****
    _background = cocos2d::ui::Scale9Sprite::create("white_square.png");
    _background->setAnchorPoint(cocos2d::Vec2(0, 0));
    _background->setPosition(origin);
    _background->setContentSize(size);
    _background->setColor(cocos2d::Color3B(128, 128, 128));
    this->addChild(_background);
    
    // ******************
    // loading text
    
    // ** cocos2d-objc **
    // _loading = [CCSprite spriteWithImageNamed:@"loading.png"];
    // _loading.positionType = CCPositionTypeNormalized;
    // _loading.position = (CGPoint){0.5, 0.5};
    // [self addChild:_loading];
    
    // ** cocos2d-x *****
    _loading = cocos2d::Sprite::createWithSpriteFrameName("loading.png");
    _loading->setNormalizedPosition(cocos2d::Vec2(0.5, 0.5));
    this->addChild(_loading);
    
    // ******************
    // progress indicator
    
    // ** cocos2d-objc **
    //_progress = [CCProgressNode progressWithSprite:[CCSprite spriteWithImageNamed:@"progress.png"]];
    //_progress.positionType = CCPositionTypeNormalized;
    //_progress.position = (CGPoint){0.5, 0.5};
    //_progress.type = CCProgressNodeTypeRadial;
    //_progress.rotation = 180;
    //_progress.percentage = 0;
    //[self addChild:_progress];
    
    // ** cocos2d-x *****
    _progress = cocos2d::ProgressTimer::create(cocos2d::Sprite::createWithSpriteFrameName("progress.png"));
    _progress->setNormalizedPosition(cocos2d::Vec2(0.5, 0.5));
    _progress->setType(cocos2d::ProgressTimer::Type::RADIAL);
    _progress->setRotation(180);
    _progress->setPercentage(0);
    this->addChild(_progress);
    
    // ******************
    // schedule update
    
    // ** cocos2d-objc **
    // _loadStep = 0;
    // [self schedule:@selector(loadNext:) interval:0.033];
    
    // ** cocos2d-x *****
    _loadStep = 0;
    this->schedule(CC_SCHEDULE_SELECTOR(LoadScene::loadNext), 0.033);
    
    // ******************
    // done

    // ** cocos2d-objc **
    // return self;

    // ** cocos2d-x *****
    return true;
    
    // ******************
}

// -----------------------------------------------------------------------

void LoadScene::loadNext(float dt)
{
    switch (_loadStep)
    {
        case 0:
        {
            // load ex textures here
            // our loading doesnt take time, so we add a small delay to simulate "real" loading
            usleep(500000);
            _progress->setPercentage(40);
            break;
        }
        case 1:
        {
            // load ex audio here
            usleep(500000);
            _progress->setPercentage(50);
            break;
        }
        case 2:
        {
            // load animations, shaders etc
            usleep(500000);
            _progress->setPercentage(60);
            break;
        }
        case 3:
        {
            // pre render stuff
            usleep(500000);
            _progress->setPercentage(90);
            break;
        }
        default:
        {
            // done
            _progress->setPercentage(100);
            this->unschedule(CC_SCHEDULE_SELECTOR(LoadScene::loadNext));
            
            // ******************
            // Show some fancy animation.
            // Why, do you ask? Well, because we can.
            
            // ** cocos2d-objc **
            // [_progress runAction:[CCActionSequence actions:
            //                       [CCActionCallBlock actionWithBlock:^(void)
            //                        {
            //                        [_progress runAction:[CCActionEaseOut actionWithAction:[CCActionFadeOut actionWithDuration:1.0] rate:2.0]];
            //                        [_progress runAction:[CCActionEaseOut actionWithAction:[CCActionScaleTo actionWithDuration:1.0 scale:5.0] rate:2.0]];
            //                        [_loading runAction:[CCActionFadeOut actionWithDuration:1.0]];
            //                        }],
            //                       [CCActionDelay actionWithDuration:1.5], // here we wait for scale and fade to complete
            //                       [CCActionCallBlock actionWithBlock:^(void)
            //                        {
            //                        [[CCDirector sharedDirector] replaceScene:[MainScene new]
            //                                                   withTransition:[CCTransition transitionRevealWithDirection:CCTransitionDirectionLeft duration:0.5]];
            //                        }],
            //                       nil]];
            
            // ** cocos2d-x *****
            auto scaleProgress = cocos2d::CallFunc::create([this]()
            {
                _progress->runAction(cocos2d::ScaleTo::create(1.0, 5.0));
                _progress->runAction(cocos2d::FadeOut::create(1.0));
                _loading->runAction(cocos2d::FadeOut::create(1.0));
                
            });

            auto runMainScene = cocos2d::CallFunc::create([this]()
            {
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionSlideInR::create(0.5, MainScene::createScene()));
            });

            _progress->runAction(cocos2d::Sequence::create(scaleProgress,
                                                           cocos2d::DelayTime::create(1.5),
                                                           runMainScene,
                                                           NULL));
            // ******************
            
            break;
        }
    }
    
    // next step
    _loadStep ++;
}

// -----------------------------------------------------------------------

void LoadScene::menuCloseCallback(Ref* pSender)
{
    cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// -----------------------------------------------------------------------












