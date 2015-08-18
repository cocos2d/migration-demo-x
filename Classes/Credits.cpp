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

#include "Credits.h"

// -----------------------------------------------------------------------

Credits::Credits()
{
    // default constructor
}

Credits::~Credits()
{
    // destructor
    CCLOG("Credits killed");
}

Credits* Credits::createWithScene(cocos2d::Scene *scene, const std::string& plist)
{
    Credits *credits = new (std::nothrow) Credits();
    CCASSERT(credits, "You must unlearn, what you have learned");
    
    if (credits->initWithScene(scene, plist))
    {
        credits->autorelease();
        return credits;
    }
    CC_SAFE_DELETE(credits);
    return nullptr;
}

bool Credits::initWithScene(cocos2d::Scene *scene, const std::string& plist)
{
    // open the "dictionary"
    // in -x this is called a ValueMap, but the functionality is pretty much identical
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(plist);
    cocos2d::ValueMap dictionary = cocos2d::FileUtils::getInstance()->getValueMapFromFile(fullPath);

    // load stuff
    // _shaderStack = [NSMutableArray array];
    this->setContentSize(cocos2d::Director::getInstance()->getWinSize());
    _scene = scene;
    _yPos = 0.5;
    _isScrolling = true;
    _endGame = false;
    _spacing = dictionary["spacing"].asFloat();
    _useGreyScale = dictionary["use.greyscale"].asBool();
    _scrollSpeed = dictionary["scroll.speed"].asFloat();
    
    // create a scroll node occupying the entire screen
    _scrollNode = cocos2d::Node::create();
    _scrollNode->setContentSize(cocos2d::Director::getInstance()->getWinSize());
    // allow us to fade the scrollnode and all its children without fading the back button
    _scrollNode->setCascadeOpacityEnabled(true);
    this->addChild(_scrollNode);
    
    // create the sprite
    cocos2d::Sprite *logo = cocos2d::Sprite::createWithSpriteFrameName(dictionary["image"].asString());
    logo->setNormalizedPosition(cocos2d::Vec2(0.5, _yPos));
    _scrollNode->addChild(logo);
    
    // adjust yPos for first section
    _yPos -= (logo->getContentSize().height * 0.5 / _scrollNode->getContentSize().height);
    _yPos -= _spacing;

    // load the sections
    for (int sectionIndex = 1; sectionIndex < 999; sectionIndex ++)
    {
        std::string sectionName = cocos2d::StringUtils::format("section - %d", sectionIndex);
        if (!dictionary[sectionName].isNull()) this->loadSectionWithValueMap(dictionary[sectionName].asValueMap());
        else break;
    }
    
    // load endgame
    cocos2d::ValueMap endGameDict = dictionary["endgame"].asValueMap();
    for (int creditIndex = 1; creditIndex < 999; creditIndex ++)
    {
        std::string entry = cocos2d::StringUtils::format("credit - %d", creditIndex);
        if (!endGameDict[entry].isNull()) _endGameList.push_back(entry);
        else break;
    }
    
    // back button
    _back = cocos2d::ui::Button::create("back.png", "back.png", "back.png", cocos2d::ui::Button::TextureResType::PLIST);
    _back->setNormalizedPosition(cocos2d::Vec2(0.12, 0.86));
    _back->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                       {
                                           // Launch setup screen
                                           this->removeFromParentAndCleanup(true);
                                           /*
                                           [_scrollNode runAction:[CCActionSequence actions:
                                                                   [CCActionFadeOut actionWithDuration:1.0],
                                                                   [CCActionCallBlock actionWithBlock:^(void)
                                                                    {
                                                                    [self removeFromParentAndCleanup:YES];
                                                                    }],
                                                                   nil]];
                                            */
                                       });
    this->addChild(_back);
    
    

    
    
    
    
    
    
    
    
    
    
    // initialize touch handling
    cocos2d::EventListenerTouchOneByOne *listener = cocos2d::EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(Credits::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // start update
    this->scheduleUpdate();
    
    return true;
}

// -----------------------------------------------------------------------

bool Credits::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

// -----------------------------------------------------------------------

