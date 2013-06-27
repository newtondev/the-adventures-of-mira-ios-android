//
//  GameCharacter.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "GameCharacter.h"

using namespace cocos2d;

GameCharacter::~GameCharacter()
{
    
}

void GameCharacter::checkAndClampSpritePosition()
{
    CCLOG("GameCharacter->checkAndClampSpritePosition method should be overridden");
}

void GameCharacter::changeStateToIdle()
{
    CCLOG("GameCharacter->changeStateToIdle method should be overridden");
}

void GameCharacter::changeStateToSpawning()
{
    CCLOG("GameCharacter->changeStateToSpawning method should be overridden");
}

void GameCharacter::changeStateToFlying()
{
    CCLOG("GameCharacter->changeStateToFlying method should be overridden");
}

void GameCharacter::changeStateToHit()
{
    CCLOG("GameCharacter->changeStateToHit method should be overridden");
}

void GameCharacter::changeStateToDead()
{
    CCLOG("GameCharacter->changeStateToDead method should be overridden");
}
