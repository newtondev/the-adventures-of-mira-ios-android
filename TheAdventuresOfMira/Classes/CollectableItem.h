//
//  CollectableItem.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/15.
//
//

#ifndef __TheAdventuresOfMira__CollectableItem__
#define __TheAdventuresOfMira__CollectableItem__

#include "GameObject.h"

class CollectableItem : public GameObject
{
public:
    static CollectableItem *create(GameObjectType gameObjectType);
    
    ~CollectableItem();
    
    void changeState(CharacterState newState);
    
    cocos2d::CCRect adjustedBoundingBox();
    
    void checkAndClampSpritePosition();
    
    bool init(GameObjectType type);
    
    void initSprite();
};

#endif /* defined(__TheAdventuresOfMira__CollectableItem__) */
