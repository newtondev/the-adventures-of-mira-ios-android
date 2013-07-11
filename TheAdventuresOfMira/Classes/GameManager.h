//
//  GameManager.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__GameManager__
#define __TheAdventuresOfMira__GameManager__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "MainMenuLayer.h"
#include "AboutGameLayer.h"
#include "GameOverLayer.h"
#include "BackgroundLayer.h"
#include "GameSceneLayer.h"
#include "GameplayLayer.h"
#include <string>
#include <map>
#include <iostream>

/**
 * Responsible for the layers and the logic of the game.
 */
class GameManager : public cocos2d::CCObject
{
public:
    // Whether the music is enabled or disabled
    CC_SYNTHESIZE(bool, isMusicON, IsMusicON);
    // Whether the sound effects are enabled or disabled
    CC_SYNTHESIZE(bool, isSoundEffectsON, IsSoundEffectsON);
    // Has the player died?
    CC_SYNTHESIZE(bool, hasPlayerDied, HasPlayerDied);
    
    // The parallax scrolling background layer
    CC_SYNTHESIZE(BackgroundLayer *, backgroundLayer, BackgroundLayer);
    // The layer than contains the main menu and buttons
    CC_SYNTHESIZE(MainMenuLayer *, mainMenuLayer, MainMenuLayer);
    // The layer that contains the about game layer and buttons
    CC_SYNTHESIZE(AboutGameLayer *, aboutGameLayer, AboutGameLayer);
    // The layer that displays the game over screen and buttons
    CC_SYNTHESIZE(GameOverLayer *, gameOverLayer, GameOverLayer);
    // The layer that contains the game scene
    CC_SYNTHESIZE(GameSceneLayer *, gameSceneLayer, GameSceneLayer);
    // The layer that contains the gameplay elements
    CC_SYNTHESIZE(GameplayLayer *, gameplayLayer, GameplayLayer);
    
    // The current state the game is in i.e. playing, game over, etc
    CC_SYNTHESIZE(GameState, gameState, GameState);
    
    // The current velocity of flight
    CC_SYNTHESIZE(float, velocity, Velocity);
    
    // The current player score
    CC_SYNTHESIZE(long, score, Score);
    // The amount of lives the player has
    CC_SYNTHESIZE(long, lives, Lives);
    // The total distance travelled
    CC_SYNTHESIZE(long, distance, Distance);
    
    CC_SYNTHESIZE(GameDifficulty, gameDifficulty, GameDifficulty);
    
    CC_SYNTHESIZE(DeviceSize, deviceSize, DeviceSize);
    CC_SYNTHESIZE(DeviceType, deviceType, DeviceType);
    
protected:
    // Has the audio been initialized
    bool hasAudioBeenInitialized;
    // Our sound engine responsible for loading and playing music and sounds
    CocosDenshion::SimpleAudioEngine *soundEngine;
    
    // Our list of sound files retain!
    cocos2d::CCDictionary *listOfSoundEffectFiles;
    std::map<std::string, bool> *soundEffectsState;
    
    // The audio manager responsible for the music and sound
    CC_SYNTHESIZE(AudioManagerState, audioManagerState, AudioManagerState);
    // Check if Loading has finished
    CC_SYNTHESIZE(bool, hasFinishedLoading, HasFinishedLoading);
    
    CC_SYNTHESIZE(int, currentSong, CurrentSong);
    
    // public methods
public:
    // Constructor
    GameManager();
    // Destructor
    ~GameManager();
    
    // Singleton instance
    static GameManager *sharedGameManager();
    
    // Initialize the Game Manager
    bool init();
    
    // Show Main Menu
    void initMainMenu();
    void showMainMenu();
    
    // Show About Game Menu
    void initAboutGameMenu();
    void showAboutGame();
    
    // Start a new game
    void startNewGame();
    
    // End game
    void endGame();
    
    // Set the flight velocity to maximum
    void maxVelocity();
    // Set the flight velcoity to normal
    void normalVelocity();
    // Set the flight velocity to minimum
    void minVelocity();
    
    // Launches a new game obstacle
    void launchGameObstacle();
    
    // Generates a random float value between the low and high values specified
    static float randomValueBetween(float low, float high);
    
    // Generates a random int value between the low and high values specified
    static int randomIntValueBetween(int low, int high);
    
    // Purges the shared game manager and all objects and variable values
    static void purgeSharedGameManager();
    
    // Increases the player score by the amount specified
    void increaseScore(long amount);
    // Increases the distance travelled by the amount specified
    void increaseDistance(long amount);
    // Take a life from the player
    void takeLife();
    // Give a life to the player
    void giveLife();
    
    int getStartingLives();
    int getDifficulty();
    
    // Added for audio
    void initAudioAsync();
    void setupAudioEngine();
    //int playSoundEffect(const char *soundEffectKey);
    //void stopSoundEffect(int soundEffectID);
    void playBackgroundTrack(const char *trackFileName);
    void playRandomSong();
    //std::string formatSceneTypeToString(SceneTypes sceneID);
    //cocos2d::CCDictionary *getSoundEffectsListForSceneWithID(SceneTypes sceneID);
    //void loadAudioForSceneWithID(SceneTypes sceneID);
    //void unloadAudioForSceneWithID(SceneTypes sceneID);
};

#endif /* defined(__TheAdventuresOfMira__GameManager__) */
