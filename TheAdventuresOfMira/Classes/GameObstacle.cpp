//
//  GameObstacle.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/10.
//
//

#include "GameObstacle.h"
#include "GameManager.h"

using namespace cocos2d;

GameObstacle *GameObstacle::create(GameObjectType pGameObjectType)
{
    GameObstacle *pRet = new GameObstacle();
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

GameObstacle::~GameObstacle()
{
    if (spawningAnimationAction)
    {
        spawningAnimationAction->release();
        spawningAnimationAction = NULL;
    }
    if (flyingAnimationAction)
    {
        flyingAnimationAction->release();
        flyingAnimationAction = NULL;
    }
    if (hitAnimationAction)
    {
        hitAnimationAction->release();
        hitAnimationAction = NULL;
    }
}

cocos2d::CCRect GameObstacle::adjustedBoundingBox()
{
    CCRect originalBoundingBox = this->boundingBox();
    return CCRect(originalBoundingBox.origin.x+(originalBoundingBox.size.width/8), originalBoundingBox.origin.y+(originalBoundingBox.size.height/4), originalBoundingBox.size.width*0.7, originalBoundingBox.size.height*0.4);
}

void GameObstacle::checkAndClampSpritePosition()
{
    
}

void GameObstacle::changeState(CharacterState newState)
{    
    if (currentAction != NULL && !currentAction->isDone()) {
        this->stopAction(currentAction);
    }
    currentAction = NULL;
    this->setCharacterState(newState);
    
    switch (newState)
    {
        case kCharacterStateIdle:
        {
            this->stopAllActions();
            this->setRotation(0);
            currentAction = NULL;
        }
            break;
        case kCharacterStateSpawning:
        {
            currentAction = spawningAnimationAction;
        }
            break;
        case kCharacterStateFlying:
        {
            currentAction = this->flyingAnimationAction;
        }
            break;
        case kCharacterStateHit:
        {
            currentAction = this->hitAnimationAction;
            
            CCActionInterval *rotateAction = CCRotateBy::create(0.6f, 360);
            this->runAction(CCRepeatForever::create(rotateAction));
        }
            break;
        default:
            break;
    }
    
    if (currentAction != NULL)
    {
        this->runAction(currentAction);
    }
}

void GameObstacle::changeStateToIdle()
{
    this->changeState(kCharacterStateIdle);
}

void GameObstacle::changeStateToSpawning()
{
    this->changeState(kCharacterStateSpawning);
}

void GameObstacle::changeStateToFlying()
{
    this->changeState(kCharacterStateFlying);
    CCPoint pos = this->getPosition();
    this->setPosition(ccp(pos.x+getContentSize().width, pos.y));
}

void GameObstacle::changeStateToHit()
{
    this->changeState(kCharacterStateHit);
}

void GameObstacle::changeStateToDead()
{
    this->changeState(kCharacterStateDead);
}

void GameObstacle::initAnimations()
{
    switch (this->getGameObjectType())
    {
        case kGameObjectTypeObstacleBlueBird:
            // Initialize the spawning animation and repeat action
        {
            CCAnimation *spawningAnimation = CCAnimation::create();
            for (int i = 1; i <= 4; i++) {
                spawningAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("watchout_%i.png", i)->getCString()));
            }
            spawningAnimation->setDelayPerUnit(0.1f);
            this->setSpawningAnimationAction(CCRepeatForever::create(CCAnimate::create(spawningAnimation)));
            this->spawningAnimationAction->retain();
        }
            
            // Initialize the flying animation and repeat action
        {
            CCAnimation *flyingAnimation = CCAnimation::create();
            for (int i = 1; i <= 4; i++) {
                flyingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bluebird_%i.png", i)->getCString()));
            }
            flyingAnimation->setDelayPerUnit(0.1f);
            this->setFlyingAnimationAction(CCRepeatForever::create(CCAnimate::create(flyingAnimation)));
            this->flyingAnimationAction->retain();
        }
            
            // Initialize the hit animation and repeat action
        {
            CCAnimation *hitAnimation = CCAnimation::create();
            hitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bluebird_5.png"));
            this->setHitAnimationAction(CCAnimate::create(hitAnimation));
            this->hitAnimationAction->retain();
        }
            break;
            
        case kGameObjectTypeObstacleBat:
            // Initialize the spawning animation and repeat action
        {
            CCAnimation *spawningAnimation = CCAnimation::create();
            for (int i = 1; i <= 4; i++) {
                spawningAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("watchout_%i.png", i)->getCString()));
            }
            spawningAnimation->setDelayPerUnit(0.1f);
            this->setSpawningAnimationAction(CCRepeatForever::create(CCAnimate::create(spawningAnimation)));
            this->spawningAnimationAction->retain();
        }
            
            // Initialize the flying animation and repeat action
        {
            CCAnimation *flyingAnimation = CCAnimation::create();
            for (int i = 1; i <= 4; i++) {
                flyingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bat_%i.png", i)->getCString()));
            }
            flyingAnimation->setDelayPerUnit(0.1f);
            this->setFlyingAnimationAction(CCRepeatForever::create(CCAnimate::create(flyingAnimation)));
            this->flyingAnimationAction->retain();
        }
            
            // Initialize the hit animation and repeat action
        {
            CCAnimation *hitAnimation = CCAnimation::create();
            hitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bat_5.png"));
            this->setHitAnimationAction(CCAnimate::create(hitAnimation));
            this->hitAnimationAction->retain();
        }
            break;
            
        case kGameObjectTypeObstacleSquirrel:
            // Initialize the spawning animation and repeat action
        {
            CCAnimation *spawningAnimation = CCAnimation::create();
            for (int i = 1; i <= 4; i++) {
                spawningAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("watchout_%i.png", i)->getCString()));
            }
            spawningAnimation->setDelayPerUnit(0.1f);
            this->setSpawningAnimationAction(CCRepeatForever::create(CCAnimate::create(spawningAnimation)));
            this->spawningAnimationAction->retain();
        }
            
            // Initialize the flying animation and repeat action
        {
            CCAnimation *flyingAnimation = CCAnimation::create();
            for (int i = 1; i <= 4; i++) {
                flyingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("squirrel_%i.png", i)->getCString()));
            }
            flyingAnimation->setDelayPerUnit(0.1f);
            this->setFlyingAnimationAction(CCRepeatForever::create(CCAnimate::create(flyingAnimation)));
            this->flyingAnimationAction->retain();
        }
            
            // Initialize the hit animation and repeat action
        {
            CCAnimation *hitAnimation = CCAnimation::create();
            hitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("squirrel_5.png"));
            this->setHitAnimationAction(CCAnimate::create(hitAnimation));
            this->hitAnimationAction->retain();
        }
            break;
            
        case kGameObjectTypeObstacleLadyBug:
            // Initialize the spawning animation and repeat action
        {
            CCAnimation *spawningAnimation = CCAnimation::create();
            for (int i = 1; i <= 4; i++) {
                spawningAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("watchout_%i.png", i)->getCString()));
            }
            spawningAnimation->setDelayPerUnit(0.1f);
            this->setSpawningAnimationAction(CCRepeatForever::create(CCAnimate::create(spawningAnimation)));
            this->spawningAnimationAction->retain();
        }
            
            // Initialize the flying animation and repeat action
        {
            CCAnimation *flyingAnimation = CCAnimation::create();
            for (int i = 1; i <= 3; i++) {
                flyingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("ladybug_%i.png", i)->getCString()));
            }
            flyingAnimation->setDelayPerUnit(0.1f);
            this->setFlyingAnimationAction(CCRepeatForever::create(CCAnimate::create(flyingAnimation)));
            this->flyingAnimationAction->retain();
        }
            
            // Initialize the hit animation and repeat action
        {
            CCAnimation *hitAnimation = CCAnimation::create();
            hitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ladybug_4.png"));
            this->setHitAnimationAction(CCAnimate::create(hitAnimation));
            this->hitAnimationAction->retain();
        }
            break;
            
        default: // kGameObstacleTypeRedBird
        {
            // Initialize the spawning animation and repeat action
            {
                CCAnimation *spawningAnimation = CCAnimation::create();
                for (int i = 1; i <= 4; i++) {
                    spawningAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("watchout_%i.png", i)->getCString()));
                }
                spawningAnimation->setDelayPerUnit(0.1f);
                this->setSpawningAnimationAction(CCRepeatForever::create(CCAnimate::create(spawningAnimation)));
                this->spawningAnimationAction->retain();
            }
            
            // Initialize the flying animation and repeat action
            {
                CCAnimation *flyingAnimation = CCAnimation::create();
                    for (int i = 1; i <= 4; i++) {
                        flyingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("redbird_%i.png", i)->getCString()));
                    }
                flyingAnimation->setDelayPerUnit(0.1f);
                this->setFlyingAnimationAction(CCRepeatForever::create(CCAnimate::create(flyingAnimation)));
                this->flyingAnimationAction->retain();
            }
            
            // Initialize the hit animation and repeat action
            {
                CCAnimation *hitAnimation = CCAnimation::create();
                hitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("redbird_5.png"));
                this->setHitAnimationAction(CCAnimate::create(hitAnimation));
                this->hitAnimationAction->retain();
            }
        }
            break;
    }
}

bool GameObstacle::init(GameObjectType type)
{
    bool pRet = false;
    if (GameCharacter::init())
    {
        this->setGameObjectType(type);
        this->initAnimations();
        this->changeState(kCharacterStateIdle);
        this->setAdjustedVelocity(-1*GameManager::randomValueBetween(1.0f, 6.0f));
        
        pRet = true;
    }
    return pRet;
}

void GameObstacle::playSpawningSound()
{
    
}

void GameObstacle::playHitSound()
{
    
}

void GameObstacle::playDeadSound()
{
    
}

void GameObstacle::update(float dt)
{
    GameCharacter::update(dt);
}
