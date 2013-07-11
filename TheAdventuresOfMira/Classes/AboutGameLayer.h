//
//  AboutGameLayer.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__AboutGameLayer__
#define __TheAdventuresOfMira__AboutGameLayer__

#include "cocos2d.h"

class AboutGameLayer : public cocos2d::CCLayer
{
private:
    void createBackButton();
public:
    CREATE_FUNC(AboutGameLayer);
    virtual bool init();
    void backButtonTouched();
};

#endif /* defined(__TheAdventuresOfMira__AboutGameLayer__) */
