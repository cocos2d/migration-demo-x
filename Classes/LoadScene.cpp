#include "LoadScene.h"
#include "UIScale9Sprite.h"

USING_NS_CC;

Scene* LoadScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadScene::init()
{
    // create the base class
    // If this fails, the world will end anyways, so an assert will make sure we are aware of any problems during development
    if (!Layer::init()) assert("The Kessel Run in 12 parsecs? O'rly?");

    // get size and position of visible area
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

    //  first we preload the artwork needed to run the load scene
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("demo.plist");
    
    // create a colored background
    _background = cocos2d::ui::Scale9Sprite::create("white_square.png");
    _background->setAnchorPoint((cocos2d::Vec2){0, 0});
    _background->setContentSize(visibleSize);
    _background->setPosition(visibleOrigin);
    _background->setColor((cocos2d::Color3B){128, 128, 128});
    this->addChild(_background);
    
    // loading text

    
    
    // progress indicator
    _progress = cocos2d::ProgressTimer::create(cocos2d::Sprite::createWithSpriteFrameName("progress.png"));
    _progress->setPosition(visibleOrigin + (Vec2){100, 100});
    _progress->setPercentage(66);
    this->addChild(_progress);
    

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(LoadScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(visibleOrigin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                visibleOrigin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleOrigin.x + visibleSize.width/2,
                            visibleOrigin.y + visibleSize.height - label->getContentSize().height));

    label->setScale(0.25);
    
    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "LoadScene" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + visibleOrigin.x, visibleSize.height/2 + visibleOrigin.y));

    // add the sprite as a child to this layer
    sprite->setScale(0.25);
    
    this->addChild(sprite, 0);
    
    return true;
}


void LoadScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
