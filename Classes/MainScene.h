#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

// -----------------------------------------------------------------------

class MainLayer : public cocos2d::Layer
{
protected:
    cocos2d::Sprite *_loading;
public:
    CREATE_FUNC(MainLayer);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
};

// -----------------------------------------------------------------------

class MainScene : public cocos2d::Scene
{
protected:
    MainLayer *_layer;
public:
    CREATE_FUNC(MainScene);
    virtual bool init();
};

// -----------------------------------------------------------------------

#endif // __MAIN_SCENE_H__

















