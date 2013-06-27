//
//  GameOverLayer.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "GameOverLayer.h"
#include "Constants.h"
#include "GameManager.h"

using namespace cocos2d;

// Initialize our Main Menu Layer, and add the initial main menu with the title screen, play button and about button.
bool GameOverLayer::init()
{
    // Initialize the parent
    if (!CCLayer::init()) return false;
    
    // Load the high scores
    CCUserDefault *store = CCUserDefault::sharedUserDefault();
    int bestScore = store->getIntegerForKey("best-score", 0);
    int bestDistance = store->getIntegerForKey("best-distance", 0);
    int bestDifficulty = store->getIntegerForKey("best-difficulty", 0);
    bool newRecord = false;
    
    if (GameManager::sharedGameManager()->getScore() > bestScore && GameManager::sharedGameManager()->getDistance() > bestDistance)
    {
        bestScore = GameManager::sharedGameManager()->getScore();
        bestDistance = GameManager::sharedGameManager()->getDistance();
        bestDifficulty = GameManager::sharedGameManager()->getDifficulty();
        store->setIntegerForKey("best-score", bestScore);
        store->setIntegerForKey("best-distance", bestDistance);
        store->setIntegerForKey("best-difficulty", bestDifficulty);
        store->flush();
        newRecord = true;
    }
    
    // Set the screen size to the full dimensions of the device (full screen)
    this->setContentSize(SCREEN_SIZE);
    
    float labelScaleText = 1.2f;
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid854x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x400 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid720x480)
    {
        labelScaleText = 0.9f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeNormal)
    {
        labelScaleText = 1.0f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeSmall)
    {
        labelScaleText = 0.5f;
    }
    
    CCSprite *gameOverTitle = CCSprite::createWithSpriteFrameName("game_over.png");
    gameOverTitle->setScale(0.9f);
    gameOverTitle->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.8));
    this->addChild(gameOverTitle);
    
    CCString *score = CCString::createWithFormat("YOUR SCORE: %i", GameManager::sharedGameManager()->getScore());
    CCLabelBMFont *scoreLabel = CCLabelBMFont::create(score->getCString(), "myGlyphs.fnt");
    scoreLabel->setScale(labelScaleText);
    scoreLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.65));
    this->addChild(scoreLabel);
    
    CCString *distance = CCString::createWithFormat("YOUR DISTANCE: %i", GameManager::sharedGameManager()->getDistance());
    CCLabelBMFont *distanceLabel = CCLabelBMFont::create(distance->getCString(), "myGlyphs.fnt");
    distanceLabel->setScale(labelScaleText);
    distanceLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.59));
    this->addChild(distanceLabel);
    
    CCString *ydifficulty;
    switch (GameManager::sharedGameManager()->getDifficulty())
    {
        case 3:
            ydifficulty = CCString::create("HARD");
            break;
        case 2:
            ydifficulty = CCString::create("MEDIUM");
            break;
        default:
            ydifficulty = CCString::create("EASY");
    }
    
    CCString *difficulty = CCString::createWithFormat("YOUR DIFFICULTY: %s", ydifficulty->getCString());
    CCLabelBMFont *difficultyLabel = CCLabelBMFont::create(difficulty->getCString(), "myGlyphs.fnt");
    difficultyLabel->setScale(labelScaleText);
    difficultyLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.53));
    this->addChild(difficultyLabel);
    
    CCString *highScore = CCString::createWithFormat("HIGH SCORE: %i", bestScore);
    CCLabelBMFont *highScoreLabel = CCLabelBMFont::create(highScore->getCString(), "myGlyphs.fnt");
    highScoreLabel->setScale(labelScaleText);
    highScoreLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.43));
    this->addChild(highScoreLabel);
    
    CCString *highDistance = CCString::createWithFormat("BEST DISTANCE: %i", bestDistance);
    CCLabelBMFont *highDistanceLabel = CCLabelBMFont::create(highDistance->getCString(), "myGlyphs.fnt");
    highDistanceLabel->setScale(labelScaleText);
    highDistanceLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.37));
    this->addChild(highDistanceLabel);
    
    CCString *bdifficulty;
    switch (bestDifficulty)
    {
        case 3:
            bdifficulty = CCString::create("HARD");
            break;
        case 2:
            bdifficulty = CCString::create("MEDIUM");
            break;
        default:
            bdifficulty = CCString::create("EASY");
    }
    
    CCString *highDifficulty = CCString::createWithFormat("DIFFICULTY: %s", bdifficulty->getCString());
    CCLabelBMFont *highDifficultyLabel = CCLabelBMFont::create(highDifficulty->getCString(), "myGlyphs.fnt");
    highDifficultyLabel->setScale(labelScaleText);
    highDifficultyLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.31));
    this->addChild(highDifficultyLabel);
    
    // Play again button
    createPlayAgainButton();
    
    // Play Game Over Sound
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_gameover.mp3", false);
    
    // Do new record animation
    if (newRecord)
    {
        // TODO
    }
    
    // Initialization was successful
    return true;
}

void GameOverLayer::createPlayAgainButton()
{
    // Create the startButton
    CCSprite *playAgainButtonSpriteUp = CCSprite::createWithSpriteFrameName("playagain_button.png");
    CCSprite *playAgainButtonSpriteDown = CCSprite::createWithSpriteFrameName("playagain_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    playAgainButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *playAgainButton = CCMenuItemSprite::create(playAgainButtonSpriteUp, playAgainButtonSpriteDown, this, menu_selector(GameOverLayer::playAgainButtonTouched));
    playAgainButton->setPositionX(-playAgainButton->getContentSize().width/1.2);
    playAgainButton->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleTo::create(1.0f, 1.2f), CCScaleTo::create(1.0f, 1.0f))));
    
    // Create the mainButton
    CCSprite *mainButtonSpriteUp = CCSprite::createWithSpriteFrameName("main_button.png");
    CCSprite *mainButtonSpriteDown = CCSprite::createWithSpriteFrameName("main_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    mainButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *mainButton = CCMenuItemSprite::create(mainButtonSpriteUp, mainButtonSpriteDown, this, menu_selector(GameOverLayer::mainButtonTouched));
    mainButton->setPositionX(mainButton->getContentSize().width/1.2);
    
    // Create the start game menu
    CCMenu *gameMenu = CCMenu::create(playAgainButton, mainButton, NULL);
    // Set the initial position off screen
    gameMenu->setPosition(ccp(SCREEN_WIDTH/2, -SCREEN_HEIGHT));
    // Set the tag of the start menu so that we can refer to it later using getChildByTag(...)
    gameMenu->setTag(kGameOverLayer_PlayAgainMenu);
    
    // Create and run an animation that will slide the start game menu in from below the screen to its intended location
    CCActionInterval *moveAction = CCMoveTo::create(0.3f, ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.15));
    CCFiniteTimeAction *easeIn = CCEaseIn::create(moveAction, 0.2f);
    gameMenu->runAction(easeIn);
    
    // Add the start menu to the layer
    this->addChild(gameMenu);
}

void GameOverLayer::playAgainButtonTouched()
{
    GameManager::sharedGameManager()->startNewGame();
}

void GameOverLayer::mainButtonTouched()
{
    this->getChildByTag(kGameOverLayer_PlayAgainMenu)->stopAllActions();
    GameManager::sharedGameManager()->showMainMenu();
}
