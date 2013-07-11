//
//  GameplayLayer.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "GameplayLayer.h"
#include "HudLayer.h"
#include "GameManager.h"
#include "GameObstacle.h"
#include "CollectableItem.h"

using namespace cocos2d;

bool GameplayLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    
     CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    // scramble our random number generator
    srand(time(NULL));
    
    this->setKeypadEnabled(true);
    
    // Holds all the obstacles
    obstaclesLayer = CCLayer::create();
    addChild(obstaclesLayer, 2);
    
    // Holds all the items
    itemsLayer = CCLayer::create();
    addChild(itemsLayer, 1);
    
    this->scheduleUpdate();
    
    setSugarRushActive(false);
    
    return true;
}

void GameplayLayer::update(float dt)
{
    if (GameManager::sharedGameManager()->getGameState() == kGameStatePlayGame)
    {
        DeviceType device = GameManager::sharedGameManager()->getDeviceType();
        if (device == kDeviceTypeiPhone5 || device == kDeviceTypeiPhone4 || device == kDeviceTypeiPhone ||
            device == kDeviceTypeiPad3 || device == kDeviceTypeiPad)
        {
            miraEmitter->setSourcePosition(miraPlayer->getPosition());
        }
        
        checkCollisions();
        
        if (GameManager::sharedGameManager()->getGameState() == kGameStatePlayGame)
        {
            // Loop through updating position of game obstacles
            updateObstacles();
            
            // Loop through items updating position
            updateCollectables();
            
            performCleanup();
            
            // Sugar Rush
            if (sugarRushActive)
            {
                sugarRushTick--;
                if (sugarRushTick <= 0)
                {
                    resetSugarRush();
                }
            }
            
            // Magnet
            if (magnetActive)
            {
                magnetTick--;
                if (magnetTick <= 0)
                {
                    resetMagnet();
                }
            }
            
            // Increase distance
            if (distanceTick >= 50) {
                distanceTick = 0;
                if (sugarRushActive)
                {
                    GameManager::sharedGameManager()->increaseDistance(3);
                }
                else
                {
                    GameManager::sharedGameManager()->increaseDistance(1);
                }
            }
            distanceTick++;
        }
    }
    else if (GameManager::sharedGameManager()->getGameState() == kGameStateGameOver && miraPlayer != NULL)
    {
        DeviceType device = GameManager::sharedGameManager()->getDeviceType();
        if (device == kDeviceTypeiPhone5 || device == kDeviceTypeiPhone4 || device == kDeviceTypeiPhone ||
            device == kDeviceTypeiPad3 || device == kDeviceTypeiPad)
        {
            miraEmitter->setSourcePosition(miraPlayer->getPosition());
        }
        miraPlayer->setPosition(ccp(miraPlayer->getPosition().x-6.7, miraPlayer->getPosition().y-6));
        
        if (miraPlayer->getPosition().y <= -200)
        {
            GameManager::sharedGameManager()->minVelocity();
            miraPlayer->stopAllActions();
            this->removeChild(miraPlayer, true);
            GameManager::sharedGameManager()->endGame();
        }
    }
    
    // Check to make sure music is playing
    if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        GameManager::sharedGameManager()->playRandomSong();
    }
}

void GameplayLayer::updateObstacles()
{
    if (obstaclesLayer->getChildrenCount() > 0)
    {
        for (int i = 0; i < obstaclesLayer->getChildrenCount(); i++)
        {
            GameObstacle *obstacle = (GameObstacle *) obstaclesLayer->getChildren()->objectAtIndex(i);
            if (obstacle->getCharacterState() == kCharacterStateFlying || obstacle->getCharacterState() == kCharacterStateHit) {
                if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeNormal || GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeSmall)
                {
                    obstacle->setPosition(ccp(obstacle->getPosition().x+GameManager::sharedGameManager()->getVelocity()+(obstacle->getAdjustedVelocity()*0.5), obstacle->getPosition().y));
                }
                else
                {
                    obstacle->setPosition(ccp(obstacle->getPosition().x+GameManager::sharedGameManager()->getVelocity()+obstacle->getAdjustedVelocity(), obstacle->getPosition().y));
                }
            }
        }
    }
}

