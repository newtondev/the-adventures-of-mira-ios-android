//
//  GameObject.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__GameObject__
#define __TheAdventuresOfMira__GameObject__

#include "cocos2d.h"
#include "Constants.h"

class GameObject : public cocos2d::CCSprite
{
    CC_SYNTHESIZE(bool, isActive, IsActive);
    CC_SYNTHESIZE(bool, reactsToScreenBoundaries, ReactsToScreenBoundaries);
    CC_SYNTHESIZE(cocos2d::CCSize, screenSize, ScreenSize);
    CC_SYNTHESIZE(GameObjectType, gameObjectType, GameObjectType);
    
public:
    virtual bool init();
    virtual void changeState(CharacterState newState);
    virtual cocos2d::CCRect adjustedBoundingBox();
};

#endif /* defined(__TheAdventuresOfMira__GameObject__) */