void Credits::loadSectionWithValueMap(cocos2d::ValueMap dictionary)
{
    cocos2d::Label *label;
    
    if (dictionary["header"].isNull()) return;
    
    label = cocos2d::Label::createWithSystemFont(dictionary["header"].asString(), "ArialMT", 16);
    label->setNormalizedPosition(cocos2d::Vec2(0.5, _yPos));
    _yPos -= _spacing;
    _scrollNode->addChild(label);
    
    for (int index = 1; index < 999; index ++)
    {
        std::string entryName = cocos2d::StringUtils::format("credit - %d", index);
        if (!dictionary[entryName].isNull())
        {
            label = cocos2d::Label::createWithSystemFont(dictionary[entryName].asString(), "ArialMT", 10);
            label->setNormalizedPosition(cocos2d::Vec2(0.5, _yPos));
            _yPos -= _spacing;
            _scrollNode->addChild(label);
        }
        else break;
    }
    // Take back one kadam to honor the Hebrew God
    _yPos -= _spacing;
}

// -----------------------------------------------------------------------

void Credits::update(float delta)
{
    if (!_isScrolling) return;
    
    float scrollAmountPrSecond = _scrollNode->getContentSize().height * _scrollSpeed;
    _scrollNode->setPosition(_scrollNode->getPosition() + cocos2d::Vec2(0, scrollAmountPrSecond * delta));

    if (_endGame) return;
    
    // start fading a little before last line hits centre of screen
    if (_scrollNode->getPosition().y > ((fabs(_yPos) + 0.2) * _scrollNode->getContentSize().height))
    {
        // endgame is on
        _endGame = true;
        
        // hide the back button
        _back->setVisible(false);
        
        // run endgame sequence
        auto fadeOut = cocos2d::CallFunc::create([&]()
        {
            _scrollNode->runAction(cocos2d::FadeOut::create(1));
        });
        
        auto showEndGame = cocos2d::CallFunc::create([&]()
        {
            // clear scrollNode (not visible anyways)
            _scrollNode->removeAllChildrenWithCleanup(true);
            _scrollNode->setPosition(cocos2d::Vec2(0, 0));
            _isScrolling = false;
            // show endgame
            _yPos = 0.5 + ((_endGameList.size() - 1) * _spacing * 0.5);
            for (std::string entry : _endGameList)
            {
                cocos2d::Label *label = cocos2d::Label::createWithSystemFont(entry, "ArialMT", 14);
                label->setNormalizedPosition(cocos2d::Vec2(0.5, _yPos));
                _yPos -= _spacing;
                _scrollNode->addChild(label);
            }
            _scrollNode->runAction(cocos2d::FadeIn::create(0.5));
        });

        auto endCredits = cocos2d::CallFunc::create([&]()
        {
            this->removeFromParentAndCleanup(true);
        });
        
        _scrollNode->runAction(cocos2d::Sequence::create(fadeOut,
                                                         cocos2d::DelayTime::create(1),
                                                         showEndGame,
                                                         cocos2d::DelayTime::create(2),
                                                         fadeOut,
                                                         cocos2d::DelayTime::create(1),
                                                         endCredits,
                                                         nullptr));

        
        
        /*
        
        // run endgame sequence
        [_scrollNode runAction:[CCActionSequence actions:
                                [CCActionFadeOut actionWithDuration:1.0],
                                [CCActionCallBlock actionWithBlock:^(void)
                                 {
                                 // clear scrollNode (not visible anyways)
                                 [_scrollNode removeAllChildrenWithCleanup:YES];
                                 _scrollNode.position = CGPointZero;
                                 _isScrolling = NO;
                                 
                                 // show endgame
                                 _yPos = 0.5 + ((_endgame.count - 1) * _spacing * 0.5);
                                 for (NSString *labelText in _endgame)
                                 {
                                 CCLabelTTF *label = [CCLabelTTF labelWithString:labelText fontName:@"ArialMT" fontSize:36];
                                 label.positionType = CCPositionTypeNormalized;
                                 label.position = (CGPoint){0.5, _yPos};
                                 [_scrollNode addChild:label];
                                 _yPos -= _spacing;
                                 }
                                 }],
                                [CCActionFadeIn actionWithDuration:0.5],
                                [CCActionDelay actionWithDuration:2.0],
                                [CCActionFadeOut actionWithDuration:1.0],
                                [CCActionCallBlock actionWithBlock:^(void)
                                 {
                                 [self removeFromParentAndCleanup:YES];
                                 }],
                                nil]];
         */
    }
}





















