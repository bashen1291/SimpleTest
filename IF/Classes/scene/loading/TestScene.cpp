//
// Created by imac_liudi on 2018/8/1.
//

#include "TestScene.h"
#include "cocos2d.h"
#include "Rain.h"

extern void printBackTraceTolog( const char* data);

void printBackTraceTolog( const char* data){};

extern bool IsFLOG();
extern void FLOG(const char * format, ...);

bool IsFLOG(){return false;};
void FLOG(const char * format, ...){};

extern void ForcePrintBackTraceTolog(const char *);
void ForcePrintBackTraceTolog(const char *){;};

extern void printDebugKeyInfo( const char* key, bool value);
void printDebugKeyInfo( const char* key, bool value){};

extern std::string g_theBranchLinkData;

std::string g_theBranchLinkData = "";






TestScene *TestScene::create() {
    auto ret = new TestScene();
    if(ret && ret->init())
        ret ->autorelease();
    else
        CC_SAFE_DELETE(ret);
    return ret;
}

TestScene::TestScene() {


}
TestScene::~TestScene() {

}

bool TestScene::init() {
    auto node = CCNode::create();
    addChild(node);

    auto spr = Sprite3D::create("test/yunbingcheGun01.c3t");
    node->addChild(spr);
    spr->setScale(1);
//    spr->setPosition(2000, 2000);
//    spr->setColor(Color3B::RED);
//    auto rect = spr->getBoundingBox();
//    auto layerColor = CCLayerColor::create(Color4B::RED);
//    layerColor->setContentSize(rect.size);
//    layerColor->setPosition(rect.origin);
//    node->addChild(layerColor);
    node->setPosition(500, 500);
//    spr->setCullFace(GL_BACK);
//    CCLOG("test, %f, %f, %f, %f", rect.origin.x, rect.origin.y);
//    auto winSize = CCDirector::sharedDirector()->getWinSize();
//    node->setPosition(winSize.width/2, winSize.height/2);
//    auto background = CCSprite::create("test/screenshot1.png");
//    node->addChild(background);
//    background->setScale(CCDirector::sharedDirector()->getWinSize().height  / background->getContentSize().height);
//
//    CCLayerColor *bluelayer = CCLayerColor::create(ccc4(65,65,65,128), winSize.width, winSize.height);
//    bluelayer->setAnchorPoint(ccp(0.5, 0.5));
//    bluelayer->ignoreAnchorPointForPosition(false);
//    bluelayer->setPosition(0, 0);
//    bluelayer->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
//    bluelayer->setOpacity(0);
//    bluelayer->runAction(FadeTo::create(5, 100));
//
//    node->addChild(bluelayer);
//
//    bluelayer->runAction(CCSequence::create(CCDelayTime::create(20),
//            FadeOut::create(10), nullptr));
//
//
//    CCLayerColor *lightlayer = CCLayerColor::create(ccc4(0,0,0,128), winSize.width, winSize.height);
//    lightlayer->setAnchorPoint(ccp(0.5, 0.5));
//    lightlayer->ignoreAnchorPointForPosition(false);
//    lightlayer->setPosition(0, 0);
//    lightlayer->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
////    lightlayer->setOpacity(0);
//    CCTintTo* tinto1 = CCTintTo::create(0.15, 0,0,0);
//    CCTintTo* tinto2 = CCTintTo::create(0.15, 255,246,238);
//
//    lightlayer->runAction(CCRepeat::create(CCSequence::create(
//            CCDelayTime::create(5),
//            EaseSineInOut::create(CCTintTo::create(0.3, 255,246,238)),
//            EaseSineInOut::create(CCTintTo::create(0.1, 0,0,0)),
//            EaseSineInOut::create(CCTintTo::create(0.1, 255,246,238)),
//            EaseSineInOut::create(CCTintTo::create(0.3, 0,0,0)),
//            nullptr
//            ), 3));
//    node->addChild(lightlayer);
////    lightlayer->runAction(CCFadeTo::create(3, 150));
//
//
//
//    //add rain
//    auto rain1 = Rain::create();
//    rain1->setTag(10);
//    node->addChild(rain1);
//    rain1->setScale(CCDirector::sharedDirector()->getWinSize().height * 2 / rain1->getContentSize().height);
////        rain1->setAnchorPoint(CCPoint::ZERO);
//    rain1->setRotationQuat(Quaternion(Vec3::UNIT_X,  MATH_DEG_TO_RAD(10.75052)));
//
//    rain1->setPositionZ(150);
//    rain1->startRainIn(5, 1.5);
//    auto q3 = Quaternion(Vec3::UNIT_Z,  MATH_DEG_TO_RAD(19.68799));
//
//    scheduleOnce([=](float dt)
//    {
//        rain1->startRainOut(10);
//        return;
//    }, 20, "rainstop");
    return Scene::init();

}

void TestScene::onEnter() {
    Node::onEnter();
}

void TestScene::onExit() {
    Node::onExit();
}
