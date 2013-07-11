//
//  Mira.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "Mira.h"
#include "GameManager.h"

using namespace cocos2d;

Mira::~Mira()
{
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
    if (deathAnimationAction)
    {
        deathAnimationAction->release();
        deathAnimationAction = NULL;
    }
}

CCRect Mira::adjustedBoundingBox()
{
    CCRect originalBoundingBox = this->boundingBox();
    return CCRect(originalBoundingBox.origin.x+(originalBoundingBox.size.width/8), originalBoundingBox.origin.y+(originalBoundingBox.size.height/4), originalBoundingBox.size.width*0.7, originalBoundingBox.size.height*0.4);
}

void Mira::checkAndClampSpritePosition()
{
    
}

void Mira::changeState(CharacterState newState)
{
    // Make it invisible
    //this->setVisible(false);
    
    if (currentAction != NULL && !currentAction->isDone()) {
        this->stopAction(currentAction);
    }
    currentAction = NULL;
    this->setCharacterState(newState);
    
    switch (newState)
    {
        case kCharacterStateIdle:
            //this->stopAllActions();
            break;
        case kCharacterStateFlying:
        {
            currentAction = this->flyingAnimationAction;
//            this->setScale(0.7f);
        }
            break;
        case kCharacterStateHit:
        {
            currentAction = this->hitAnimationAction;
//            this->setScale(0.7f);
            this->changeToInvulnerable();
            this->minVelocity();
            
            CCFiniteTimeAction *delayAction = CCDelayTime::create(3.0f);
            CCFiniteTimeAction *backToFlyingAction = CCCallFunc::create(this, callfunc_selector(Mira::changeStateToFlying));
            this->runAction(CCSequence::createWithTwoActions(delayAction, backToFlyingAction));
            
            CCActionInterval *blinkAction = CCBlink::create(5.0f, 15);
            CCFiniteTimeAction *backToVulnerableAction = CCCallFunc::create(this, callfunc_selector(Mira::changeToVulnerable));
            this->runAction(CCSequence::createWithTwoActions(blinkAction, backToVulnerableAction));
        }
            break;
        case kCharacterStateDead:
        {
            currentAction = this->deathAnimationAction;
//            this->setScale(0.7f);
            
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
        //this->setVisible(true);
    }
}

void Mira::changeStateToIdle()
{
    this->changeState(kCharacterStateIdle);
}

void Mira::changeStateToSpawning()
{
    this->changeState(kCharacterStateSpawning);
}

void Mira::changeStateToFlying()
{
    this->normalVelocity();
    this->changeState(kCharacterStateFlying);
}

void Mira::changeStateToHit()
{
    this->changeState(kCharacterStateHit);
}

void Mira::changeStateToDead()
{
    this->changeState(kCharacterStateDead);
}

void Mira::changeToVulnerable()
{
    this->setVulnerable(true);
}

void Mira::changeToInvulnerable()
{
    this->setVulnerable(false);
}

void Mira::maxVelocity()
{
    GameManager::sharedGameManager()->maxVelocity();
}

void Mira::normalVelocity()
{
    GameManager::sharedGameManager()->normalVelocity();
}

void Mira::minVelocity()
{
    GameManager::sharedGameManager()->minVelocity();
}

void Mira::initAnimations()
{
    // Initialize the flying animation and repeat action
    {
        CCAnimation *flyingAnimation = CCAnimation::create();
        for (int i = 1; i <= 20; i++) {
            flyingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bee_%i.png", i)->getCString()));
        }
        flyingAnimation->setDelayPerUnit(0.1f);        
        this->setFlyingAnimationAction(CCRepeatForever::create(CCAnimate::create(flyingAnimation)));
        this->flyingAnimationAction->retain();
    }
    
    // Initialize the hit animation and repeat action
    {
        CCAnimation *hitAnimation = CCAnimation::create();
        for (int i = 21; i <= 24; i++) {
            hitAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bee_%i.png", i)->getCString()));
        }
        hitAnimation->setDelayPerUnit(0.1f);
        this->setHitAnimationAction(CCRepeatForever::create(CCAnimate::create(hitAnimation)));
        this->hitAnimationAction->retain();
    }
    
    // Initialize the death animation and repeat action
    {
        CCAnimation *deathAnimation = CCAnimation::create();
        for (int i = 21; i <= 24; i++) {
            deathAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bee_%i.png", i)->getCString()));
        }
        deathAnimation->setDelayPerUnit(0.1f);
        this->setDeathAnimationAction(CCRepeatForever::create(CCAnimate::create(deathAnimation)));
        this->deathAnimationAction->retain();
    }
    
    /**
    
    CCAnimation *hit = CCAnimation::create();
    for (int i = 21; i <=24; i++) {
        hit->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bee_%i.png", i)->getCString()));
    }
    CCActionInterval *hitAction = CCAnimate::create(hit);
    hitAction->setDuration(0.4f);
    this->hitAnimationAction = CCRepeatForever::create(hitAction);
    this->hitAnimationAction->retain();
    this->setHitAnimation(hit);
    this->hitAnimation->retain();
     */
}

bool Mira::init()
{
    bool pRet = false;
    if (GameObject::init())
    {
        this->setGameObjectType(kGameObjectTypeMira);
        this->initAnimations();
        this->setVulnerable(true);
        this->changeState(kCharacterStateFlying);
        //this->setScale(0.8f);
        
        pRet = true;
    }
    return pRet;
}

void Mira::playHitSound()
{
    
}

void Mira::playDeadSound()
{
    
}
