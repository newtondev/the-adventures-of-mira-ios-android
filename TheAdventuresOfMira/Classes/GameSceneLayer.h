//
//  GameScene.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__GameScene__
#define __TheAdventuresOfMira__GameScene__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class GameSceneLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(GameSceneLayer);
    
    // the parallax background layer
    //CC_PROPERTY_PASS_BY_REF(BackgroundLayer, backgroundLayer, BackgroundLayer);
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // back button was pressed
    virtual void keyBackClicked();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
};

#endif /* defined(__TheAdventuresOfMira__GameScene__) */
