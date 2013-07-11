//
//  GameCharacter.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__GameCharacter__
#define __TheAdventuresOfMira__GameCharacter__

#include "GameObject.h"

class GameCharacter : public GameObject
{
    CC_SYNTHESIZE(CharacterState, characterState, CharacterState);
    CC_SYNTHESIZE(cocos2d::CCAction *, currentAction, CurrentAction);
    
    ~GameCharacter();
    virtual void checkAndClampSpritePosition();
    virtual void changeStateToIdle();
    virtual void changeStateToSpawning();
    virtual void changeStateToFlying();
    virtual void changeStateToHit();
    virtual void changeStateToDead();
};

#endif /* defined(__TheAdventuresOfMira__GameCharacter__) */