void GameplayLayer::updateCollectables()
{
    if (itemsLayer->getChildrenCount() > 0)
    {
        for (int i = 0; i < itemsLayer->getChildrenCount(); i++)
        {
            CollectableItem *item = (CollectableItem *) itemsLayer->getChildren()->objectAtIndex(i);
            if (!magnetActive)
            {
                item->setPosition(ccp(item->getPosition().x+GameManager::sharedGameManager()->getVelocity()+2, item->getPosition().y));
            }
            else
            {
                CCPoint curPos = item->getPosition();
                CCPoint miraPos = miraPlayer->getPosition();
                CCPoint newPos;
                                
                newPos.x = curPos.x - (curPos.x - miraPos.x) * 0.2;
                newPos.y = curPos.y - (curPos.y - miraPos.y) * 0.2;
                
                item->setPosition(newPos);
            }
        }
    }
}

void GameplayLayer::checkCollisions()
{
    CCRect miraBoundingBox = miraPlayer->adjustedBoundingBox();
    CharacterState miraState = miraPlayer->getCharacterState();
    
    // Check Obstacle Collisions
    if (miraState != kCharacterStateHit)
    {
        if (obstaclesLayer->getChildrenCount() > 0)
        {
            for (int i = 0; i < obstaclesLayer->getChildrenCount(); i++)
            {
                GameObstacle *obstacle = (GameObstacle *) obstaclesLayer->getChildren()->objectAtIndex(i);
                // Avoid the logic if the character has already been hit
                if (obstacle->getCharacterState() == kCharacterStateHit)
                    continue;
            
                if ((miraState == kCharacterStateFlying && miraPlayer->getVulnerable()) && obstacle->getCharacterState() == kCharacterStateFlying && miraBoundingBox.intersectsRect(obstacle->adjustedBoundingBox()))
                {
                    if (obstacle->getCharacterState() != kCharacterStateHit)
                    {
                        obstacle->changeState(kCharacterStateHit);
                        if (!sugarRushActive)
                        {
                            GameManager::sharedGameManager()->takeLife();
                        }
                        if (GameManager::sharedGameManager()->getLives() <= 0)
                        {
                            // Game is over
                            GameManager::sharedGameManager()->setGameState(kGameStateGameOver);
                            
                            // Set Mira to Dead
                            miraPlayer->changeState(kCharacterStateDead);
                            
                            // Unschedule selectors
                            this->unschedule(schedule_selector(GameplayLayer::launchGameObstacle));
                            this->unschedule(schedule_selector(GameplayLayer::launchCollectableItem));
                            
                            // todo force gameover action
                            obstaclesLayer->stopAllActions();
                            removeChild(obstaclesLayer, true);
                            itemsLayer->stopAllActions();
                            removeChild(itemsLayer, true);
                            
                            // Set Mira to Dead
                            miraPlayer->changeState(kCharacterStateDead);
                            
                            // Animate Mira going down
                            CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_thud.mp3", false);
                            return;
                        }
                        else
                        {
                            CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_thud.mp3", false);
                            if (!sugarRushActive)
                            {
                                miraPlayer->changeState(kCharacterStateHit);
                            }
                            else
                            {
                                // TODO popup score and fade out
                                GameManager::sharedGameManager()->increaseScore(100);
                                CCLabelBMFont *bonusLabel = CCLabelBMFont::create("100", "myGlyphs.fnt");
                                bonusLabel->setPosition(miraPlayer->getPosition());
                                addChild(bonusLabel, 99);
                                
                                CCActionInterval *scale = CCScaleTo::create(0.2f, 3.0f);
                                CCActionInterval *fade = CCFadeOut::create(0.2f);
                                CCSequence *actions = CCSequence::createWithTwoActions(scale, fade);
                                bonusLabel->runAction(CCSequence::createWithTwoActions(actions, CCCallFuncN::create(this,  callfuncN_selector(GameplayLayer::removeChildSpecified))));
                            }
                        }
                        if (!sugarRushActive)
                        {
                            this->cameraShakeAction();
                        }
                        break;
                    }
                }
            }
        }
    }
    
    // Check Item Collisions
    if (itemsLayer->getChildrenCount() > 0)
    {
        for (int i = 0; i < itemsLayer->getChildrenCount(); i++)
        {
            CollectableItem *item = (CollectableItem *) itemsLayer->getChildren()->objectAtIndex(i);
            if (miraBoundingBox.intersectsRect(item->adjustedBoundingBox()))
            {
                if (miraState != kCharacterStateHit)
                {
                    if (item->getGameObjectType() == kGameObjectTypePowerUpCandy)
                    {
                        activateSugarRush();
                    }
                    else if (item->getGameObjectType() == kGameObjectTypePowerUpMagnet)
                    {
                        activateMagnet();
                    }
                }
                
                // Increment the score
                if (item->getGameObjectType() != kGameObjectTypePowerUpMagnet && item->getGameObjectType() != kGameObjectTypePowerUpCandy)
                {
                    GameManager::sharedGameManager()->increaseScore(10);
                }
                
                // Play sound
                CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.3);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_collect.mp3", false);
                
                // Remove
                item->stopAllActions();
                itemsLayer->removeChild(item, true);
            }
        }
    }
}

