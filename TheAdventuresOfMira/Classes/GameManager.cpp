//
//  GameManager.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "GameManager.h"
#include "GameSceneLayer.h"
#include "GameObstacle.h"
#include "HudLayer.h"

using namespace cocos2d;
using namespace std;

static GameManager *_sharedGameManager = NULL;
static bool s_bFirstRun = true;

GameManager::GameManager()
{
    listOfSoundEffectFiles = NULL;
    soundEffectsState = NULL;
}

GameManager::~GameManager()
{
    CC_SAFE_RELEASE_NULL(listOfSoundEffectFiles);
    //CC_SAFE_RELEASE(soundEffectsState);
}

void GameManager::purgeSharedGameManager()
{
    // safe release for sharedGameManager
    CC_SAFE_RELEASE_NULL(_sharedGameManager);
}

GameManager* GameManager::sharedGameManager()
{
    if (s_bFirstRun)
    {
        if (!_sharedGameManager)
        {
            _sharedGameManager = new GameManager();
            _sharedGameManager->init();
        }
        s_bFirstRun = false;
    }
    return _sharedGameManager;
}

bool GameManager::init()
{
    this->minVelocity();
    isMusicON = true;
    isSoundEffectsON = true;
    hasPlayerDied = false;
    hasFinishedLoading = false;
    hasAudioBeenInitialized = false;
    soundEngine = NULL;
    audioManagerState = kAudioManagerStateUninitialized;
    
    // Initialize layers, etc.
    this->setBackgroundLayer(BackgroundLayer::create());
    this->backgroundLayer->retain();
    this->backgroundLayer->setTag(kGameManager_BackgroundLayer);
    
    return true;
}

void GameManager::initMainMenu()
{
    if (aboutGameLayer != NULL) {
        aboutGameLayer = NULL;
    }
    
    this->setMainMenuLayer(MainMenuLayer::create());
    this->mainMenuLayer->retain();
    this->mainMenuLayer->setTag(kGameManager_MainMenuLayer);
}

void GameManager::initAboutGameMenu()
{
    
    /**
    if (mainMenuLayer != NULL) {
        if (mainMenuLayer->retainCount() > 0)
            mainMenuLayer->release();
        mainMenuLayer = NULL;
    }*/
    
    this->setAboutGameLayer(AboutGameLayer::create());
    this->aboutGameLayer->retain();
    this->aboutGameLayer->setTag(kGameManager_AboutGameLayer);
}

void GameManager::showAboutGame()
{
    if (this->getGameSceneLayer()->getChildByTag(kGameManager_MainMenuLayer) != NULL)
    {
        this->getGameSceneLayer()->removeChildByTag(kGameManager_MainMenuLayer, true);
    }
    
    initAboutGameMenu();
    gameSceneLayer->addChild(this->aboutGameLayer, 1);
}

void GameManager::showMainMenu()
{
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.35);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("song_intro.mp3", true);
    
    //gameSceneLayer->removeChildByTag(kGameManager_GameOverLayer, true);
    
    if (this->getGameSceneLayer()->getChildByTag(kGameManager_AboutGameLayer) != NULL)
    {
        gameSceneLayer->removeChildByTag(kGameManager_AboutGameLayer, true);
    }
    if (this->getGameSceneLayer()->getChildByTag(kGameManager_GameOverLayer) != NULL)
    {
        gameSceneLayer->removeChildByTag(kGameManager_GameOverLayer, true);
    }
    initMainMenu();
    gameSceneLayer->addChild(this->mainMenuLayer, 1);
}

void GameManager::startNewGame()
{
    // Play random music
    playRandomSong();
    
    // Remove GameOver Screen
    if (this->getGameSceneLayer()->getChildByTag(kGameManager_GameOverLayer) != NULL)
    {
        this->getGameSceneLayer()->removeChildByTag(kGameManager_GameOverLayer, true);
    }
    
    this->setGameplayLayer(GameplayLayer::create());
    this->gameplayLayer->retain();
    this->gameplayLayer->setTag(kGameManager_GameplayLayer);
    
    this->score = 0;
    this->lives = GameManager::sharedGameManager()->getStartingLives();
    this->distance = 0;
    
    if (this->getGameSceneLayer()->getChildByTag(kGameManager_MainMenuLayer) != NULL)
    {
        this->getGameSceneLayer()->removeChildByTag(kGameManager_MainMenuLayer, true);
    }
    this->getGameSceneLayer()->addChild(gameplayLayer);
    this->gameplayLayer->startNewGame();
}

void GameManager::endGame()
{
    if (this->getGameSceneLayer()->getChildByTag(kGameManager_GameplayLayer) != NULL)
    {
        this->getGameSceneLayer()->removeChildByTag(kGameManager_GameplayLayer, true);
    }
    
    this->setGameOverLayer(GameOverLayer::create());
    this->gameOverLayer->retain();
    this->gameOverLayer->setTag(kGameManager_GameOverLayer);
    
    this->getGameSceneLayer()->addChild(gameOverLayer);
}

