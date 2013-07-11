//
//  GameOverLayer.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__GameOverLayer__
#define __TheAdventuresOfMira__GameOverLayer__

#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayer
{
private:
    void createPlayAgainButton();
public:
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
    void playAgainButtonTouched();
    void mainButtonTouched();
};

#endif /* defined(__TheAdventuresOfMira__GameOverLayer__) */