void GameplayLayer::performCleanup()
{
    // Cleanup Obstacles
    if (obstaclesLayer->getChildrenCount() > 0)
    {
        for (int i = 0; i < obstaclesLayer->getChildrenCount(); i++)
        {
            GameObstacle *obstacle = (GameObstacle *) obstaclesLayer->getChildren()->objectAtIndex(i);
            if (obstacle->getPosition().x <= -200)
            {
                obstacle->stopAllActions();
                obstaclesLayer->removeChild(obstacle, true);
            }
        }
    }
    
    // Cleanup Items
    if (itemsLayer->getChildrenCount() > 0)
    {
        for (int i = 0; i < itemsLayer->getChildrenCount(); i++)
        {
            CollectableItem *item = (CollectableItem *) itemsLayer->getChildren()->objectAtIndex(i);
            if (item->getPosition().x <= -50)
            {
                item->stopAllActions();
                itemsLayer->removeChild(item, true);
            }
        }
    }
}

void GameplayLayer::addObstacle(float dt)
{
    
}

void GameplayLayer::startNewGame()
{
    distanceTick = 0;
    
    CCSprite *getReadySprite = CCSprite::createWithSpriteFrameName("get_ready.png");
    getReadySprite->setPosition(ccp(-getReadySprite->getContentSize().width, SCREEN_HEIGHT/2));
    getReadySprite->setTag(kGameplayLayer_GetReadySprite);
    
    CCFiniteTimeAction *actionSequence = CCSequence::create(
                                                            CCEaseIn::create(CCMoveTo::create(0.6f, ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)), 1.0f),
                                                            CCCallFunc::create(this, callfunc_selector(GameplayLayer::normalVelocity)),
                                                            CCDelayTime::create(1.0f),
                                                            CCEaseOut::create(CCMoveTo::create(0.6f, ccp(SCREEN_WIDTH*2, SCREEN_HEIGHT/2)), 1.0f),
                                                            CCCallFunc::create(this, callfunc_selector(GameplayLayer::initHud)),
                                                            CCCallFunc::create(this, callfunc_selector(GameplayLayer::initMiraPlayer)),
                                                            NULL
                                                        );
    getReadySprite->runAction(actionSequence);
    this->addChild(getReadySprite);
    
}

void GameplayLayer::normalVelocity()
{
    GameManager::sharedGameManager()->normalVelocity();
}

void GameplayLayer::createObjectOfType(GameObjectType objectType, cocos2d::CCPoint spawnLocation, int zValue)
{
    
}

void GameplayLayer::initHud()
{
    HudLayer *hudLayer = HudLayer::create();
    hudLayer->init();
    hudLayer->setTag(kHudLayer);
    hudLayer->setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT);
    
    CCActionInterval *moveToAction = CCMoveTo::create(0.6f, ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT-(hudLayer->getContentSize().height/2)));
    CCActionInterval *easeInAction = CCEaseIn::create(moveToAction, 1.0f);
    hudLayer->runAction(easeInAction);
    this->addChild(hudLayer);
}

