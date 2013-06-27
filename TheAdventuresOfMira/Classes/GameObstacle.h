//
//  GameObstacle.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/10.
//
//

#ifndef __TheAdventuresOfMira__GameObstacle__
#define __TheAdventuresOfMira__GameObstacle__

#include "GameCharacter.h"
#include "Mira.h"

class GameObstacle : public GameCharacter
{
    CC_SYNTHESIZE(float, adjustedVelocity, AdjustedVelocity);
    CC_SYNTHESIZE(cocos2d::CCAction *, spawningAnimationAction, SpawningAnimationAction);
    CC_SYNTHESIZE(cocos2d::CCAction *, flyingAnimationAction, FlyingAnimationAction);
    CC_SYNTHESIZE(cocos2d::CCAction *, hitAnimationAction, HitAnimationAction);
    CC_SYNTHESIZE_PASS_BY_REF(Mira, miraPlayer, MiraPlayer);
    
public:
    static GameObstacle *create(GameObjectType gameObjectType);
    
    ~GameObstacle();
    
    cocos2d::CCRect adjustedBoundingBox();
    
    void checkAndClampSpritePosition();
    
    void changeState(CharacterState newState);
    
    void changeStateToIdle();
    
    void changeStateToSpawning();
    
    void changeStateToFlying();
    
    void changeStateToHit();
    
    void changeStateToDead();
    
    void initAnimations();
    
    bool init(GameObjectType type);
    
    void playSpawningSound();
    
    void playHitSound();
    
    void playDeadSound();
    
    void update(float dt);
};

#endif /* defined(__TheAdventuresOfMira__GameObstacle__) */
