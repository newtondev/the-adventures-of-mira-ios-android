//
//  CCParallaxScrollOffset.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__CCParallaxScrollOffset__
#define __TheAdventuresOfMira__CCParallaxScrollOffset__

#include "cocos2d.h"
using namespace cocos2d;

class CCParallaxScrollOffset : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(CCParallaxScrollOffset);
    //
    CC_SYNTHESIZE(CCPoint, scrollOffset, ScrollOffset);
    CC_SYNTHESIZE(CCPoint, origPosition, OrigPosition);
    CC_SYNTHESIZE(CCPoint, relVelocity, RelVelocity);
    CC_SYNTHESIZE(CCPoint, ratio, Ratio);
    CC_SYNTHESIZE(CCPoint, buffer, Buffer);
    CC_SYNTHESIZE(CCNode*, theChild, TheChild);
    
    static CCParallaxScrollOffset* scrollWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s);
    static CCParallaxScrollOffset* scrollWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s, CCPoint v);
    CCParallaxScrollOffset* initWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s, CCPoint v);
    CCParallaxScrollOffset* initWithNode(CCNode *node, CCPoint r, CCPoint p, CCPoint s);
};

#endif /* defined(__TheAdventuresOfMira__CCParallaxScrollOffset__) */