void GameplayLayer::initMiraPlayer()
{
    Mira *mira = new Mira();
    this->setMiraPlayer(mira);
    miraPlayer->init();
    miraPlayer->retain();
    
    this->addChild(miraPlayer, 10, kMiraSpriteTagValue);
    
    DeviceType device = GameManager::sharedGameManager()->getDeviceType();
    if (device == kDeviceTypeiPhone5 || device == kDeviceTypeiPhone4 || device == kDeviceTypeiPhone ||
        device == kDeviceTypeiPad3 || device == kDeviceTypeiPad)
    {
        miraEmitter = CCParticleMeteor::create();
        miraEmitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("stars.png"));
        if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeXLarge || GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeLarge)
        {
            miraEmitter->setStartSize(40);
        }
        else
        {
            miraEmitter->setStartSize(20);
        }
        miraEmitter->setEndSize(2);
        miraEmitter->setRadialAccel(30);
        miraEmitter->setGravity(ccp(-1430, 0));
        miraEmitter->setPosition(miraPlayer->getPosition());
        this->addChild(miraEmitter);
    }
    
    miraPlayer->setPosition(ccp(-(miraPlayer->getContentSize().width*2), SCREEN_HEIGHT/2));
    CCActionInterval *moveMiraIn = CCMoveTo::create(0.3f, ccp(SCREEN_WIDTH*0.20, SCREEN_HEIGHT/2));
    CCFiniteTimeAction *moveInEffect = CCEaseIn::create(moveMiraIn, 1.0f);
    CCFiniteTimeAction *initGameplayAction = CCCallFuncN::create(this, callfuncN_selector(GameplayLayer::initGameplay));
    CCSequence *sequence = CCSequence::createWithTwoActions(moveInEffect, initGameplayAction);
    miraPlayer->runAction(sequence);
}

void GameplayLayer::initGameplay()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_laugh.mp3", false);
    
    GameManager::sharedGameManager()->setGameState(kGameStatePlayGame);
    
    this->schedule(schedule_selector(GameplayLayer::launchGameObstacle), GameManager::randomValueBetween(2.0f, 3.0f));
    this->schedule(schedule_selector(GameplayLayer::launchCollectableItem), 0.3f);
}

void GameplayLayer::launchCollectableItem()
{
    int collectableItemType = (arc4random() % 5) + 1;
    if ((arc4random() % 10) == 5) {
        if ((arc4random() % 10) <= 2) {
            collectableItemType = 7-(arc4random() % 2);
        }
    }
    
    GameObjectType type = kGameObjectTypeCollectableFlower1;
    switch (collectableItemType) {
        case 2:
            type = kGameObjectTypeCollectableFlower2;
            break;
        case 3:
            type = kGameObjectTypeCollectableFlower3;
            break;
        case 4:
            type = kGameObjectTypeCollectableFlower4;
            break;
        case 5:
            type = kGameObjectTypeCollectableFlower5;
            break;
        case 6:
            type = kGameObjectTypePowerUpCandy;
            break;
        case 7:
            type = kGameObjectTypePowerUpMagnet;
            break;
            
        default:
            type = kGameObjectTypeCollectableFlower1;
            break;
    }
    
    CollectableItem *item = CollectableItem::create(type);
    switch (pattern) {
        case 1:     // Horizontal alignment on the top
            if (patternCount == 0) {
                // Choose a Y value above the middle
                lastYPos = GameManager::randomValueBetween(((float)SCREEN_HEIGHT*0.12), ((float)SCREEN_HEIGHT-(SCREEN_HEIGHT*0.211)));
                patternCount++;
            } else if (patternCount >= 10) {
                changePattern();
            } else {
                patternCount++;
            }
            item->setPosition(ccp(SCREEN_WIDTH+50, lastYPos));
            break;
        // ------------
        case 2:     // ZigZag
            if (patternCount == 0) {
                lastYPos = GameManager::randomValueBetween(((float)SCREEN_HEIGHT*0.12), ((float)SCREEN_HEIGHT-(SCREEN_HEIGHT*0.211)));
                patternCount++;
                int mid = ((float)SCREEN_HEIGHT-(SCREEN_HEIGHT*0.211))/2;
                if (lastYPos > mid) {
                    // going up
                    patternDirection = 0;
                } else {
                    // going down
                    patternDirection = 1;
                }
            } else if (patternCount >= 20) {
                changePattern();
            } else {
                if (patternDirection == 0) {
                    if ((lastYPos - item->getContentSize().height) < (SCREEN_HEIGHT*0.12)) {
                        // go down
                        patternDirection = 1;
                    }
                } else {
                    if ((lastYPos + item->getContentSize().height) > (((float)SCREEN_HEIGHT-(SCREEN_HEIGHT*0.211)))) {
                        // go up
                        patternDirection = 0;
                    }
                }
                if (patternDirection == 0) {
                    lastYPos = lastYPos - item->getContentSize().height;
                } else {
                    lastYPos = lastYPos + item->getContentSize().height;
                }
                
                patternCount++;
            }
            item->setPosition(ccp(SCREEN_WIDTH+50, lastYPos));
            break;
        default:
            float randYPos = GameManager::randomValueBetween(((float)SCREEN_HEIGHT*0.12), ((float)SCREEN_HEIGHT-(SCREEN_HEIGHT*0.211)));
            item->setPosition(ccp(SCREEN_WIDTH+50, randYPos));
            
            patternCount++;
            
            if (patternCount > 20) {
                changePattern();
            }
    }
    
    itemsLayer->addChild(item);
    item->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
}

