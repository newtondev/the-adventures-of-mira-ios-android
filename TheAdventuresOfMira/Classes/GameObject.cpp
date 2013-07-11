//
//  GameObject.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "GameObject.h"

using namespace cocos2d;

bool GameObject::init()
{
    bool pRet = false;
    
    if (CCSprite::init())
    {
        screenSize = SCREEN_SIZE;
        isActive = true;
        gameObjectType = kObjectTypeNone;
        // added to set scale
        pRet = true;
    }
    
    return pRet;
}

void GameObject::changeState(CharacterState newState)
{
    CCLOG("GameObject->changeState method should be overridden");
}

CCRect GameObject::adjustedBoundingBox()
{
    CCLOG("GameObject->adjustedBoundingBox should be overridden");
    return this->boundingBox();
}
