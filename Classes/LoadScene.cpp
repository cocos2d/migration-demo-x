#include "LoadScene.h"
#include "MainScene.h"
#include "UIScale9Sprite.h"
#include <unistd.h>

USING_NS_CC;

// -----------------------------------------------------------------------

Scene* LoadScene::createScene()
{
    /*
     This is how the templates normally create a scene
     If you wonder why scene is based on cocos2d::Layer, and why you cant use create(), here is the explanation
     
     When creating a scene, you must also have at least one layer. Unlike -objc, you can not add nodes to a scene, only layers.
     So to avoid creating both a cocos2d::Scene descendant, and a cocos2d::Layer descendant, this hybrid is created.
     
     So why not simply base it on cocos2d::Scene you ask?
     
     The reason is as stated above, that you can not add nodes to a scene. So if the class was based on cocos2d::Scene, you could not
     use the syntax this->addChild in myScene::init. You would have to create a cocos2d::Layer, and add the nodes to that, so you would 
     end up with this->_layer->addChild, which really isnt all that good programming.
     
     The final thing needed is a constructor / factory method, since you can not use default MyScene::create, as it would return a cocos2d::Layer.
     Because of that, we use createScene to build the scene + layer hierachy, and then return the scene.
    
     For an "easier to understand" approach, see MainScene
    */

    // create the scene, which we will later return
    auto scene = Scene::create();
    
    // create the layer, and add it to the scene
    auto layer = LoadScene::create();
    scene->addChild(layer);

    // return the scene
    return scene;
}

// -----------------------------------------------------------------------

bool LoadScene::init()
{
    // ******************
    // create the base class
    
    // ** cocos2d-objc **
    // self = [super init];
    // NSAssert(self, @"Whoops");
    
    // ** cocos2d-x *****
    if (!Layer::init()) CCASSERT(false, "The Kessel Run in 12 parsecs? O'rly?");
    
    // ******************
    // preload artwork needed for load scene
    
    // ** cocos2d-objc **
    // [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"demo.plist"];

    // ** cocos2d-x *****
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("demo.plist");
    
    // ******************
    // get some screen dimensions
    
    // ** cocos2d-objc **
    // CGSize size = [CCDirector sharedDirector].viewSize;
    
    // ** cocos2d-x *****
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    
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
    _background->setAnchorPoint((cocos2d::Vec2){0, 0});
    _background->setPosition(origin);
    _background->setContentSize(size);
    _background->setColor((cocos2d::Color3B){128, 128, 128});
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
    _loading->setNormalizedPosition((Vec2){0.5, 0.5});
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
    _progress->setNormalizedPosition((Vec2){0.5, 0.5});
    _progress->setType(ProgressTimer::Type::RADIAL);
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
            auto scaleProgress = CallFunc::create([this]()
            {
                _progress->runAction(cocos2d::ScaleTo::create(1.0, 5.0));
                _progress->runAction(cocos2d::FadeOut::create(1.0));
                _loading->runAction(cocos2d::FadeOut::create(1.0));
                
            });

            auto runMainScene = CallFunc::create([this]()
            {
                Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5, MainScene::create()));
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
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// -----------------------------------------------------------------------












