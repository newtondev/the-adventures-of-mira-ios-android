//
//  MainMenuLayer.h
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#ifndef __TheAdventuresOfMira__MainMenuLayer__
#define __TheAdventuresOfMira__MainMenuLayer__

#include "cocos2d.h"

#define kButtonDifficultyEasy   9001
#define kButtonDifficultyMedium 9002
#define kButtonDifficultyHard   9003

// Represents the Main Menu of the Game
class MainMenuLayer : public cocos2d::CCLayer
{
public:
    // Create method
    CREATE_FUNC(MainMenuLayer);
    
    // Initialize our Main Menu Layer, and add the initial main menu with the title screen, play button and about button.
    virtual bool init();
    
    // Create, initialize, add to layer and perform the initial animation for the Main Menu.
    void addMainMenuChildren();
    
    // Animate the main menu items to slide out and remove the main menu children from the layer and cleanup.
    void removeMainMenuChildren();
    
    // Removes the MainMenuTitle from the layer.
    void removeGameTitle();
    
    // Removes the MainMenu from the layer.
    void removeGameMenu();
    
    // Create, initialize, add to layer and perform initial animation to display the start button.
    void addStartMenuChildren();
    
    // Animate the start menu item to slide out and remove the start menu children from the layer and cleanup.
    void removeStartMenuChildren();
    
    // Removes the start game menu from the layer, and informs the GameManager to start a new game.
    void removeStartGameMenu();
    
    // Action to perform when the Play Game Button was touched.
    void playGameButtonTouched();
    
    // Action to perform when the About Game Button was touched.
    void aboutGameButtonTouched();
    
    // Action to perform when the Start Easy Game Button was touched.
    void easyGameButtonTouched();
    
    // Action to perform when the Start Medium Game Button was touched.
    void mediumGameButtonTouched();
    
    // Action to perform when the Start Hard Game Button was touched.
    void hardGameButtonTouched();
};

#endif /* defined(__TheAdventuresOfMira__MainMenuLayer__) */
