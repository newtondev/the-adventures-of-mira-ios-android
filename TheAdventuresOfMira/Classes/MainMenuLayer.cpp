//
//  MainMenuLayer.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "MainMenuLayer.h"
#include "Constants.h"
#include "GameManager.h"

using namespace cocos2d;

// Initialize our Main Menu Layer, and add the initial main menu with the title screen, play button and about button.
bool MainMenuLayer::init()
{
    // Initialize the parent
    if (!CCLayer::init()) return false;
    
    // Set the screen size to the full dimensions of the device (full screen)
    this->setContentSize(SCREEN_SIZE);
    
    // Create and show the Main Menu
    this->addMainMenuChildren();
    
    // Initialization was successful
    return true;
}

// Create, initialize, add to layer and perform the initial animation for the Main Menu.
void MainMenuLayer::addMainMenuChildren()
{
    // Create and initialze the game title sprite
    CCSprite *title = (CCSprite::createWithSpriteFrameName("game_title.png"));
    // Set the tag of the game title so that we can refer to it later using getChildByTag(...)
    title->setTag(kMainMenuLayer_TitleSprite);
    // Set the initial position of the game title
    title->setPosition(ccp(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.6));
    title->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleTo::create(1.0f, 1.1f), CCScaleTo::create(1.0f, 1.0f))));
    
    // Create the playButton
    CCSprite *playButtonSpriteUp = CCSprite::createWithSpriteFrameName("play_button.png");
    CCSprite *playButtonSpriteDown = CCSprite::createWithSpriteFrameName("play_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    playButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *playGameButton = CCMenuItemSprite::create(playButtonSpriteUp, playButtonSpriteDown, this, menu_selector(MainMenuLayer::playGameButtonTouched));
    
    // Create the aboutButton
    CCSprite *aboutButtonSpriteUp = CCSprite::createWithSpriteFrameName("about_button.png");
    CCSprite *aboutButtonSpriteDown = CCSprite::createWithSpriteFrameName("about_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    aboutButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *aboutGameButton = CCMenuItemSprite::create(aboutButtonSpriteUp, aboutButtonSpriteDown, this, menu_selector(MainMenuLayer::aboutGameButtonTouched));
    
    // Create the main menu and add the buttons to it
    CCMenu *gameMenu = CCMenu::create(playGameButton, aboutGameButton, NULL);
    gameMenu->alignItemsHorizontallyWithPadding(playButtonSpriteUp->getContentSize().width/1.2);
    gameMenu->setPosition(ccp(SCREEN_SIZE.width*0.7f, -playButtonSpriteUp->getContentSize().height*2));
    // Set the tag of the main menu so that we can refer to it later using getChildByTag(...)
    gameMenu->setTag(kMainMenuLayer_MainMenu);
    
    // Add the title to the layer
    this->addChild(title);
    // Add the main menu to the layer
    this->addChild(gameMenu);
    
    // Create an action that makes the main menu animate coming up from below the screen to its intended position
    CCActionInterval *moveAction = CCMoveTo::create(1.0f, ccp(SCREEN_SIZE.width*0.7f, SCREEN_SIZE.height*0.15f));
    CCActionInterval *easeAction = CCEaseIn::create(moveAction, 1.0f);
    gameMenu->runAction(easeAction);
}

// Animate the main menu items to slide out and remove the main menu children from the layer and cleanup.
void MainMenuLayer::removeMainMenuChildren()
{
    // Find the game title sprite and create an animation where it slides out the right of the screen
    CCSprite *title = (CCSprite *) this->getChildByTag(kMainMenuLayer_TitleSprite);
    CCActionInterval *moveAction = CCMoveTo::create(0.3f, ccp(SCREEN_WIDTH+100, title->getPosition().y));
    CCFiniteTimeAction *easeOut = CCEaseOut::create(moveAction, 0.2f);
    CCFiniteTimeAction *removeTitle = CCCallFuncN::create(this, callfuncN_selector(MainMenuLayer::removeGameTitle));
    CCSequence *titleOut = CCSequence::createWithTwoActions(easeOut, removeTitle);
    title->runAction(titleOut);
    
    // Find the main menu and create an animation where it slides out the right of the screen
    CCMenu *gameMenu = (CCMenu *)this->getChildByTag(kMainMenuLayer_MainMenu);
    CCActionInterval *mmoveAction = CCMoveTo::create(0.3f, ccp(SCREEN_WIDTH+100, gameMenu->getPosition().y));
    CCFiniteTimeAction *measeOut = CCEaseOut::create(mmoveAction, 0.2f);
    CCFiniteTimeAction *mremoveTitle = CCCallFuncN::create(this, callfuncN_selector(MainMenuLayer::removeGameMenu));
    CCSequence *mtitleOut = CCSequence::createWithTwoActions(measeOut, mremoveTitle);
    gameMenu->runAction(mtitleOut);
}

// Removes the MainMenuTitle from the layer.
void MainMenuLayer::removeGameTitle()
{
    // Remove the game title from the layer
    this->removeChildByTag(kMainMenuLayer_TitleSprite, true);
}

// Removes the MainMenu from the layer.
void MainMenuLayer::removeGameMenu()
{
    // Remove the main menu from the layer
    this->removeChildByTag(kMainMenuLayer_MainMenu, true);
    
    // Add the start button to the layer
    addStartMenuChildren();
}

// Create, initialize, add to layer and perform initial animation to display the start button.
void MainMenuLayer::addStartMenuChildren()
{
    // Create the Easy Game Button
    CCSprite *easyButtonSpriteUp = CCSprite::createWithSpriteFrameName("easy_button.png");
    CCSprite *easyButtonSpriteDown = CCSprite::createWithSpriteFrameName("easy_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    easyButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *easyGameButton = CCMenuItemSprite::create(easyButtonSpriteUp, easyButtonSpriteDown, this, menu_selector(MainMenuLayer::easyGameButtonTouched));
    easyGameButton->setTag(kButtonDifficultyEasy);
    easyGameButton->setPositionX(-easyGameButton->getContentSize().width-(easyGameButton->getContentSize().width*0.1));
    
    // Create the Medium Game Button
    CCSprite *mediumButtonSpriteUp = CCSprite::createWithSpriteFrameName("medium_button.png");
    CCSprite *mediumButtonSpriteDown = CCSprite::createWithSpriteFrameName("medium_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    mediumButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *mediumGameButton = CCMenuItemSprite::create(mediumButtonSpriteUp, mediumButtonSpriteDown, this, menu_selector(MainMenuLayer::mediumGameButtonTouched));
    mediumGameButton->setTag(kButtonDifficultyMedium);
    
    // Create the Hard Game Button
    CCSprite *hardButtonSpriteUp = CCSprite::createWithSpriteFrameName("hard_button.png");
    CCSprite *hardButtonSpriteDown = CCSprite::createWithSpriteFrameName("hard_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    hardButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *hardGameButton = CCMenuItemSprite::create(hardButtonSpriteUp, hardButtonSpriteDown, this, menu_selector(MainMenuLayer::hardGameButtonTouched));
    hardGameButton->setTag(kButtonDifficultyHard);
    hardGameButton->setPositionX(hardGameButton->getContentSize().width+(hardGameButton->getContentSize().width*0.2));
    
    // Create the start game menu
    CCMenu *gameMenu = CCMenu::create(easyGameButton, mediumGameButton, hardGameButton, NULL);
    // Set the initial position off screen
    gameMenu->setPosition(ccp(SCREEN_WIDTH/2, -SCREEN_HEIGHT));
    // Set the tag of the start menu so that we can refer to it later using getChildByTag(...)
    gameMenu->setTag(kMainMenuLayer_StartGameMenu);

    // Create and run an animation that will slide the start game menu in from below the screen to its intended location
    CCActionInterval *moveAction = CCMoveTo::create(0.3f, ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
    CCFiniteTimeAction *easeIn = CCEaseIn::create(moveAction, 0.2f);    
    gameMenu->runAction(easeIn);
    
    // Add the start menu to the layer
    this->addChild(gameMenu);
}

// Animate the start menu item to slide out and remove the start menu children from the layer and cleanup.
void MainMenuLayer::removeStartMenuChildren()
{
    // Find our start menu and run an animation to make it slide out to the right, then call a method to dispose of the start menu
    CCMenu *gameMenu = (CCMenu *)this->getChildByTag(kMainMenuLayer_StartGameMenu);
    if (GameManager::sharedGameManager()->getGameDifficulty() == kGameDifficultyEasy)
    {
        gameMenu->getChildByTag(kButtonDifficultyEasy)->setVisible(true);
        gameMenu->getChildByTag(kButtonDifficultyMedium)->setVisible(false);
        gameMenu->getChildByTag(kButtonDifficultyHard)->setVisible(false);
    }
    else if (GameManager::sharedGameManager()->getGameDifficulty() == kGameDifficultyMedium)
    {
        gameMenu->getChildByTag(kButtonDifficultyEasy)->setVisible(false);
        gameMenu->getChildByTag(kButtonDifficultyMedium)->setVisible(true);
        gameMenu->getChildByTag(kButtonDifficultyHard)->setVisible(false);
    }
    else if (GameManager::sharedGameManager()->getGameDifficulty() == kGameDifficultyHard)
    {
        gameMenu->getChildByTag(kButtonDifficultyEasy)->setVisible(false);
        gameMenu->getChildByTag(kButtonDifficultyMedium)->setVisible(false);
        gameMenu->getChildByTag(kButtonDifficultyHard)->setVisible(true);
    }
    CCActionInterval *mmoveAction = CCMoveTo::create(0.3f, ccp(SCREEN_WIDTH+100, gameMenu->getPosition().y));
    CCFiniteTimeAction *measeOut = CCEaseOut::create(mmoveAction, 0.2f);
    CCFiniteTimeAction *mremove = CCCallFuncN::create(this, callfuncN_selector(MainMenuLayer::removeStartGameMenu));
    CCSequence *mtitleOut = CCSequence::createWithTwoActions(measeOut, mremove);
    gameMenu->runAction(mtitleOut);
}

// Removes the start game menu from the layer, and informs the GameManager to start a new game.
void MainMenuLayer::removeStartGameMenu()
{
    // Removes the start game menu from the layer
    this->removeChildByTag(kMainMenuLayer_StartGameMenu, true);
    
    // Start a new game.
    GameManager::sharedGameManager()->startNewGame();
}

// Action to perform when the Play Game Button was touched.
void MainMenuLayer::playGameButtonTouched()
{
    // Remove the main menu and add the start game menu
    this->removeMainMenuChildren();
}

// Action to perform when the About Game Button was touched.
void MainMenuLayer::aboutGameButtonTouched()
{
    GameManager::sharedGameManager()->showAboutGame();
}


// Action to perform when the Start Easy Game Button was touched.
void MainMenuLayer::easyGameButtonTouched()
{
    GameManager::sharedGameManager()->setGameDifficulty(kGameDifficultyEasy);
    // Remove the start game button and tell the GameManager to start a new game
    removeStartMenuChildren();
}

// Action to perform when the Start Medium Game Button was touched.
void MainMenuLayer::mediumGameButtonTouched()
{
    GameManager::sharedGameManager()->setGameDifficulty(kGameDifficultyMedium);
    // Remove the start game button and tell the GameManager to start a new game
    removeStartMenuChildren();
}

// Action to perform when the Start Hard Game Button was touched.
void MainMenuLayer::hardGameButtonTouched()
{
    GameManager::sharedGameManager()->setGameDifficulty(kGameDifficultyHard);
    // Remove the start game button and tell the GameManager to start a new game
    removeStartMenuChildren();
}

