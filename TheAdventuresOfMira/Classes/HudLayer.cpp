//
//  HudLayer.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "HudLayer.h"
#include "Constants.h"
#include "GameManager.h"

using namespace cocos2d;

bool HudLayer::init()
{
    if (!CCLayer::init()) return false;
    
    CCSprite *hudBackground = CCSprite::createWithSpriteFrameName("head_ui.png");
    this->setContentSize(hudBackground->getContentSize());
    this->addChild(hudBackground);
    
    float labelScaleText = 1.0f;
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid854x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x400 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid720x480)
    {
        labelScaleText = 0.7f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeNormal)
    {
        labelScaleText = 0.8f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeSmall)
    {
        labelScaleText = 0.45f;
    }
    
    livesLabel = CCLabelBMFont::create(CCString::createWithFormat("%i", GameManager::sharedGameManager()->getLives())->getCString(), "myGlyphs.fnt");
    livesLabel->retain();
    livesLabel->setScale(labelScaleText);
    livesLabel->setTag(kLabel_Lives);
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeiPhone5)
    {
        livesLabel->setPosition(ccp(-(SCREEN_WIDTH/4.4), livesLabel->getPosition().y-4));
    }
    else if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid1280x800 ||
             GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid1280x720)
    {
        livesLabel->setPosition(ccp(-(SCREEN_WIDTH/4.9), livesLabel->getPosition().y-4));
    }
    else
    {
        livesLabel->setPosition(ccp(-(SCREEN_WIDTH/3.7), livesLabel->getPosition().y-4));
    }
    addChild(livesLabel);
    
    scoreLabel = CCLabelBMFont::create(CCString::createWithFormat("%i", GameManager::sharedGameManager()->getScore())->getCString(), "myGlyphs.fnt");
    scoreLabel->retain();
    scoreLabel->setScale(labelScaleText);
    scoreLabel->setTag(kLabel_Score);
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeiPhone5)
    {
        scoreLabel->setPosition(ccp((SCREEN_WIDTH/2)-(SCREEN_WIDTH/2.1), scoreLabel->getPosition().y-4));
    }
    else if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid1280x800 ||
             GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid1280x720)
    {
        scoreLabel->setPosition(ccp((SCREEN_WIDTH/2)-(SCREEN_WIDTH/2.09), scoreLabel->getPosition().y-4));
    }    
    else
    {
        scoreLabel->setPosition(ccp((SCREEN_WIDTH/2)-(SCREEN_WIDTH/2.13), scoreLabel->getPosition().y-4));
    }
    addChild(scoreLabel);
    
    distanceLabel = CCLabelBMFont::create(CCString::createWithFormat("%i", GameManager::sharedGameManager()->getDistance())->getCString(), "myGlyphs.fnt");
    distanceLabel->retain();
    distanceLabel->setScale(labelScaleText);
    distanceLabel->setTag(kLabel_Distance);
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeiPhone5)
    {
        distanceLabel->setPosition(ccp((SCREEN_WIDTH/2)-(SCREEN_WIDTH/4.4), distanceLabel->getPosition().y-4));
    }
    else if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid1280x800 ||
             GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid1280x720)
    {
        distanceLabel->setPosition(ccp((SCREEN_WIDTH/2)-(SCREEN_WIDTH/3.85), distanceLabel->getPosition().y-4));
    }
    else
    {
        distanceLabel->setPosition(ccp((SCREEN_WIDTH/2)-(SCREEN_WIDTH/5.65), distanceLabel->getPosition().y-4));
    }
    addChild(distanceLabel);
    
    return true;
}

