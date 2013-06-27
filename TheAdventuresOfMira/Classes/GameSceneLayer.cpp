//
//  GameScene.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 2012/10/04.
//
//

#include "GameSceneLayer.h"
#include "GameManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameSceneLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameSceneLayer *layer = GameSceneLayer::create();
    layer->setTag(kGameManager_GameSceneLayer);
    
    GameManager::sharedGameManager()->setGameSceneLayer(layer);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameSceneLayer::init()
{
    // super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // add a menu item with "X" image, which is clicked to quit the program
    // you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    /**
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameSceneLayer::menuCloseCallback) );
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    pCloseItem->setPosition( ccp(screenSize.width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
     */
    
    // create and add the background parallax scrolling layer
    this->addChild(GameManager::sharedGameManager()->getBackgroundLayer(), 0);
    
    // add the main menu layer
    //GameManager::sharedGameManager()->showMainMenu();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("song_intro.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("song_1.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("song_2.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("song_3.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("song_4.mp3");
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_thud.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_laugh.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_click.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_collect.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_gameover.mp3");
    
    return true;
}

void GameSceneLayer::keyBackClicked()
{
    this->menuCloseCallback(this);
}

void GameSceneLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
