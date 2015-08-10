#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include "cocos2d.h"

// -----------------------------------------------------------------------

class LoadScene : public cocos2d::Layer
{
protected:
    cocos2d::Scene *_scene;
    cocos2d::ui::Scale9Sprite *_background;
    cocos2d::ProgressTimer *_progress;
    cocos2d::Sprite *_loading;
    int _loadStep;
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void loadNext(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadScene);
};

// -----------------------------------------------------------------------

#endif // __LOAD_SCENE_H__
