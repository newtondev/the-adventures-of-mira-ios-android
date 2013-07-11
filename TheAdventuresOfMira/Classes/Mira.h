//
//  Mira.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__Mira__
#define __TheAdventuresOfMira__Mira__

#include "GameCharacter.h"

class Mira : public GameCharacter
{
    CC_SYNTHESIZE(cocos2d::CCAction *, flyingAnimationAction, FlyingAnimationAction);
    CC_SYNTHESIZE(cocos2d::CCAction *, hitAnimationAction, HitAnimationAction);
    CC_SYNTHESIZE(cocos2d::CCAction *, deathAnimationAction, DeathAnimationAction);
    CC_SYNTHESIZE(cocos2d::CCAction *, currentAction, CurrentAction);
    CC_SYNTHESIZE(bool, vulnerable, Vulnerable);
    
public:
    ~Mira();
    
    cocos2d::CCRect adjustedBoundingBox();
    
    void checkAndClampSpritePosition();
    
    void changeState(CharacterState newState);
    
    void changeStateToIdle();
    
    void changeStateToSpawning();
    
    void changeStateToFlying();
    
    void changeStateToHit();
    
    void changeStateToDead();
    
    void changeToVulnerable();
    
    void changeToInvulnerable();
    
    void maxVelocity();
    
    void normalVelocity();
    
    void minVelocity();
    
    void initAnimations();
    
    bool init();
    
    void playSpawningSound();
    
    void playHitSound();
    
    void playDeadSound();
};

#endif /* defined(__TheAdventuresOfMira__Mira__) */