void GameplayLayer::changePattern()
{
    pattern = arc4random()%3;
    patternCount = 0;
}

void GameplayLayer::launchGameObstacle()
{
    int obstacleType = (arc4random() % 5) + 1;
    GameObjectType type = kGameObjectTypeObstacleRedBird;
    switch (obstacleType) {
        case 2:
            type = kGameObjectTypeObstacleBlueBird;
            break;
            
        case 3:
            type = kGameObjectTypeObstacleBat;
            break;
            
        case 4:
            type = kGameObjectTypeObstacleSquirrel;
            break;
            
        case 5:
            type = kGameObjectTypeObstacleLadyBug;
            break;
            
        default:
            type = kGameObjectTypeObstacleRedBird;
            break;
    }
    
    GameObstacle *obstacle = GameObstacle::create(type);
    obstacle->changeState(kCharacterStateIdle);
    obstaclesLayer->addChild(obstacle);
    
    float randYPos = GameManager::randomValueBetween(((float)SCREEN_HEIGHT*0.12), ((float)SCREEN_HEIGHT-(SCREEN_HEIGHT*0.211)));
    obstacle->setPosition(ccp(SCREEN_WIDTH*0.9, randYPos));
    
    CCFiniteTimeAction *changeToSpawningState = CCCallFunc::create(obstacle, callfunc_selector(GameObstacle::changeStateToSpawning));
    CCActionInterval *delaySpawningInterval = CCSequence::createWithTwoActions(CCDelayTime::create(GameManager::randomValueBetween(2.0f, 5.0f)), changeToSpawningState);
    
    CCFiniteTimeAction *changeToFlyingState = CCCallFunc::create(obstacle, callfunc_selector(GameObstacle::changeStateToFlying));
    CCActionInterval *delayFlyingInterval = CCSequence::createWithTwoActions(CCDelayTime::create(3.0f), changeToFlyingState);
    
    this->runAction(CCSequence::createWithTwoActions(delaySpawningInterval, delayFlyingInterval));
}

// DEBUG ONLY
void GameplayLayer::draw()
{
    CCLayer::draw();
    
    /**
    if (GameManager::sharedGameManager()->getGameState() == kGameStatePlayGame)
    {
        if (this->getChildByTag(kMiraSpriteTagValue)) {
            CCRect miraBoundingBox = miraPlayer->adjustedBoundingBox();
            drawPoly(miraBoundingBox);
        }
    
        if (obstaclesLayer && obstaclesLayer->getChildrenCount() > 0)
        {
            for (int i = 0; i < obstaclesLayer->getChildrenCount(); i++)
            {
                GameObstacle *obstacle = (GameObstacle *) obstaclesLayer->getChildren()->objectAtIndex(i);
                drawPoly(obstacle->adjustedBoundingBox());
            }
        }
    
        if (itemsLayer && itemsLayer->getChildrenCount() > 0)
        {
            for (int i = 0; i < itemsLayer->getChildrenCount(); i++)
            {
                CollectableItem *item = (CollectableItem *) itemsLayer->getChildren()->objectAtIndex(i);
                drawPoly(item->adjustedBoundingBox());
            }
        }
    }
     */
}

