//
//  CollectableItem.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/15.
//
//

#include "CollectableItem.h"
#include "GameManager.h"

using namespace cocos2d;

CollectableItem *CollectableItem::create(GameObjectType pGameObjectType)
{
    CollectableItem *pRet = new CollectableItem();
    if (pRet && pRet->init(pGameObjectType))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

CollectableItem::~CollectableItem()
{

}

void CollectableItem::changeState(CharacterState newState)
{
    
}

cocos2d::CCRect CollectableItem::adjustedBoundingBox()
{
    CCRect originalBoundingBox = this->boundingBox();
    return CCRect(originalBoundingBox.origin.x+(originalBoundingBox.size.width/8), originalBoundingBox.origin.y+(originalBoundingBox.size.height/4), originalBoundingBox.size.width*0.7, originalBoundingBox.size.height*0.4);
}

void CollectableItem::checkAndClampSpritePosition()
{
    
}

bool CollectableItem::init(GameObjectType type)
{
    bool pRet = false;
    if (GameObject::init())
    {
        this->setGameObjectType(type);
        this->changeState(kCharacterStateIdle);
        this->initSprite();
        pRet = true;
    }
    return pRet;
}

void CollectableItem::initSprite()
{
    switch (this->getGameObjectType()) {
        case kGameObjectTypeCollectableFlower1:
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("item_1.png"));
            break;
            
        case kGameObjectTypeCollectableFlower2:
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("item_2.png"));
            break;
            
        case kGameObjectTypeCollectableFlower3:
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("item_3.png"));
            break;
            
        case kGameObjectTypeCollectableFlower4:
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("item_4.png"));
            break;
            
        case kGameObjectTypeCollectableFlower5:
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("item_5.png"));
            break;
            
        case kGameObjectTypePowerUpCandy:
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("item_6.png"));
            break;
            
        case kGameObjectTypePowerUpMagnet:
            this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("item_7.png"));
            break;
            
        default:
            break;
    }
}
