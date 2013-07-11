//
//  BackgroundLayer.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "BackgroundLayer.h"
#include "GameManager.h"

using namespace cocos2d;

bool BackgroundLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    parallax = CCParallaxScrollNode::create();
    
    CCSprite *backgroundImage1 = CCSprite::createWithSpriteFrameName("background.png");
    CCSprite *backgroundImage2 = CCSprite::createWithSpriteFrameName("background.png");
    parallax->addInfiniteScrollXWithZ(0, ccp(0.05, 0), ccp(0,SCREEN_HEIGHT-backgroundImage1->getContentSize().height), backgroundImage1, backgroundImage2, NULL);
    
    CCSprite *hillsImage1 = CCSprite::createWithSpriteFrameName("hills_bg.png");
    CCSprite *hillsImage2 = CCSprite::createWithSpriteFrameName("hills_bg.png");
    parallax->addInfiniteScrollXWithZ(1, ccp(0.15,0), ccp(0,SCREEN_HEIGHT*0.08), hillsImage1, hillsImage2, NULL);
    
    CCSprite *treesImage1 = CCSprite::createWithSpriteFrameName("trees_bg.png");
    CCSprite *treesImage2 = CCSprite::createWithSpriteFrameName("trees_bg.png");
    parallax->addInfiniteScrollXWithZ(2, ccp(0.25,0), ccp(0,SCREEN_HEIGHT*0.045), treesImage1, treesImage2, NULL);
    
    CCSprite *grassImage1 = CCSprite::createWithSpriteFrameName("grass_bg.png");
    CCSprite *grassImage2 = CCSprite::createWithSpriteFrameName("grass_bg.png");
    parallax->addInfiniteScrollXWithZ(4, ccp(1,0), ccp(0,0), grassImage1, grassImage2, NULL);
    
    CCSprite *windImage1 = CCSprite::createWithSpriteFrameName("wind.png");
    windImage1->setTag(kWindTag1);
    windImage1->setOpacity(90);
    CCSprite *windImage2 = CCSprite::createWithSpriteFrameName("wind.png");
    windImage2->setTag(kWindTag2);
    windImage2->setOpacity(90);
    parallax->addInfiniteScrollXWithZ(3, ccp(4, 0), ccp(0,0), windImage1, windImage2, NULL);
    
    this->addChild(parallax);
    this->scheduleUpdate();
    
    hideWind();
    
    return true;
}

void BackgroundLayer::hideWind()
{
    parallax->getChildByTag(kWindTag1)->setVisible(false);
    parallax->getChildByTag(kWindTag2)->setVisible(false);
}

void BackgroundLayer::showWind()
{
    parallax->getChildByTag(kWindTag1)->setVisible(true);
    parallax->getChildByTag(kWindTag2)->setVisible(true);
}

void BackgroundLayer::update(float dt)
{
    parallax->updateWithVelocity(ccp(GameManager::sharedGameManager()->getVelocity(), 0), dt);
}
