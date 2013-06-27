//
//  GameplayLayer.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__GameplayLayer__
#define __TheAdventuresOfMira__GameplayLayer__

#include "cocos2d.h"
#include "Constants.h"
#include "Mira.h"

class GameplayLayer : public cocos2d::CCLayer, public GameplayLayerDelegate
{
    CC_SYNTHESIZE(Mira *, miraPlayer, MiraPlayer);
    CC_SYNTHESIZE(CCLayer *, obstaclesLayer, ObstaclesLayer);
    CC_SYNTHESIZE(CCLayer *, itemsLayer, ItemsLayer);
    CC_SYNTHESIZE(long, distanceTick, DistanceTick);
    
    CC_SYNTHESIZE(bool, sugarRushActive, SugarRushActive);
    CC_SYNTHESIZE(long, sugarRushTick, SugarRushTick);
    
    CC_SYNTHESIZE(bool, magnetActive, MagnetActive);
    CC_SYNTHESIZE(long, magnetTick, MagnetTick);
    
    CC_SYNTHESIZE(cocos2d::CCParticleMeteor *, miraEmitter, miraEmitter);

    CC_SYNTHESIZE(int, lastYPos, LastYPos);
    CC_SYNTHESIZE(int, patternCount, PatternCount);
    CC_SYNTHESIZE(int, patternDirection, PatternDirection);
    CC_SYNTHESIZE(int, pattern, Pattern);
    
public:
    CREATE_FUNC(GameplayLayer);
    
    virtual bool init();
    
    void update(float dt);
    
    void addObstacle(float dt);
    
    void startNewGame();
    
    void launchCollectableItem();
    
    void launchGameObstacle();
    
    void initHud();
    
    void initMiraPlayer();
    
    void initGameplay();
    
    void checkCollisions();
    
    void updateObstacles();
    
    void updateCollectables();
    
    void cameraShakeAction();
    
    void cameraShake();
    
    void performCleanup();
    
    void normalVelocity();
    
    void draw();
    
    void changePattern();
    
    void removeChildSpecified(cocos2d::CCNode *sender);
    
    static void drawPoly(const cocos2d::CCRect rect);
    
    void translateMiraPosition(cocos2d::CCPoint translation);
    
    virtual void createObjectOfType(GameObjectType objectType, cocos2d::CCPoint spawnLocation, int zValue);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void resetSugarRush();
    void activateSugarRush();
    
    void resetMagnet();
    void activateMagnet();
};

#endif /* defined(__TheAdventuresOfMira__GameplayLayer__) */
