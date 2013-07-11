//
//  AboutGameLayer.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "AboutGameLayer.h"
#include "Constants.h"
#include "GameManager.h"

using namespace cocos2d;

// Initialize our Main Menu Layer, and add the initial main menu with the title screen, play button and about button.
bool AboutGameLayer::init()
{
    // Initialize the parent
    if (!CCLayer::init()) return false;
    
    // Set the screen size to the full dimensions of the device (full screen)
    this->setContentSize(SCREEN_SIZE);
    
    CCSprite *aboutGameTitle = CCSprite::createWithSpriteFrameName("about_game.png");
    aboutGameTitle->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/1.2));
    aboutGameTitle->setScale(0.8f);
    this->addChild(aboutGameTitle);
    
    float labelScaleNormal = 1.0f;
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid854x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x400 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid720x480)
    {
        labelScaleNormal = 0.8f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeNormal)
    {
        labelScaleNormal = 0.9f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeSmall)
    {
        labelScaleNormal = 0.45f;
    }
    
    float labelScaleSmall = 0.8f;
    if (GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid854x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x480 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid800x400 ||
        GameManager::sharedGameManager()->getDeviceType() == kDeviceTypeAndroid720x480)
    {
        labelScaleSmall = 0.6f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeNormal)
    {
        labelScaleSmall = 0.7f;
    }
    else if (GameManager::sharedGameManager()->getDeviceSize() == kDeviceSizeSmall)
    {
        labelScaleSmall = 0.4f;
    }
    
    CCLabelBMFont *descriptionLabel1 = CCLabelBMFont::create("HELP MIRA THE BEE COLLECT AS MANY FLOWERS AS", "myGlyphs.fnt");
    descriptionLabel1->setScale(labelScaleNormal);
    descriptionLabel1->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/1.45));
    this->addChild(descriptionLabel1);
    
    CCLabelBMFont *descriptionLabel2 = CCLabelBMFont::create("POSSIBLE TO MAKE HONEY FOR HER HIVE", "myGlyphs.fnt");
    descriptionLabel2->setScale(labelScaleNormal);
    descriptionLabel2->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/1.55));
    this->addChild(descriptionLabel2);
    
    CCLabelBMFont *createdLabel = CCLabelBMFont::create("CONCEPT   PROGRAMMING   MUSIC:", "myGlyphs.fnt");
    createdLabel->setScale(labelScaleSmall);
    createdLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/1.85));
    this->addChild(createdLabel);
    
    CCLabelBMFont *craigLabel = CCLabelBMFont::create("C R A I G   N E W T O N", "myGlyphs.fnt");
    craigLabel->setScale(labelScaleNormal);
    craigLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2.0));
    this->addChild(craigLabel);
    
    CCLabelBMFont *artworkLabel = CCLabelBMFont::create("ARTWORK  AND  GRAPHIC  DESIGN:", "myGlyphs.fnt");
    artworkLabel->setScale(labelScaleSmall);
    artworkLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2.45));
    this->addChild(artworkLabel);
    
    CCLabelBMFont *artistsLabel = CCLabelBMFont::create("R A Y N A L D O   P E R E Z    AND    J O S E   F E R N A N D E Z", "myGlyphs.fnt");
    artistsLabel->setScale(labelScaleNormal);
    artistsLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/2.75));
    this->addChild(artistsLabel);
    
    CCLabelBMFont *copyrightLabel = CCLabelBMFont::create("COPYRIGHT 2012 NEWTON DEVELOPMENT STUDIO", "myGlyphs.fnt");
    copyrightLabel->setScale(labelScaleNormal);
    copyrightLabel->setPosition(ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/3.75));
    this->addChild(copyrightLabel);
    
    // Back button
    createBackButton();
    
    // Initialization was successful
    return true;
}

void AboutGameLayer::createBackButton()
{
    // Create the backButton
    CCSprite *backButtonSpriteUp = CCSprite::createWithSpriteFrameName("main_button.png");
    CCSprite *backButtonSpriteDown = CCSprite::createWithSpriteFrameName("main_button.png");
    // Scale the down to 90% so that it looks like the button was pressed
    backButtonSpriteDown->setScale(0.9f);
    CCMenuItemSprite *backButton = CCMenuItemSprite::create(backButtonSpriteUp, backButtonSpriteDown, this, menu_selector(AboutGameLayer::backButtonTouched));
    backButton->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleTo::create(0.4f, 1.1f), CCScaleTo::create(1.0f, 1.0f))));
    
    // Create the start game menu
    CCMenu *gameMenu = CCMenu::create(backButton, NULL);
    // Set the initial position off screen
    gameMenu->setPosition(ccp(SCREEN_WIDTH/2, -SCREEN_HEIGHT));
    // Set the tag of the start menu so that we can refer to it later using getChildByTag(...)
    gameMenu->setTag(kAboutGameLayer_BackMenu);
    
    // Create and run an animation that will slide the start game menu in from below the screen to its intended location
    CCActionInterval *moveAction = CCMoveTo::create(0.3f, ccp(SCREEN_WIDTH/2, SCREEN_HEIGHT/8));
    CCFiniteTimeAction *easeIn = CCEaseIn::create(moveAction, 0.2f);
    gameMenu->runAction(easeIn);
    
    // Add the start menu to the layer
    this->addChild(gameMenu);
}

void AboutGameLayer::backButtonTouched()
{
    this->getChildByTag(kAboutGameLayer_BackMenu)->stopAllActions();
    GameManager::sharedGameManager()->showMainMenu();
}
