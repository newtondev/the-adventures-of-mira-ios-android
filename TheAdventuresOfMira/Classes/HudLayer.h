//
//  HudLayer.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__HudLayer__
#define __TheAdventuresOfMira__HudLayer__

#include "cocos2d.h"
#include "Constants.h"
#include "CCParallaxScrollNode.h"

class HudLayer : public cocos2d::CCLayer
{
    CC_SYNTHESIZE(CCLabelBMFont *, livesLabel, LivesLabel);
    CC_SYNTHESIZE(CCLabelBMFont *, scoreLabel, ScoreLabel);
    CC_SYNTHESIZE(CCLabelBMFont *, distanceLabel, DistanceLabel);
    
public:
    CREATE_FUNC(HudLayer);
    virtual bool init();
};

#endif /* defined(__TheAdventuresOfMira__HudLayer__) */
