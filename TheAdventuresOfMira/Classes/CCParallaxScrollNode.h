//
//  CCParallaxScrollNode.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__CCParallaxScrollNode__
#define __TheAdventuresOfMira__CCParallaxScrollNode__

#include "cocos2d.h"
#include "CCParallaxScrollOffset.h"

using namespace cocos2d;

class CCParallaxScrollNode : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(CCParallaxScrollNode);
    
    CCSpriteBatchNode batch;
    CCSize _range;
    CCArray *_scrollOffsets;
    
    void addChild(CCSprite *node, int z, CCPoint r, CCPoint p, CCPoint so);
    void addChild(CCSprite *node, int z, CCPoint r, CCPoint p, CCPoint so, CCPoint v);
    
    void removeChild(CCSprite *node, bool cleanup);
    void updateWithVelocity(CCPoint vel, float dt);
    void updateWithYPosition(float y, float dt);
    
    void addInfiniteScrollWithZ(int z, CCPoint ratio, CCPoint pos, CCPoint dir, CCSprite *firstObject, ...);
    void addInfiniteScrollXWithZ(int z, CCPoint ratio, CCPoint pos, CCSprite* firstObject, ...);
    void addInfiniteScrollYWithZ(int z,  CCPoint ratio, CCPoint pos, CCSprite* firstObject, ...);
    
    void addInfiniteScrollWithObjects(CCArray *objects, int z, CCPoint ratio, CCPoint pos, CCPoint dir);
    void addInfiniteScrollWithObjects(CCArray *objects, int z, CCPoint ratio, CCPoint pos, CCPoint dir, CCPoint relVel);
    void addInfiniteScrollWithObjects(CCArray *objects, int z, CCPoint ratio, CCPoint pos, CCPoint dir, CCPoint relVel, CCPoint padding);
    
};

#endif /* defined(__TheAdventuresOfMira__CCParallaxScrollNode__) */
