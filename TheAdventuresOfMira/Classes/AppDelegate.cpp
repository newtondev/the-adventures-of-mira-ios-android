//
//  TheAdventuresOfMiraAppDelegate.cpp
//  TheAdventuresOfMira
//
//  Created by Craig Newton on 7/11/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "GameSceneLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // load up the sprite cache resources for the platform
    TargetPlatform target = getTargetPlatform();
    DeviceSize deviceSize = kDeviceSizeLarge;
    DeviceType deviceType = kDeviceTypeiPad3;
    // ANDROID
    if (target == kTargetAndroid)
    {
        if (SCREEN_WIDTH > 1280)
        {
            // Set the device type
            deviceType = kDeviceTypeAndroid1280x800;
            deviceSize = kDeviceSizeLarge;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_1280x800.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_1280x800.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1280,800, kResolutionNoBorder);
        }
        else if (SCREEN_WIDTH == 1280 && (SCREEN_HEIGHT <= 800 && SCREEN_HEIGHT >= 730))
        {
            // Set the device type
            deviceType = kDeviceTypeAndroid1280x800;
            deviceSize = kDeviceSizeLarge;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_1280x800.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_1280x800.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1280,800, kResolutionExactFit);
        }
        else if (SCREEN_WIDTH == 1280 && (SCREEN_HEIGHT <= 720 && SCREEN_HEIGHT >= 650))
        {
            // Set the device type
            deviceType = kDeviceTypeAndroid1280x720;
            deviceSize = kDeviceSizeLarge;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_1280x720.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_1280x720.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1280,720, kResolutionExactFit);
        }
        else if (SCREEN_WIDTH == 1024 && (SCREEN_HEIGHT <= 600 && SCREEN_HEIGHT >= 530))
        {
            // Set the device type
            deviceType = kDeviceTypeAndroid1024x600;
            deviceSize = kDeviceSizeLarge;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_1024x600.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_1024x600.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024,600, kResolutionExactFit);
        }
        else if (SCREEN_WIDTH == 854 && (SCREEN_HEIGHT <= 480 && SCREEN_HEIGHT >= 410))
        {
            // Set the device type
            deviceType = kDeviceTypeAndroid854x480;
            deviceSize = kDeviceSizeNormal;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_854x480.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_854x480.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(854,480, kResolutionExactFit);
        }
        else if (SCREEN_WIDTH == 800 && (SCREEN_HEIGHT <= 480 && SCREEN_HEIGHT >= 410))
        {
            // Set the device type
            deviceType = kDeviceTypeAndroid800x480;
            deviceSize = kDeviceSizeNormal;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_800x480.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_800x480.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800,480, kResolutionExactFit);
        }
        else if (SCREEN_WIDTH == 800 && (SCREEN_HEIGHT <= 400 && SCREEN_HEIGHT >= 330))
        {
            // Set the device type
            deviceType = kDeviceTypeAndroid800x400;
            deviceSize = kDeviceSizeNormal;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_800x400.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_800x400.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800,400, kResolutionExactFit);
        }
        else if (SCREEN_WIDTH == 720 && (SCREEN_HEIGHT <= 480 && SCREEN_HEIGHT >= 410))
        {
            // Set the device type
            deviceType = kDeviceTypeAndroid720x480;
            deviceSize = kDeviceSizeNormal;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_720x480.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_720x480.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(720,480, kResolutionExactFit);
        }
        else
        {
            // Backup just in case
            // Set the device type
            deviceType = kDeviceTypeAndroid800x400;
            deviceSize = kDeviceSizeNormal;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("android_800x480.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("android_800x480.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800,480, kResolutionNoBorder);
        }
    }
    // iOS
    else if (target == kTargetIpad)
    {
        // iPad 3
        if (SCREEN_WIDTH == 2048)
        {
            // Set the device type
            deviceType = kDeviceTypeiPad3;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("spritesheet-ipad3.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("spritesheet-ipad3.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(2048,1536, kResolutionExactFit);
            deviceSize = kDeviceSizeXLarge;
        }
        // iPad 1, 2
        else
        {
            // Set the device type
            deviceType = kDeviceTypeiPad;
            // setup  the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("spritesheet-ipad.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("spritesheet-ipad.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024,768, kResolutionExactFit);
            deviceSize = kDeviceSizeLarge;
        }
    }
    else if (target == kTargetIphone)
    {
        // iPhone 5 Retina Display
        if (SCREEN_WIDTH == 1136 || SCREEN_WIDTH == 568)
        {
            // Set the device type
            deviceType = kDeviceTypeiPhone5;
            // setup the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("spritesheet-iphone5-hd.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("spritesheet-iphone5-hd.png");
            deviceSize = kDeviceSizeNormal;
        }
        // iPhone 4 Retina Display
        else if (SCREEN_WIDTH == 960)
        {
            // Set the device type
            deviceType = kDeviceTypeiPhone4;
            // setup the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("spritesheet-iphone-hd.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("spritesheet-iphone-hd.png");
            deviceSize = kDeviceSizeNormal;
        }
        // iPhone3G, iPod Touch
        else
        {
            // Set the device type
            deviceType = kDeviceTypeiPhone;
            // setup the sprite frame cache using our spritesheet plist
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("spritesheet-iphone.plist");
            // setup the texture cache using our spritesheet image
            CCTextureCache::sharedTextureCache()->addImage("spritesheet-iphone.png");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480,320, kResolutionExactFit);
            deviceSize = kDeviceSizeSmall;
        }
    }

    // initialize the game manager first before the scene
    GameManager::sharedGameManager()->setDeviceSize(deviceSize);
    GameManager::sharedGameManager()->setDeviceType(deviceType);
    
    // create a scene. it's an autorelease object
    CCScene *pScene = GameSceneLayer::scene();
    GameManager::sharedGameManager()->showMainMenu();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
    
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();
    
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
