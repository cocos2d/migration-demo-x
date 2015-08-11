#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include "cocos2d.h"

// -----------------------------------------------------------------------

class LoadScene : public cocos2d::Scene
{
protected:
    cocos2d::ui::Scale9Sprite *_background;
    cocos2d::ProgressTimer *_progress;
    cocos2d::Sprite *_loading;
    int _loadStep;
public:
    // implement the "static create()" method manually
    CREATE_FUNC(LoadScene);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // scheduled method
    void loadNext(float dt);
};

// -----------------------------------------------------------------------

#endif // __LOAD_SCENE_H__