void GameManager::maxVelocity()
{
    if (getGameDifficulty() == kGameDifficultyHard)
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kMaxScrollVelocity*0.9;
        }
        else
        {
            this->velocity = kMaxScrollVelocity*1.8;
        }
    }
    else if (getGameDifficulty() == kGameDifficultyMedium)
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kMaxScrollVelocity;
        }
        else
        {
            this->velocity = kMaxScrollVelocity*1;
        }
    }
    else
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kMaxScrollVelocity * 0.5;
        }
        else
        {
            this->velocity = kMaxScrollVelocity;
        }
    }
}

void GameManager::normalVelocity()
{
    if (getGameDifficulty() == kGameDifficultyHard)
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kNormalScrollVelocity;
        }
        else
        {
            this->velocity = kNormalScrollVelocity*1.8;
        }
    }
    else if (getGameDifficulty() == kGameDifficultyMedium)
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kNormalScrollVelocity*0.8;
        }
        else
        {
            this->velocity = kNormalScrollVelocity*1;
        }
    }
    else
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kNormalScrollVelocity * 0.5;
        }
        else
        {
            this->velocity = kNormalScrollVelocity;
        }
    }
}

void GameManager::minVelocity()
{
    if (getGameDifficulty() == kGameDifficultyHard)
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kMinScrollVelocity;
        }
        else
        {
            this->velocity = kMinScrollVelocity*1.8;
        }
    }
    else if (getGameDifficulty() == kGameDifficultyMedium)
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kMinScrollVelocity*0.8;
        }
        else
        {
            this->velocity = kMinScrollVelocity*1;
        }
    }
    else
    {
        if (getDeviceSize() == kDeviceSizeNormal || getDeviceSize() == kDeviceSizeSmall)
        {
            this->velocity = kMinScrollVelocity * 0.5;
        }
        else
        {
            this->velocity = kMinScrollVelocity;
        }
    }
}

void GameManager::launchGameObstacle()
{
    this->getGameplayLayer()->launchGameObstacle();
}

float GameManager::randomValueBetween(float low, float high)
{
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}

int GameManager::randomIntValueBetween(int low, int high)
{
    return (((int) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}

void GameManager::setupAudioEngine()
{
    if (hasAudioBeenInitialized == true)
    {
        return;
    }
    else
    {
        soundEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
        hasAudioBeenInitialized = true;
    }
}

void GameManager::initAudioAsync()
{
    
}

void GameManager::increaseScore(long amount)
{
    score = score + amount;
    HudLayer *hudLayer = (HudLayer *) gameplayLayer->getChildByTag(kHudLayer);
    hudLayer->getScoreLabel()->setString(CCString::createWithFormat("%i", score)->getCString());
}

void GameManager::increaseDistance(long amount)
{
    distance = distance + amount;
    HudLayer *hudLayer = (HudLayer *) gameplayLayer->getChildByTag(kHudLayer);
    hudLayer->getDistanceLabel()->setString(CCString::createWithFormat("%i", distance)->getCString());
}

void GameManager::takeLife()
{
    lives = lives - 1;
    HudLayer *hudLayer = (HudLayer *) gameplayLayer->getChildByTag(kHudLayer);
    hudLayer->getLivesLabel()->setString(CCString::createWithFormat("%i", lives)->getCString());
}

void GameManager::giveLife()
{
    lives = lives + 1;
    HudLayer *hudLayer = (HudLayer *) gameplayLayer->getChildByTag(kHudLayer);
    CCLabelTTF* livesLabel = (CCLabelTTF *) hudLayer->getChildByTag(kLabel_Lives);
    livesLabel->setString(CCString::createWithFormat("%i", lives)->getCString());
}

void GameManager::playBackgroundTrack(const char *trackFileName)
{
	if (soundEngine->isBackgroundMusicPlaying())
	{
		soundEngine->stopBackgroundMusic();
	}
    
	char filePath[100] = {0};
	sprintf(filePath, "%s", trackFileName);
	soundEngine->preloadBackgroundMusic(filePath);
	if (isMusicON == true)
		soundEngine->playBackgroundMusic(filePath, true);
}

void GameManager::playRandomSong()
{   
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
    
    // Generate a new randomSong number and make sure it is not the
    // previously played track.
    int randomSong = 0;
    while ((randomSong=(arc4random()%4)+1)==currentSong){}
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.35);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCString::createWithFormat("song_%i.mp3", randomSong)->getCString(), false);
    
    currentSong = randomSong;
}

int GameManager::getStartingLives()
{
    if (getGameDifficulty() == kGameDifficultyHard)
    {
        return 2;
    }
    else if (getGameDifficulty() == kGameDifficultyMedium)
    {
        return 4;
    }
    else
    {
        return 6;
    }
}

int GameManager::getDifficulty()
{
    switch (gameDifficulty)
    {
        case kGameDifficultyHard:
            return 3;
        case kGameDifficultyMedium:
            return 2;
        default:
            return 1;
    }
}
