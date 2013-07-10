LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := mira/main.cpp \
                   ../../TheAdventuresOfMira/Classes/AppDelegate.cpp \
                   ../../TheAdventuresOfMira/Classes/AboutGameLayer.cpp \
                   ../../TheAdventuresOfMira/Classes/BackgroundLayer.cpp \
                   ../../TheAdventuresOfMira/Classes/CCParallaxScrollNode.cpp \
                   ../../TheAdventuresOfMira/Classes/CCParallaxScrollOffset.cpp \
                   ../../TheAdventuresOfMira/Classes/CollectableItem.cpp \
                   ../../TheAdventuresOfMira/Classes/GameCharacter.cpp \
                   ../../TheAdventuresOfMira/Classes/GameManager.cpp \
                   ../../TheAdventuresOfMira/Classes/GameObject.cpp \
                   ../../TheAdventuresOfMira/Classes/GameObstacle.cpp \
                   ../../TheAdventuresOfMira/Classes/GameOverLayer.cpp \
                   ../../TheAdventuresOfMira/Classes/GameplayLayer.cpp \
                   ../../TheAdventuresOfMira/Classes/GameSceneLayer.cpp \
                   ../../TheAdventuresOfMira/Classes/HudLayer.cpp \
                   ../../TheAdventuresOfMira/Classes/MainMenuLayer.cpp \
                   ../../TheAdventuresOfMira/Classes/Mira.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../TheAdventuresOfMira/Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