void GameplayLayer::drawPoly(const CCRect rect)
{    
    // draw bounding box
    CCPoint vertices[4] = {
        ccp(rect.origin.x, rect.origin.y),
        ccp(rect.origin.x+rect.size.width, rect.origin.y),
        ccp(rect.origin.x+rect.size.width, rect.origin.y+rect.size.height),
        ccp(rect.origin.x, rect.origin.y+rect.size.height ),
    };
    ccDrawPoly(vertices, 4, true);
}

void GameplayLayer::translateMiraPosition(CCPoint translation)
{
    if (this->miraPlayer->getCharacterState() == kCharacterStateHit)
        return;
    
    CCPoint newPos = ccpAdd(this->miraPlayer->getPosition(), translation);
    float minY = SCREEN_HEIGHT * 0.12;
    float maxY = SCREEN_HEIGHT - (SCREEN_HEIGHT*0.211);
    float minX = SCREEN_WIDTH * 0.14;
    float maxX = SCREEN_WIDTH - (SCREEN_WIDTH * 0.22);
    if (newPos.x < minX) {
        newPos.x = minX;
    } else if (newPos.x > maxX) {
        newPos.x = maxX;
    }
    if (newPos.y < minY) {
        newPos.y = minY;
    } else if (newPos.y > maxY) {
        newPos.y = maxY;
    }
    
    float rotation = -(translation.y * 1.4);
    if (rotation > 20.0f) {
        rotation = 20.0f;
    } else if (rotation < -20.0f) {
        rotation = -20.0f;
    }
    
    this->miraPlayer->setRotation(rotation);
    this->miraPlayer->setPosition(newPos);
}

bool GameplayLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void GameplayLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (miraPlayer != NULL && GameManager::sharedGameManager()->getGameState() == kGameStatePlayGame) {
        CCPoint touchLocation = this->convertTouchToNodeSpace(pTouch);
        CCPoint oldTouchLocation = pTouch->getPreviousLocationInView();
        oldTouchLocation = CCDirector::sharedDirector()->convertToGL(oldTouchLocation);
        oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);
        
        CCPoint translation = ccpSub(touchLocation, oldTouchLocation);
        this->translateMiraPosition(translation);
    }
}

void GameplayLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (miraPlayer != NULL && GameManager::sharedGameManager()->getGameState() == kGameStatePlayGame) {
        CCAction * rotateAction = CCRotateTo::create(0.15, 0);
        this->miraPlayer->runAction(rotateAction);
    }
}

void GameplayLayer::cameraShakeAction()
{
    CCFiniteTimeAction *cameraShakeFunc = CCCallFunc::create(this, callfunc_selector(GameplayLayer::cameraShake));
    CCActionInterval *shakeSeq = CCSequence::createWithTwoActions(CCDelayTime::create(0.023f), cameraShakeFunc);
    CCActionInterval *shakeItUp = CCRepeat::create(shakeSeq, 4);
    this->runAction(shakeItUp);
}

void GameplayLayer::cameraShake()
{
    BackgroundLayer *backgroundLayer = GameManager::sharedGameManager()->getBackgroundLayer();
    CCPoint backgroundPosition = backgroundLayer->getPosition();
    
    if (backgroundLayer->getScale() == 1.05f) {
        backgroundLayer->setScale(1.0f);
    }
    else
    {
        backgroundLayer->setScale(1.05f);
    }
    
    if (this->getScale() == 1.05f) {
        this->setScale(1.0f);
    }
    else
    {
        this->setScale(1.05f);
    }
}

void GameplayLayer::activateSugarRush()
{
    sugarRushTick = kMiraSugarRushTime;
    setSugarRushActive(true);
    GameManager::sharedGameManager()->maxVelocity();
    GameManager::sharedGameManager()->getBackgroundLayer()->showWind();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_laugh.mp3", false);
}

void GameplayLayer::resetSugarRush()
{
    sugarRushTick = kMiraSugarRushTime;
    GameManager::sharedGameManager()->normalVelocity();
    setSugarRushActive(false);
    GameManager::sharedGameManager()->getBackgroundLayer()->hideWind();
}

void GameplayLayer::activateMagnet()
{
    magnetTick = kMiraMagnetTime;
    setMagnetActive(true);
}

void GameplayLayer::resetMagnet()
{
    magnetTick = kMiraMagnetTime;
    setMagnetActive(false);
}

void GameplayLayer::removeChildSpecified(cocos2d::CCNode *sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite, true);
}
