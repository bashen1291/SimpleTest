//
//  LoadingScene.cpp
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//
//

#include "LoadingScene.h"
#include "PlayerInfo.h"
#include "../../Ext/CCDevice.h"
#include "SceneController.h"
#include "SoundController.h"
#include "LoginCommand.h"
#include "AZCommonUtils.hpp"
#include "PopupViewController.h"
#include "KoreaPermitPopUPView.h"
#include "AppLibHelper.h"
#include "NetController.h"
#include "YesNoDialog.h"
#include "ParticleController.h"
#include "InitCommand.h"
#include "SuggestionView.h"
#include "PushInit.h"
#include "IFLoadingSceneArmyNode.h"
#include "FunBuildController.h"
#include "CCDevice.h"
#include "CCMathUtils.h"
#include "md5.h"
#include "AnnouncementView.h"

#include "ChangeServerView.h"

#include "CrashController.hpp"
#include "UIComponent.h"
#include "GuideController.h"
#include "ECServiceCocos2dx.h"
#include "UILocalNotificationHelper.h"
#include "ChatServiceCocos2dx.h"
#include "GamePublisher.h"
#include "PlatformUtil.h"
#include "base/CCGlobalLock.h"
#include "DynamicResourceFuDaoController.h"
#include "UpdatePopUp.h"
#include "ArenaController.hpp"
#include "NetSetingPopview.hpp"
#include "GuideViewBlackMask.hpp"
#include "UserAgreementPopUp.hpp"
#include "PasswordInputPopupView.hpp"

#include "WorldMapGuideView.h"
#include "FBUtilies.h"
#include "UserBindCommand.h"
#include "SetAccountView.h"
#include "LoadingNoticePopView.hpp"
#include "IFUserRecord.hpp"
#include "WarZAccountBindRewardView.hpp"
#include "LocalResourceController.h"
#include "ActivityController.h"
#include "CCAnimationEx.hpp"
#include "SubsidiaryCityController.hpp"
#include "SubSidiaryCityPutTipsView.hpp"
#include "EUReview.h"
#include "EUSelectCountry.h"
#include "EUReviewNew.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "CrashReport.h"
#endif

#define MSG_MAIN_THREAD_XML 453
#define LOADING_STEP        80
#define LOADING_PROGRESS_STEP  5
#define LOADING_PROGRESS_FINISH -1
#define LOADING_BLOOD_OFFSET 5
#define LOADING_LOGO_TAG    666
#define LOADING_1 667
#define LOADING_2 668
#define LOADING_3 669
#define LOADING_4 670
#define CNSCENE_TAG 1000

extern pthread_t BACK_PROCESS_THREAD_ID;

bool g_isSavedUserInfo = false;

bool _enableCheckNet = true;

bool g_useSmallLogin = false;

extern bool g_isSuccessUnZip;
extern int g_currentNum;
extern int g_allNum;
extern void printDebugKeyInfo(const char*, bool init);
extern void printRefDebugInfo( cocos2d::Ref* object );
extern void printDebugKeyValue(const char* key, const char* val);
extern bool g_isInLoadingScene;
extern bool g_isLoadingSceneInit;
extern bool use_kcp;
extern bool use_snc;
static int loadingSceneCount = 0;

static vector<LoadingScene*> DumpLoadingScene;
static LoadingScene* currentLoading = nullptr;
string g_durloading_commandlist="";
static string g_login_error_combine = "";
string g_sfs_serverIP = "0";
string g_login_error = "";
string g_gsl = "";
int g_sfs__serverPort = 0;
int g_sfs_status = 0;
int g_http_status = -1;
int g_retry_connect = 0;


//LoadingCNScene
LoadingCNScene* LoadingCNScene::create(LoadingScene* scene)
{
    auto ret = new LoadingCNScene(scene);
    if(ret && ret->init()){
        ret->autorelease();
    }else{
        CC_SAFE_RELEASE_NULL(ret);
    }
    return ret;
}

LoadingCNScene::LoadingCNScene(LoadingScene* scene)
:m_scene(scene)
{
    m_remove = false;
}

LoadingCNScene::~LoadingCNScene()
{
}

bool LoadingCNScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
//    CCLoadSprite::autoDoResourceByPath("Loading/Loading_4.plist", this);
    auto ccb = CCBLoadFile("LoadingView1", this, this);
    if (!ccb){
        return false;
    }
    this->setContentSize(ccb->getContentSize());
    if (m_tipsTitle){
        //82001166  健康公告
        m_tipsTitle->setString(_lang("82001166"));
    }
    if (m_tipsContent){
        string content = _lang("82001167");
        content.append("\n");
        content.append(_lang("82001168"));
        content.append("\n");
        content.append(_lang("82001169"));
        content.append("\n");
        content.append(_lang("82001170"));
        content.append("\n");
        m_tipsContent->setString(content);
    }
    if (m_copyrightNode){
        for (int i = 0; i < 8; ++i){
            auto label = dynamic_cast<CCLabelIF*>(m_copyrightNode->getChildByTag(i+1));
            if (label){
                label->setString(_lang(CCCommonUtils::itoa(82001171+i)));
            }
        }
    }
    if (m_adviseLabel){
        m_adviseLabel->setString(_lang("82001179"));
    }
    
    std::function<void(CCNode* node, bool value)> each_node = [&each_node](CCNode* node, bool value) {
        node->setCascadeOpacityEnabled(value);
        for( auto&& child : node->getChildren()) {
            each_node(child,value);
        }
    };
    each_node(this, true);
    updateOpacity(0);
    return true;
}

void LoadingCNScene::onEnter(){
    CCLayer::onEnter();
    m_time = 0.0f;
    m_tipsContent->setObjAnimation(true);
    m_tipsContent->schedule([this](float dt) {
        CCLog(">>> now m_times: %f", m_time);
        m_time += dt;
        if (m_time <= 0.5){
            m_opa += 50;
        }else if (m_time > 0.5 || m_time <= 2.2){
            m_opa = 255;
        }else if (m_time > 2.2){
            m_opa -= 30;
        }
        if (m_opa < 0){
            m_opa = 0;
        }else if (m_opa > 255){
            m_opa = 255;
        }
        updateOpacity(m_opa);
        if (m_time > 3.0){
            if (!m_remove){
                if (m_scene){
                    m_scene->removeCNScene();
                }
            }
            m_remove = true;
        }
    }, 0.01f, "M_UpdateLoading");
    
    //点击
    m_touchClickNode = CCAZTouchNode::create(this, nullptr);
    if (m_touchClickNode){
        m_touchClickNode->addTouchNode(m_clickNode);
        addChild(m_touchClickNode);
    }
}

void LoadingCNScene::onExit(){
    if (m_tipsContent){
        m_tipsContent->unschedule("M_UpdateLoading");
    }
    CCLayer::onExit();
}

void LoadingCNScene::updateOpacity(int opa){
    if (m_tipsTitle){
        //82001166  健康公告
        m_tipsTitle->setOpacity(opa);
    }
    if (m_tipsContent){
        m_tipsContent->setOpacity(opa);
    }
    if (m_copyrightNode){
        for (int i = 0; i < 8; ++i){
            auto label = dynamic_cast<CCLabelIF*>(m_copyrightNode->getChildByTag(i+1));
            if (label){
                label->setOpacity(opa);
            }
        }
    }
    if (m_adviseLabel){
        m_adviseLabel->setOpacity(opa);
    }
}

bool LoadingCNScene::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK_EX(this, "m_clickNode", CCNode, m_clickNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK_EX(this, "m_tipsTitle", CCLabelIF, m_tipsTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK_EX(this, "m_tipsContent", CCLabelIF, m_tipsContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK_EX(this, "m_copyrightNode", CCNode, m_copyrightNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK_EX(this, "m_adviseLabel", CCLabelIF, m_adviseLabel);
    return false;
}

bool LoadingCNScene::onTouchClickNode(CCNode* node)
{
    if (m_scene && node && m_clickNode == node){
        m_scene->showConnectInfo();
        return true;
    }
    return false;
}


//LoadingScene
LoadingScene::LoadingScene()
:m_steps(LOADING_STEP)
,m_progress(5)
,m_platformLoginFlag(false)
,m_loadingTotalTime(0)
,m_loginUUID("")
,m_checkNetLog("")
,needAccountInfo(false)
,m_isNetStep3Pass(false)
,m_bShowConfirmPanel(true)
{
    DumpLoadingScene.push_back(this);
    this->_DebugAllRefCountBackTrace = true;
    loadingSceneCount++;
    g_isLoadingSceneInit = true;
    //个人军备的本地缓存
    CCUserDefault::sharedUserDefault()->setIntegerForKey("SingleScoreActiveView", 0);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("SingleScoreActiveView::refreshBar", 0);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("SingleScoreActiveView::showHelpView", 0);
    //
    CCUserDefault::sharedUserDefault()->setIntegerForKey("CONNECT_SEND", 0);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("CONNECT_TIMES", 0);
    CCUserDefault::sharedUserDefault()->setBoolForKey("AllianceServiceInfoCell", false);
    CCUserDefault::sharedUserDefault()->setBoolForKey("ImperialScene::onShowPopView", false);
    CCUserDefault::sharedUserDefault()->flush();
    if( IsFLOG()) {
        FLOG("NET Loading set connect Time 0");
    }
    //
    if( loadingSceneCount > 1) {
        printDebugKeyInfo("LoadingSceneOOM", true);
        if (DumpLoadingScene.size() > 0) {
            printRefDebugInfo(DumpLoadingScene[0]);
        }
    }
    currentLoading = this;
    g_durloading_commandlist.clear();
    printDebugKeyValue("LOADINGCOMMAND", g_durloading_commandlist.c_str());
    g_login_error_combine = "";
    g_gsl = "";
}

LoadingScene::~LoadingScene()
{
    auto iter = std::find(DumpLoadingScene.begin(), DumpLoadingScene.end(), this);
    
    if( iter != DumpLoadingScene.end() && (*iter) != nullptr) {
        DumpLoadingScene.erase(iter);
    }
    
    g_isLoadingSceneInit = false;
    loadingSceneCount--;
}

void LoadingScene::removeCNScene()
{
    this->removeChildByTag(CNSCENE_TAG);
    if (m_initFinsh){
        CCSafeNotificationCenter::sharedNotificationCenter()->postNotification(MSG_INIT_FINISH);
    }
}

void LoadingScene::showConnectInfo()
{
    if (m_conStatusCode){
        m_conStatusCode->setZOrder(CNSCENE_TAG+1);
    }
}

bool LoadingScene::isUseLoadingConfig(){
    auto loading_config = UserDefault::sharedUserDefault()->getStringForKey("loading_config", "");
    if (loading_config.compare("") == 0)
        return false;
    if (loadingBg_config.compare("") != 0 && loadingBg_config.compare(" ") != 0 ){
        if (CCSpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("loading_page_up_"+loadingBg_config+".png") == nullptr ||
            CCSpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("loading_page_down_"+loadingBg_config+".png") == nullptr){
            return false;
        }
    }
    if (particle_config.compare("") != 0 && particle_config.compare(" ") != 0){
        std::vector<std::string> _item_config;  //Loading_5#0.5:0.65
        CCCommonUtils::splitString(particle_config, ";", _item_config);
        for (int i = 0; i < _item_config.size(); ++i){
            std::vector<std::string> _config;
            CCCommonUtils::splitString(_item_config[i], "#", _config);
            if (_config.size() > 0){
                if (!FileUtils::sharedFileUtils()->isFileExist("particleImg/"+_config[0]+".plist")){
                    return false;
                }
            }
        }
    }
    //判断骨骼动画
    if ( spine_config.compare("") != 0 && spine_config.compare(" ") != 0 ){
        std::vector<std::string> _item_config;  //spine#x#y#scale#scalepad#aniName
        CCCommonUtils::splitString(spine_config, ";", _item_config);
        for (int i = 0; i < _item_config.size(); ++i){
            std::vector<std::string> _config;
            CCCommonUtils::splitString(_item_config[i], "#", _config);
            if (_config.size() > 0){
                if (!FileUtils::sharedFileUtils()->isFileExist(StringUtils::format("Spine/SP_%s.json", _config[0].c_str()))){
                    return false;
                }
            }
        }
    }
    //判断序列帧动画
    if ( frame_config.compare("") != 0 && frame_config.compare(" ") != 0 ){
        std::vector<std::string> _item_config;  //spine#x#y#scale#scalepad#aniName
        CCCommonUtils::splitString(frame_config, ";", _item_config);
        for (int i = 0; i < _item_config.size(); ++i){
            std::vector<std::string> _config;
            CCCommonUtils::splitString(_item_config[i], "#", _config);
            if (_config.size() > 0){
                if (!FileUtils::sharedFileUtils()->isFileExist(StringUtils::format("%s/%s.plist", _config[0].c_str(), _config[0].c_str()))){
                    return false;
                }
            }
        }
    }
    return true;
}


void LoadingScene::initLoadingConfig(){
    auto loading_config = UserDefault::sharedUserDefault()->getStringForKey("loading_config", "");
    if (loading_config.compare("") != 0){
        std::vector<std::string> _config;
        CCCommonUtils::splitString(loading_config, "|", _config);
        if (_config.size() > 0){
            loadingBg_config = _config[0];
        }
        if (_config.size() > 1){
            particle_config = _config[1];
        }
        if (_config.size() > 2){
            spine_config = _config[2];
        }
        if (_config.size() > 3){
            frame_config = _config[3];
        }
    }
}

bool LoadingScene::init()
{
    bool bRet = false;
    m_updateFAQTips = true;
    ChatServiceCocos2dx::isGetPowerSwitch=false;
    ChatServiceCocos2dx::isGetAllianceInfo = false;
    //热云打点--这个地方只有在CN/QQ才会设置值
    if (GlobalData::shared()->reyunDeviceId.compare("") != 0){
        CCCommonUtils::recordReYunSDKStep(GlobalData::shared()->reyunDeviceId,"ReYunSDKInit");
        GlobalData::shared()->reyunDeviceId = "";
    }
    CCCommonUtils::recordStepForLoading("3", 0,"",1);
    printDebugKeyInfo("LoadingScene", true);
    setCleanFunction([](){
        if(GlobalData::shared()->isInDataParsing){
            printDebugKeyInfo("LoadingError3", true);
            printBackTraceTolog("LoadingScene Should Not Destruct!");
        }
        printDebugKeyInfo("LoadingScene", false);
    });
    
    ParticleController::initParticle();
    
    g_http_status = -1;
    srand(time(nullptr));
    if (CCLayer::init()) {
        g_isSavedUserInfo = false;
        //
        float designHeight = 1136.0;
        CCSize screenSize = Director::getInstance()->getWinSize();
        CCLOG("$$$ loading : screenSize : %f , %f",screenSize.width,screenSize.height);
        
        float theScaleY = this->getScaleY();

        if(screenSize.height != designHeight) {
            theScaleY = screenSize.height / designHeight;
        }
        
        CCLOG("$$$ loading : theScaleY after : %f",theScaleY);
        
        CCLabelIF::initFont();
        GameController::getInstance();
        //loadingLog统计
        GameController::getInstance()->setLoadingLog("LoadingScene", "init");
        
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        auto addPt = ccp(0, 0);
        
        //初始化loading数据
        initLoadingConfig();
        
        initLoadingImageBg(screenSize);
        
        
        
        //英雄spine动画
        bool _use_config = isUseLoadingConfig();
        if (_use_config == true){
            //粒子
            if (particle_config.compare("") != 0 && particle_config.compare(" ") != 0){
                std::vector<std::string> _item_config;  //Loading_5#0.5:0.65;Loading_6#0.5;0
                CCCommonUtils::splitString(particle_config, ";", _item_config);
                for (int i = 0; i < _item_config.size(); ++i){
                    std::vector<std::string> _config;
                    CCCommonUtils::splitString(_item_config[i], "#", _config); //Loading_5#0.5:0.65
                    if (_config.size() == 2){
                        if (FileUtils::sharedFileUtils()->isFileExist("particleImg/"+_config[0]+".plist")){
                            auto particle = CCParticleSystemQuad::create("particleImg/"+_config[0]+".plist");
                            std::vector<std::string> _config_pos;
                            CCCommonUtils::splitString(_config[1], ":", _config_pos);
                            particle->setPosition(ccp(size.width*atof(_config_pos[0].c_str()), size.height*atof(_config_pos[1].c_str())));
                            particle->setScaleY(theScaleY);
                            this->addChild(particle, 20);
                        }
                    }
                }
            }
            //骨骼动画
            if (spine_config.compare("") != 0 && spine_config.compare(" ") != 0){
                auto size = Director::sharedDirector()->getWinSize();
                std::vector<std::string> _item_config;  //spine#x#y#scale#scalepad#aniName;spine#x#y#scale#scalepad#aniName
                CCCommonUtils::splitString(spine_config, ";", _item_config);
                for (int i = 0; i < _item_config.size(); ++i){
                    std::vector<std::string> _config;
                    CCCommonUtils::splitString(_item_config[i], "#", _config);//spine#x#y#scale#scalepad#aniName
                    if (_config.size() == 6){
                        std::string spineName = _config[0];
                        float posX = atof(_config[1].c_str());
                        float posY = atof(_config[2].c_str());
                        float scale = atof(_config[3].c_str());
                        float scalePad = atof(_config[4].c_str());
                        std::string aniName = _config[5];
                        if (FileUtils::sharedFileUtils()->isFileExist(StringUtils::format("Spine/SP_%s.json", spineName.c_str()))){
                            auto kingSpine = IFLoadingSceneArmyNode::create(StringUtils::format("Spine/SP_%s.atlas", spineName.data()),
                                                                            StringUtils::format("Spine/SP_%s.json", spineName.data()),
                                                                            aniName);
                            if (kingSpine)
                            {
                                kingSpine->setObjAnimation(true);
                                
                                std::function<void(CCNode* node, bool value)> each_node = [&each_node](CCNode* node, bool value) {
                                    node->setObjAnimation(value);
                                    for( auto&& child : node->getChildren()) {
                                        each_node(child,value);
                                    }
                                };
                                each_node(kingSpine, true);
                                
                                this->addChild(kingSpine);
                                kingSpine->setPosition(Vec2(posX*size.width, posY*size.height));
                                kingSpine->setScale(scale);
                                if(CCCommonUtils::isIosAndroidPad())
                                {
                                    kingSpine->setScale(scalePad);
                                }
                            }
                        }
                    }
                }
            }
            //序列帧动画
            if (frame_config.compare("") != 0 && frame_config.compare(" ") != 0){
                auto size = Director::sharedDirector()->getWinSize();
                std::vector<std::string> _item_config;  //name#x#y#scale#scalepad#delayTime;name#x#y#scale#scalepad#delayTime
                CCCommonUtils::splitString(frame_config, ";", _item_config);
                for (int i = 0; i < _item_config.size(); ++i){
                    std::vector<std::string> _config;
                    CCCommonUtils::splitString(_item_config[i], "#", _config);//spine#x#y#scale#scalepad#aniName
                    if (_config.size() == 7){
                        std::string frameName = _config[0];
                        float posX = atof(_config[1].c_str());
                        float posY = atof(_config[2].c_str());
                        float scale = atof(_config[3].c_str());
                        float scalePad = atof(_config[4].c_str());
                        int count = atoi(_config[5].c_str());
                        float delaytime = atof(_config[6].c_str());
                        if (FileUtils::sharedFileUtils()->isFileExist(StringUtils::format("%s/%s.plist", frameName.c_str(), frameName.c_str()))){
                            auto node = CCAnimationEx::create(frameName, count, delaytime);
                            if (node)
                            {
                                this->addChild(node);
                                node->setPosition(Vec2(posX*size.width, posY*size.height));
                                node->setScale(scale);
                                if(CCCommonUtils::isIosAndroidPad())
                                {
                                    node->setScale(scalePad);
                                }
                            }
                        }
                    }
                }
            }
        }else{
            auto data = LocalTextController::shared()->getGroupByKey("loadingSpine");
            if(data)
            {
                CCDictElement* element;
                CCDICT_FOREACH(data, element)
                {
                    CCDictionary* dict = _dict(element->getObject());
                    std::string spineName = dict->valueForKey("name")->getCString();
                    float posX = dict->valueForKey("posX")->floatValue();
                    float posY = dict->valueForKey("posY")->floatValue();
                    float scale = dict->valueForKey("scale")->floatValue();
                    float scalePad = dict->valueForKey("scalePad")->floatValue();
                    std::string aniName = dict->valueForKey("aniName")->getCString();
                    if (FileUtils::sharedFileUtils()->isFileExist(StringUtils::format("Loading/%s.json", spineName.data())))
                    {
                        auto kingSpine = IFLoadingSceneArmyNode::create(StringUtils::format("Loading/%s.atlas", spineName.data()),
                                                                        StringUtils::format("Loading/%s.json", spineName.data()),
                                                                        aniName);
                        if (kingSpine)
                        {
                            this->addChild(kingSpine);
                            kingSpine->setPosition(Vec2(posX, posY));
                            kingSpine->setScale(scale);
                            
                            if(CCCommonUtils::isIosAndroidPad())
                            {
                                kingSpine->setScale(scalePad);
                            }
                        }
                    }
                }
            }
            
            //添加粒子效果
            auto allDictInfo = LocalTextController::shared()->getGroupByKey("loadingParticle");
            if(allDictInfo)
            {
                CCDictElement* element;
                CCDICT_FOREACH(allDictInfo, element)
                {
                    CCDictionary* dictInfo = _dict(element->getObject());
                    std::string icon = dictInfo->valueForKey("name")->getCString();
                    std::string pos = dictInfo->valueForKey("pos")->getCString();
                    vector<string> strVec;
                    CCCommonUtils::splitString(pos, ";", strVec);
                    
                    if (FileUtils::sharedFileUtils()->isFileExist("particleImg/"+icon+".plist")){
                        auto particle = CCParticleSystemQuad::create("particleImg/"+icon+".plist");
                        particle->setPosition(ccp(size.width*atof(strVec[0].c_str()), size.height*atof(strVec[1].c_str())));
                        particle->setScaleY(theScaleY);
                        this->addChild(particle, 20);
                    }
                }
            }
        }
        //汉语
        createLoadingCN();
        
        auto loadingBarBG = CCLoadSprite::createSprite("loading_bar_BG.png");
        loadingBarBG->setTag(LOADING_1);
        
        int randWenzi=rand()%4+1;
        auto wenziStr=CCCommonUtils::format("loading_wenzi_%d.png",randWenzi);
        m_underBarLabel=CCLoadSprite::createSprite(wenziStr.c_str());
        m_underBarLabel->setPosition(ccp(loadingBarBG->getContentSize().width/2+12,loadingBarBG->getContentSize().height/2-5));
        m_underBarLabel->setVisible(false);
        loadingBarBG->addChild(m_underBarLabel);
        
        auto clipNode=CCClipNode::create(loadingBarBG->getContentSize().width-30, loadingBarBG->getContentSize().height);
        m_blood = CCSprite::create();
        m_blood->setAnchorPoint(ccp(0,0));
        CCCommonUtils::makeEffectSpr(m_blood, "loading_blood_%d.png", 8, 0.1);
        clipNode->addChild(m_blood);
        auto loadingBar = CCLoadSprite::createSprite("loading_bar_BG.png");
        loadingBar->setVisible(false);
        loadingBar->setTag(LOADING_2);
        m_loadingProgress = CCLoadSprite::createScale9Sprite("loading_progress.png");
        m_loadingProgress->setContentSize(CCSizeMake(530, 34));
        string _uuid = cocos2d::extension::CCDevice::getDeviceUid();
        
        GlobalData::shared()->version = cocos2d::extension::CCDevice::getVersionName();
        GlobalData::shared()->startType = cocos2d::extension::CCDevice::getStartType();
        
        string _versionCode = cocos2d::extension::CCDevice::getVersionCode();
        string _version = GlobalData::shared()->version.c_str();
#if COCOS2D_DEBUG > 0
        CCLabelIF* label = CCLabelIF::create(CCString::createWithFormat("V %s (%s) : UUID %s",
                                                                        _version.c_str(),_versionCode.c_str(),_uuid.c_str())->getCString());
#else
        CCLabelIF* label = CCLabelIF::create(CCString::createWithFormat("V %s (%s)",
                                                                        _version.c_str(),_versionCode.c_str())->getCString());
#endif
        label->setScale(0.5f);
        label->setFontSize(40);
        label->setColor({255,255,0});
        label->setAnchorPoint(CCPoint(1,1));
        label->setPosition(ccp(size.width-10, size.height));
        addChild(label,10);
        m_conStatusCode = CCLabelIF::create("S:(0 0 0)");
        m_conStatusCode->setScale(0.5f);
        m_conStatusCode->setFontSize(40);
        m_conStatusCode->setColor({255,255,0});
        m_conStatusCode->setAnchorPoint(CCPoint(1,1));
        m_conStatusCode->setPosition(ccp(size.width-10, size.height - 20));
        addChild(m_conStatusCode);
        
        float _tipX = CCDirector::sharedDirector()->getWinSize().width/2-40;
        m_loadtips = CCLabelIF::create(_lang("E100074").c_str());
        //m_loadtips->setFntFile("Arial_Bold_Border.fnt");
        m_loadtips->setColor({255,255,255});
        m_loadtips->setFontSize(18);
        m_loadtips->setHorizontalAlignment(kCCTextAlignmentCenter);
        m_loadtips->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        m_loadtips->setAnchorPoint(ccp(0.5, 0.5));
        m_loadtips->setPosition(ccp(_tipX,30) + addPt);
        m_loadtips->setVisible(false);
        addChild(m_loadtips, 9999);
        
        int __height = 30;
        std::string language = LocalTextController::shared()->getLanguageFileName();
        if (!CCLabelIF::canBeSupportedWithBmpFont(language))
        {
            __height = -20;
        }
        
        m_FAQ = CCLabelIF::create(_lang("E100075").c_str());
        //m_FAQ->setFntFile("Arial_Bold_Border.fnt");
        m_FAQ->setColor(ccGREEN);
        m_FAQ->setFontSize(18);
        m_FAQ->setHorizontalAlignment(kCCTextAlignmentCenter);
        m_FAQ->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        m_FAQ->setAnchorPoint(ccp(0.5, 0.5));
        m_FAQ->setPosition(ccp(_tipX + m_loadtips->getContentSize().width/2 - __height,30) + addPt);
        m_FAQ->setVisible(false);
        addChild(m_FAQ, 9999);
        
        m_line = CCLoadSprite::createSprite("FAQ_line.png");
        m_line->setAnchorPoint(ccp(0.5, 0));
        m_line->setScaleX(m_FAQ->getContentSize().width/m_line->getContentSize().width-5);
        m_line->setPosition(ccp(_tipX + m_loadtips->getContentSize().width/2 - __height,33-m_FAQ->getContentSize().height/2) + addPt);
        m_line->setVisible(false);
        addChild(m_line, 9999);
        
        m_FAQTouchNode = CCNode::create();
        m_FAQTouchNode->setContentSize(Size(m_FAQ->getContentSize().width +10, m_FAQ->getContentSize().height+10));
        m_FAQTouchNode->setAnchorPoint(ccp(0.5, 0.5));
        m_FAQTouchNode->setPosition(ccp(_tipX + m_loadtips->getContentSize().width/2,30) + addPt);
        m_FAQTouchNode->setScale(2);
        addChild(m_FAQTouchNode);
        
        float ratio = 3.0f;
        if(CCApplication::sharedApplication()->getTargetPlatform() == kTargetIpad || CCCommonUtils::isAdriodPad())
            ratio = 3.65f;
        
        CCSize lbBGsz = loadingBar->getContentSize();
        CCNode* processNode = CCNode::create();
        processNode->setPosition(ccp(0, -lbBGsz.height*ratio*(1-theScaleY)));
        this->addChild(processNode,100,100);
        
        loadingBar->setPosition(ccp(size.width/2,lbBGsz.height*ratio) + addPt);
        processNode->addChild(loadingBar);
        
        CCSize lpsz = CCSizeMake(530, 35);
        m_barSize = lpsz+CCSizeMake(0, 30);
        m_loadingProgress->setAnchorPoint(ccp(0,0));
        m_loadingProgress->setPosition(ccp(26, lpsz.height/2-1));
        m_barClipNode = CCClipNode::create(0, m_barSize.height);
        m_barClipNode->addChild(m_loadingProgress,200);
        m_barClipNode->setPosition(ccp((size.width-lpsz.width)/2,lbBGsz.height*ratio-lpsz.height) + addPt);
        processNode->addChild(m_barClipNode,200);
        loadingBarBG->setPosition(ccp(size.width/2,lbBGsz.height*ratio) + addPt);
        processNode->addChild(loadingBarBG);
        
        auto rotateSprite = CCLoadSprite::createSprite("loading_1.png");
        rotateSprite->setPosition({size.width/2, -lbBGsz.height*ratio*(1-theScaleY) + lbBGsz.height*ratio });
        this->addChild(rotateSprite, 110,110);
        rotateSprite->setVisible(false);
        
        auto processLayerColor = CCLayerColor::create(Color4B::GREEN,530.0f, 5.0f);
        processLayerColor->setPosition((size.width - 530.0f)/2.0f,-lbBGsz.height*ratio*(1-theScaleY) + lbBGsz.height*ratio - 30);
        processLayerColor->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        processLayerColor->ignoreAnchorPointForPosition(false);
        processLayerColor->setVisible(false);
        this->addChild(processLayerColor, 111,111);
        
        clipNode->setPosition(ccp(m_barClipNode->getPositionX()+28,m_barClipNode->getPositionY()+lpsz.height/2-4));
        processNode->addChild(clipNode,199);
        
        m_loadPerLabel = CCLabelIF::create();
        m_loadPerLabel->setColor(Color3B(255, 150, 150));
        m_loadPerLabel->setFontSize(22);
        m_loadPerLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
        m_loadPerLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        m_loadPerLabel->setAnchorPoint(ccp(0.5, 0.5));
        m_loadPerLabel->setPosition(ccp(size.width / 2, lbBGsz.height*ratio));
        m_loadPerLabel->setVisible(false);
        processNode->addChild(m_loadPerLabel, 222);
        
        //加流动的光
        m_clipNode = CCClipNode::create(m_barClipNode->getContentSize().width, m_barClipNode->getContentSize().height);
        
        //加进度条头上的光效
        m_headParticleNode = CCNode::create();
        
        
        auto tipsBg = CCLoadSprite::createSprite("loading_tips_bg.png");
        tipsBg->setTag(LOADING_3);
        tipsBg->setAnchorPoint(ccp(0.5, 0.5));
        tipsBg->setScaleY(3);
        tipsBg->setScaleX(5);
        tipsBg->setPosition(ccp(size.width/2, m_loadtips->getPosition().y + 60));
        addChild(tipsBg);
        
        auto tipsSize = CCSizeMake(tipsBg->getContentSize().width, tipsBg->getContentSize().height);
        
        m_loadingTips = CCLabelIF::create("loading...");
        m_loadingTips->setColor(ccWHITE);
        m_loadingTips->setFontSize(24);
        m_loadingTips->setDimensions(CCSizeMake(630, 160));
        m_loadingTips->setHorizontalAlignment(kCCTextAlignmentCenter);
        m_loadingTips->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        m_loadingTips->setAnchorPoint(ccp(0.5, 0.5));
        m_loadingTips->setPosition(ccp(size.width / 2, tipsBg->getPosition().y));
        addChild(m_loadingTips);
        
        int posy = 100;
        if(CCApplication::sharedApplication()->getTargetPlatform() == kTargetIpad || CCCommonUtils::isAdriodPad())
            posy = 100;
        
        m_faceBookLater = CCLabelIF::create(_lang("83000154").c_str(), 30);
        m_faceBookLater->setPosition(ccp(size.width/2, posy));
        m_faceBookLater->setAnchorPoint(ccp(0.5,0.5));
        addChild(m_faceBookLater,9999,300);
        m_faceBookLater->setVisible(false);
        
        m_laterLine= CCLayerColor::create();
        m_laterLine->setColor(ccWHITE);
        m_laterLine->setPosition(ccp(size.width/2 - m_faceBookLater->getContentSize().width/2, posy - 15));
        m_laterLine->setOpacity(255);
        m_laterLine->setContentSize(CCSizeMake(m_faceBookLater->getContentSize().width,1));
        addChild(m_laterLine,9999,400);
        m_laterLine->setVisible(false);
        
        m_LaterTouchNode = CCNode::create();
        m_LaterTouchNode->setPosition(ccp(size.width/2, posy));
        m_LaterTouchNode->setContentSize(CCSizeMake(size.width/3,60));
        m_LaterTouchNode->setAnchorPoint(ccp(0.5,0.5));
        addChild(m_LaterTouchNode);
        m_LaterTouchNode->setVisible(false);
        
        m_fbBindBtn = CCControlButton::create();
        m_fbBindBtn = CCControlButton::create(CCLoadSprite::createScale9Sprite("loading_facebook.png"));
        m_fbBindBtn->setPreferredSize(CCSizeMake(237,62));
        m_fbBindBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LoadingScene::onFacebookClick), CCControlEventTouchUpInside);
        m_fbBindBtn->setPosition(ccp(size.width/2, posy + m_LaterTouchNode->getContentSize().height + 20));
        addChild(m_fbBindBtn);
        m_fbBindBtn->setVisible(false);
        
        m_type = 1;
        
        if(CCFileUtils::sharedFileUtils()->isFileExist("platform_logo.png")) {
            // 渠道logo
            m_platformLogo = CCSprite::create("platform_logo.png");
            if(m_platformLogo) {
                CCSize size = CCDirector::sharedDirector()->getWinSize();
                m_platformLogo->setPosition(ccp(size.width/2, size.height/2));
                addChild(m_platformLogo);
            }
        }
        m_isAiService = false;
        bRet = true;
    }
    std::string language = LocalTextController::shared()->getLanguageFileName();
    ECServiceCocos2dx::setSDKLanguage(language.c_str());
    CCLOG("test init end");
    m_tempLoadingNode = CCNode::create();
    m_tempLoadingNode->setObjAnimation(true);
    m_tempLoadingNode->retain();
    
    return bRet;
}

void LoadingScene::createLoadingCN()
{
    string lang = LocalTextController::shared()->getLanguageFileName();
    if ("zh_CN" == lang){
        auto loadCN = LoadingCNScene::create(this);
        loadCN->setTag(CNSCENE_TAG);
        this->addChild(loadCN, CNSCENE_TAG);
    }
}

void LoadingScene::showChangeServer(CCObject* obj){
    
    if( obj != nullptr ) {
        CCBool* val = dynamic_cast<CCBool*>(obj);
        if( val != nullptr && !val->getValue() ) {
            NetSettingPopView::setNetSettingEnable(false);
            return;
        }
    }
    
    m_progress = 0.0f;
    scheduleOnce([=](float dt){
        //全局开启服务器选择， 帮助玩家选择服务器
        if (true || CCCommonUtils::isChina()){
            auto _downType = GlobalData::shared()->m_downloadType;
            int iNeedNum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(_downType);
            if( iNeedNum <= 0 || iNeedNum == 9999 )
            {
                if(GlobalData::shared()->isFinshArCameraState){
                    if( NetSettingPopView::isNetSettingExist()) {
                        return;
                    }
                    if( NetSettingPopView::isNetSettingEnable() ) {
                        PopupViewController::getInstance()->addPopupView(NetSettingPopView::create(true), false, true, false);
                    }
                }
            }
        }
    }, 20, "showChangeServer");
}

void LoadingScene::initLoadingImageBg(CCSize size)
{
    bool _use_config = isUseLoadingConfig();
    std::string page_up = "loading_page_up.png";
    std::string page_down = "loading_page_down.png";
    if (_use_config){
        page_up = "loading_page_up_"+loadingBg_config+".png";
        page_down = "loading_page_down_"+loadingBg_config+".png";
    }
    auto loadingPageUp = CCLoadSprite::createSprite(page_up.c_str());
    if (GlobalData::shared()->isMiddleEast()) {
        loadingPageUp = CCLoadSprite::createSprite("loading_page_up_cafe.png");
    }
    loadingPageUp->setPosition(ccp(size.width/2, size.height/2));
    loadingPageUp->setAnchorPoint(ccp(0.5, 0));
    CCLOG("w %f,h %f",loadingPageUp->getContentSize().height,loadingPageUp->getContentSize().width);
    this->addChild(loadingPageUp);
    
    auto loadingPageDown = CCLoadSprite::createSprite(page_down.c_str());
    if (GlobalData::shared()->isMiddleEast()) {
        loadingPageDown = CCLoadSprite::createSprite("loading_page_down_cafe.png");
    }
    loadingPageDown->setPosition(ccp(size.width/2, size.height/2));
    loadingPageDown->setAnchorPoint(ccp(0.5, 1));
    CCLOG("w %f,h %f",loadingPageDown->getContentSize().height,loadingPageDown->getContentSize().width);
    this->addChild(loadingPageDown);
    
    auto loadingLogo = CCLoadSprite::createSprite("loading_logo.png");
    if (GlobalData::shared()->isMiddleEast()) {
        loadingLogo = CCLoadSprite::createSprite("loading_logo_cafe.png");
    }
    std::string sysLanguage = cocos2d::extension::CCDevice::getLanguage();
    if(sysLanguage.find("zh_CN")<sysLanguage.length() || sysLanguage.find("zh-Hans")<sysLanguage.length()){
        loadingLogo = CCLoadSprite::createSprite("loading_logo_cn.png");
    }
    loadingLogo->setPosition(ccp(size.width-loadingLogo->getContentSize().width/2-20, size.height-loadingLogo->getContentSize().height/2-45));
    loadingLogo->setAnchorPoint(ccp(0.5, 0.5));
    CCLOG("w %f,h %f",loadingLogo->getContentSize().height,loadingLogo->getContentSize().width);
    this->addChild(loadingLogo);
}

bool LoadingScene::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_FAQ->isVisible() && isTouchInside(m_FAQTouchNode, pTouch)) {
        AZCommonUtils::onShowGuest("loading");
        return true;
    }
    
    if(m_LaterTouchNode->isVisible() && isTouchInside(m_LaterTouchNode, pTouch)){
        GlobalData::shared()->showFaceBookUi = false;
        string loadingAct = CCUserDefault::sharedUserDefault()->getStringForKey(FB_ACTION,"");
        if(loadingAct.compare("") != 0){
            CCCommonUtils::recordStep("152000003");
            CCUserDefault::sharedUserDefault()->setStringForKey(FB_ACTION,"later");
            CCUserDefault::sharedUserDefault()->flush();
        }
        this->scheduleOnce([this](float dt){
            stepLoading(nullptr);
        }, 0.01f, "StepLoading");
        return true;
    }
    return false;
}
void LoadingScene::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void LoadingScene::onFacebookClick(CCObject *pSender, CCControlEvent event)
{
    
    string localCus = CCUserDefault::sharedUserDefault()->getStringForKey(FB_USERID,"");
    string loadingAct = CCUserDefault::sharedUserDefault()->getStringForKey(FB_ACTION,"");
    if(loadingAct.compare("") == 0){
        CCCommonUtils::recordStep("152000002");
        CCUserDefault::sharedUserDefault()->setStringForKey(FB_ACTION,"fb_bind");
        CCUserDefault::sharedUserDefault()->flush();
    }

    CCLOG("[onFacebookClick] m_type:%d, fbUid:%s", m_type, localCus.c_str());
    if (m_type==1)
    {//绑定账号
        if (localCus != "")
        {//已经绑定fb  提示是否解绑
            //            PopupViewController::getInstance()->addPopupView(ChangeAccountView::create(1));
//            PopupViewController::getInstance()->addPopupView(WarningView::create(_lang("105261"), _lang("105250"), CCCallFunc::create(this, callfunc_selector(SetAccountNextView::DisconnectFacebook))));
        }else
        {
            OpenLoginFB();
        }
        CCLOG("m_type:%d, fbUid:%s", m_type, localCus.c_str());
    }
    else if (m_type==2)
    {//切换账号
        string gpUid = CCUserDefault::sharedUserDefault()->getStringForKey(GP_USERID,"");
        string _qqUid = CCUserDefault::sharedUserDefault()->getStringForKey(OICQ_USERID,"");
        string _weiboUid = CCUserDefault::sharedUserDefault()->getStringForKey(WEIBO_USERID,"");
        string account = CCUserDefault::sharedUserDefault()->getStringForKey("AZ_Account","");
        int status = CCUserDefault::sharedUserDefault()->getIntegerForKey("AZ_AccountStatus",0);
        if (localCus != "" || gpUid!="" || _qqUid!= "" || _weiboUid!="" || (account != "" && status==1))
        {//已经绑定fb  直接显示登录fb
            OpenLoginFB();
        }else
        {//当前账号未绑定 提示警告
            PopupViewController::getInstance()->addPopupView(WarningView::create(_lang("105261"), _lang("105277"), CCCallFunc::create(this, callfunc_selector(LoadingScene::OpenLoginFB))));
        }
        CCLOG("m_type:%d, fbUid:%s, gpUid:%s", m_type, localCus.c_str(), gpUid.c_str());
    }
}
void LoadingScene::OpenLoginFB(){
        scheduleOnce(schedule_selector(LoadingScene::OpenLoginFBReally), 0.01);
}

void LoadingScene::OpenLoginFBReally(float t){
    if (FBUtilies::fbIsLogin())
    {
        FBUtilies::fbLogout();
    }
    GlobalData::shared()->isBind = 39;
    bool flag = FBUtilies::fbLogin();
    if(!flag){
        GlobalData::shared()->isBind = false;
        CCCommonUtils::flyHint("", "", _lang("107080"),FLYHINT_PUNISH);
    }
    
}

void LoadingScene::showFaceBookUI(CCObject *obj){
    if(CCCommonUtils::checkIsOpenByKey("loading_facebook")){
        if(m_fbBindBtn)
            m_fbBindBtn->setVisible(true);
        if(m_laterLine)
            m_laterLine->setVisible(true);
        if(m_faceBookLater)
            m_faceBookLater->setVisible(true);
        
        if(m_LaterTouchNode){
            m_LaterTouchNode->setVisible(true);
        }
        if(this->getChildByTag(100))
            this->getChildByTag(100)->setVisible(false);
        if(this->getChildByTag(LOADING_3))
            this->getChildByTag(LOADING_3)->setVisible(false);
        m_loadingTips->setVisible(false);
    }
}

void LoadingScene::hideFaceBookUI(CCObject *obj){
    if(m_fbBindBtn)
        m_fbBindBtn->setVisible(false);
    if(m_laterLine)
        m_laterLine->setVisible(false);
    if(m_faceBookLater)
        m_faceBookLater->setVisible(false);
    if(m_LaterTouchNode){
        m_LaterTouchNode->setVisible(false);
    }
    if(this->getChildByTag(LOADING_3))
        this->getChildByTag(LOADING_3)->setVisible(true);
    m_loadingTips->setVisible(true);
}
void LoadingScene::FacebookCallback(CCObject *obj){

    //    防止facebook回来界面关闭
    //    GlobalData::shared()->isBind = false;
    CCLOG("2-2");
    GameController::getInstance()->showWaitInterface();
    CCSafeNotificationCenter::sharedNotificationCenter()->postNotification(MSG_GameStart);
    m_facebookUid =CCUserDefault::sharedUserDefault()->getStringForKey("tmpFaceBook_uid", "");
    string picUrl =CCUserDefault::sharedUserDefault()->getStringForKey("tmpFaceBook_picUrl", "");
    if (m_facebookUid == "") {
        return;
    }
    CCLOG("2-3 = %s",m_facebookUid.c_str());
    loginFacebookAction();
//#if COCOS2D_DEBUG  == 1
//    string cc = m_facebookName.append(",").append(picUrl);
//    bindFaceBook(CCString::create(cc));
//#endif
    return;
}

void LoadingScene::loginFacebookAction(){
    m_facebookUid = CCUserDefault::sharedUserDefault()->getStringForKey(FB_USERID, "");
    m_facebookName = CCUserDefault::sharedUserDefault()->getStringForKey(FB_USERNAME, "");
    if(m_facebookUid.compare("")!= 0){
        return;
    }
    GameController::getInstance()->showWaitInterface();
    CCLOG("3");
    m_facebookUid = CCUserDefault::sharedUserDefault()->getStringForKey("tmpFaceBook_uid","");
    CCLOG("4 = %s",m_facebookUid.c_str());
    CCLOG("6 = %s",m_facebookUid.c_str());
    
    int m_optType= 1;
    GameController::getInstance()->showWaitInterface();
    CCLOG("7");
    m_facebookName = CCUserDefault::sharedUserDefault()->getStringForKey("tmpFaceBook_Name","");
    CCLOG("8 = %s",m_facebookName.c_str());
    string accessToken = CCUserDefault::sharedUserDefault()->getStringForKeyWithEnc("tmpFaceBook_token");
    string fbEmail = CCUserDefault::sharedUserDefault()->getStringForKey("tmpFaceBook_email", "");
    UserBindCommand* cmd = new UserBindCommand("",m_facebookUid,"","","",m_optType,"","",m_facebookName,"","","","","",accessToken,fbEmail);
    cmd->sendAndRelease();
}

void LoadingScene::bindFaceBook(CCObject* p){
    this->scheduleOnce([this](float dt){
        stepLoading(nullptr);
    }, 0.01f, "StepLoading");
}
void LoadingScene::onGoToHelpShift(CCObject* p)
{
    this->m_bShowConfirmPanel = true;
    cocos2d::ValueVector tags;
    cocos2d::ValueMap config;
    cocos2d::ValueMap meta;
    tags.push_back(Value(CCString::create("loading")->getCString()));
    auto cokZone = NetController::shared()->getZone();
    tags.push_back(Value(CCString::createWithFormat("s%s",cokZone.substr(3).c_str())->getCString()));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    tags.push_back(Value(CCString::create("ios")->getCString()));
#else
    string channel = GlobalData::shared()->analyticID;
    if(channel == "market_global") {
        channel = "google";
    }
    tags.push_back(Value(CCString::create(channel)->getCString()));
#endif
    //金鹏:附带小版本号
    string _versionCode = cocos2d::extension::CCDevice::getVersionCode();
    tags.push_back(Value(CCString::createWithFormat("%s",_versionCode.c_str())->getCString()));
    if(GlobalData::shared()->isNewServer){
        tags.push_back(Value("新服"));
    }
    
    meta[HS_TAGS_KEY] = Value(tags);
    
    meta["VersionCode"] = Value(CCString::create(_versionCode)->getCString());
    
    //金鹏:添加额外信息看下请求数据
    string errorLog = CCCommonUtils::format("==sid:%d, ip:%s, port:%d, zoon:%s, ErrorLog:%s",
                                            NetController::shared()->getServerId(),
                                            NetController::shared()->getIp().c_str(),
                                            NetController::shared()->getPort(),
                                            NetController::shared()->getZone().c_str(),
                                            GameController::getInstance()->getLoginErrorLog().c_str()
                                            );
    string loadingLog = GameController::getInstance()->getLoadingLogString();
    string netinfo = errorLog + loadingLog + "==new check net log:" + m_checkNetLog;
    meta["loadingLog"] = Value(CCString::create(netinfo)->getCString());
    config[HS_META_DATA_KEY] = meta;//xz change_sym
    GlobalData::shared()->isBind = 23;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ECServiceCocos2dx::showSingleFAQ("15447",config);
#else
    ECServiceCocos2dx::showSingleFAQ("15448",config);
#endif
    
    char msg[128] = {0};
    sprintf(msg, "time[%.2fs]", m_loadingTotalTime);
    cocos2d::extension::CCDevice::sendTraceLogToHelpshift("loading", msg);
}

void LoadingScene::onEnter(){
    Director::sharedDirector()->setAnimationInterval(1.0 / 60);
    g_isInLoadingScene = true;
    
    CCLayer::onEnter();
    
    //做sd卡授权的回调
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::getSDcardPermit), "ar_get_sdcard_permit", nullptr);
    if (CCFileUtils::sharedFileUtils()->isFileExist("gp_no_obb.txt")){
        toOnEnter();
        return;
    }
#if COCOS2D_DEBUG > 0 || COCOS2D_DEBUG_LOCAL == 1
    toOnEnter();
#else
    scheduleOnce([this](float t){
        std::string pf = cocos2d::extension::CCDevice::getPublishRegion();
        if ( pf.compare("market_global") == 0 ){
            auto result = cocos2d::extension::CCDevice::getSDcardPermission();
            if ( result == 0){
                getSDcardPermit(CCBoolean::create(true));
            }else if (result == -1){
                CCCommonUtils::flyText(_lang("173050"));
            }
        }else{
            toOnEnter();
        }
    }, 0.2, "show_zip");
#endif
    
    
}

void LoadingScene::toOnEnter(){
    if( !g_isSuccessUnZip ) {
        m_loadingTips->setString(LocalResourceController::getInstance()->getLoadingTipsString());
        auto loadingIcon = this->getChildByTag(110);
        if( loadingIcon) {
            loadingIcon->setVisible(true);
            CCActionInterval * rotateto1 = CCRotateTo::create(0.5, 720);
            CCFiniteTimeAction* rotateAction = CCSequence::create(rotateto1,NULL);
            CCActionInterval * rotateForever =CCRepeatForever::create((CCActionInterval* )rotateAction);
            loadingIcon->runAction(rotateForever);
        }
        
        auto progressIcon = this->getChildByTag(111);
        if( progressIcon) {
            progressIcon->setVisible(true);
            progressIcon->setScaleX(0.001f);
        }
        
        this->getChildByTag(100)->setVisible(false);
        this->schedule([this, loadingIcon,progressIcon](float t) {
            
            if( !g_isSuccessUnZip ) {
                int currentNum = g_currentNum > 1 ? g_currentNum : 1;
                float currentProcess = (currentNum - 1) * 1.0f / g_allNum;
                float nextProcess = currentNum * 1.0f / g_allNum;
                float oldScaleX = progressIcon->getScaleX();
                if( oldScaleX < currentProcess && currentProcess > 0.0f && currentProcess <= 1.0f ) {
                    progressIcon->setScaleX(currentProcess);
                }
                else {
                    float newScaleX = oldScaleX + 0.001f;
                    if( newScaleX < nextProcess && newScaleX > 0.0f && newScaleX <= 1.0f) {
                        progressIcon->setScaleX(newScaleX);
                    }
                }
            }
            
        }, 0.2, "loading_uncompress_progress");
        
        this->schedule([this, loadingIcon,progressIcon](float t) {

            if( !g_isSuccessUnZip ) {
                this->setNetCurrentStatus(nullptr);
            }
            else {
                
                if(loadingIcon) {
                    loadingIcon->pauseSchedulerAndActions();
                    loadingIcon->setVisible(false);
                }
                if(progressIcon) {
                    progressIcon->setVisible(false);
                }
                this->getChildByTag(100)->setVisible(true);
                this->unschedule("loading_uncompress_resource");
                this->unschedule("loading_uncompress_progress");
                
                m_loadingTips->setString("");
                m_loadingTips->setVisible(true);
                this->onEnterProc();
            }

        }, 0.5, "loading_uncompress_resource");
    }
    else {
        this->onEnterProc();
    }
}

void LoadingScene::getSDcardPermit(CCObject* obj){
    cocos2d::CCLog(">>> lsz 3 ");
    bool result = false;
    if( obj != nullptr ) {
        CCBoolean* val = dynamic_cast<CCBoolean*>(obj);
        cocos2d::CCLog(">>> lsz 3 val - %d", val->getValue());
        if( val != nullptr) {
            if (val->getValue()){
                result = true;
                cocos2d::CCLog(">>> lsz 3 - true");
            }else{
                cocos2d::CCLog(">>> lsz 3 - false");
            }
        }
    }
    
    if (result == true){
        cocos2d::CCLog(">>> lsz 5 - to unzip");
        LocalResourceController::getInstance()->initUnzipLocalFile();
        toOnEnter();
    }else{
        scheduleOnce([](float dt)
                     {
                          CCCommonUtils::flyText(_lang("173050"));
                     }, 0.5, "FlY_LOAIDNG_PERMISSION_FAIL");
       
    }
}

void LoadingScene::onEnterProc() {

    scheduleOnce([](float dt){
        if (GlobalData::shared()->isPushInitReturn == false)
            CCCommonUtils::recordStepByHttp("14", "linetimeout", "login");
    }, 10, "LOADING_CHECK_TIMEOUT");

    NetSettingPopView::setNetSettingEnable(true);
    CCLOG("LoadingScene::onEnter %.2f", m_loadingTotalTime);
#if COCOS2D_DEBUG == 0
    Director::getInstance()->getScheduler()->schedule([this](float dt) {
        onLoadingProgressNew(dt);
    }, m_tempLoadingNode, 0.0f, false, "schedule_loadingbar_progress");
#endif
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::showChangeServer), "LOADING_SHOW_CHANGESERVER", nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::showChangeServer), "server_offline", nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::doXMLParserInit), MSG_TEMP_PUSH_CACHE_INIT, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::showPasswordUI), "show_password_ui", nullptr);
//    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::loadingGPLoginCallback), "onResponsed3rdPlatformLoading", nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::doLogin), MSG_GameStart, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::doLoginInitError), MSG_LoginInitError, nullptr);
    
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::doLoginantiAddiction), "antiAddiction_loginerror", nullptr);
    
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::doResourceUpdate), MSG_LoginSucess, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::loginInitFinsh), MSG_INIT_FINISH, nullptr);
//    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::localUnzipFinsh), LOCAL_UNZIP_FINISH, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::onRelogin), MSG_RELOGIN, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::loadContinue), LOADING_RELOAD, nullptr);
    
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::onEnterFrame), MSG_SHOW_LOADINGS_FQA, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::onResponsed_3rdPlatform), MSG_RESPONSED_3RD_PLATFORM, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::setNetCurrentStatus), "msg_net_current_status", nullptr);
    
    if (_enableCheckNet) {
        CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::checkNetStep2Ok), NET_CONNECTED, nullptr);
        CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::checkNetStep2Error), SFS_CONNECT_ERROR, nullptr);
    }
    
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::onNetworkAvailable), "NetworkAvailable", nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::FacebookCallback), MSG_FBLoginSucess, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::bindFaceBook), MSG_USER_BIND_OK, nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::offerUpdate), MSG_GameLoading, nullptr);
//    CCSafeNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoadingScene::stepLoading), MSG_GameLoading, nullptr);
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
    
    std::string _shortItemType = GlobalData::shared()->shortItemType;
    if (!_shortItemType.compare(shortItemType_clearCache) )
    {
        if (m_bShowConfirmPanel){
            m_bShowConfirmPanel = false;
            auto _dialog = YesNoDialog::show(_lang("139505").c_str()
                                             , CCCallFuncO::create(this, callfuncO_selector(LoadingScene::clearCacheOK), nullptr)
                                             , 0
                                             , true
                                             , CCCallFuncO::create(this, callfuncO_selector(LoadingScene::clearCacheCancel), nullptr)
                                             );
            _dialog->showCancelButton();
            _dialog->setYesButtonTitle(_lang("101274").c_str());
            _dialog->setNoButtonTitle(_lang("108532").c_str());
        }
        return;
    }
    //暂时使用了string干了bool的事儿
    string notLoginGPAgain = CCUserDefault::sharedUserDefault()->getStringForKey("notLoginGPAgain","false");
    if(notLoginGPAgain == "false")
    {
        doLoginGP();
    }
    
    //TODO:aims 指定账号入口分开
#if COCOS2D_DEBUG > 1 // by aims
    string gameUid;
    if (gameUid.empty()) {
        gameUid = CCCommonUtils::getStringWithEncBySharedUser(GAME_UID);
    }
    
    int server = 0;
    switch(server) {
        case 0://正式服
            showLoading(8004, "1276567958000375");
            break;
        case 1://21测试服
            showLoading("9933", "COK42", "10.0.0.42", "388505658000279");
            break;
        case 2://16测试服
            showLoading("9933", "COK2", "10.0.0.16", "50512315000002");
            break;
        case 3://线上测试服
//            showLoading("9933", "COK41", "10.0.0.41", "134776000041");
            showLoading("9933", "COK41", "10.0.0.41", "703403626000446");
            
            break;
        default://其它测试服
            showLoading("9933", "COK9001", "10.0.1.39", "104809000045");
            break;
    }
#elif COCOS2D_DEBUG == 1
    scheduleOnce(schedule_selector(LoadingScene::forceDoHttpGlobeSwitchCallback), 2.0f);//
#else
    scheduleOnce(schedule_selector(LoadingScene::forceDoHttpGlobeSwitchCallback), 0.0f);//
#endif
    // 这里延迟加载是为了等待appsflyer返回media_source，在getserverlist中用到
    CCDelayTime* delayAction = CCDelayTime::create(0.01);
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(LoadingScene::onEnterInit));
    this->runAction(CCSequence::createWithTwoActions(delayAction, callFunc));

    showChangeServer(nullptr);

    g_retry_connect = 0;
}

void LoadingScene::onEnterInit()
{
    //music
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    long dur = (long)std::chrono::duration_cast<std::chrono::microseconds>(end -start).count();
    CCLOG("guokai LocalController::shared()->init() %ld", dur );

    auto _glExtensions = (char *)glGetString(GL_EXTENSIONS);

    GlobalData::shared()->analyticID = cocos2d::extension::CCDevice::getPublishRegion();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    GlobalData::shared()->fromCountry = AppLibHelper::getLocalCountry();
#endif
    //重置平台id
    GlobalData::shared()->platformUID = "";
    if(GlobalData::shared()->analyticID == "common")
    {
        auto layer = CCLayerColor::create(ccc4(0, 0, 0, 200), CCDirector::sharedDirector()->getWinSize().width, 70);
        this->addChild(layer);
        layer->setAnchorPoint(ccp(0.5, 0));
        auto addY = [](int add,CCNode *node){
            if(node){
                node->setPositionY(node->getPositionY() + add);
            }
        };
        
        int add = 110;
        addY(add, m_loadPerLabel);
        addY(add, m_loadtips);
        addY(add, m_FAQ);
        addY(add, m_line);
        addY(add, m_FAQTouchNode);
        addY(add, m_barClipNode);
        addY(add, m_clipNode);
        addY(add, m_headParticleNode);
        addY(add, this->getChildByTag(LOADING_1));
        addY(add, this->getChildByTag(LOADING_2));
        addY(add, this->getChildByTag(LOADING_3));
        addY(add, this->getChildByTag(LOADING_4));
    }
    //中国服，除了伊朗
    if (NetController::shared()->isChina() && !NetController::shared()->isIran()){
        string lang = LocalTextController::shared()->getLanguageFileName();
        if ("zh_CN" == lang){
            auto label = CCLabelIF::create(_lang("79000408").c_str(), 22);
            this->addChild(label);
            label->setColor(ccc3(255, 236, 171));
            label->setDimensions(CCSize(CCDirector::sharedDirector()->getWinSize().width - 16, 0));
            label->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height-40));
        }
    }
    setLoadingTips();
    //为月卡做记录
    int loadCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("day_load_count")+1;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("day_load_count", loadCount);
    CCUserDefault::sharedUserDefault()->flush();
    
    //TODO:jinpeng 网络监测第一步
    checkNetStep1(nullptr);
    
    GuideController::share();
    
    this->scheduleUpdate();
    
    Application::getInstance()->runInBackThread([this]{
        BACK_PROCESS_THREAD_ID = pthread_self();
        CCDirector::getInstance()->setAutoReleasePoolEnable(false);
        CCLoadSprite::prepareImperialResourceCacheWhenLoading();
        CCDirector::getInstance()->setAutoReleasePoolEnable(true);
    });
}
void LoadingScene::showLoading(int serverId, string gameUid)
{
    string port;
    CCString strIP;
    CCString strCOK;
    if (0 < serverId) {
        port = "9933";
        strCOK.initWithFormat("COK%d",serverId);
        strIP.initWithFormat("s%d.az.im30app.com",serverId);
        showLoading(port, strCOK.getCString(), strIP.getCString(), gameUid);
    }
    else {
        CCCommonUtils::setStringWithEncBySharedUser(GAME_UID, gameUid);
//        CCUserDefault::sharedUserDefault()->setIntegerForKey("CONNECT_TIMES", CONNECT_TIMES);
        CCCommonUtils::setStringWithEncBySharedUser(ACCOUNT_IP, "s1.az.im30app.com");
        CCUserDefault::sharedUserDefault()->flush();
        sendCmdGetServerList(nullptr);
    }
}

void LoadingScene::loadingGPLoginCallback(CCObject* p)
{
//    CCString* jsonCCStr=dynamic_cast<CCString*>(p);
//    string jsonStr=jsonCCStr->getCString();
//    
//    CCLOG(CCString::createWithFormat("loadingGPLoginCallback:%s",jsonStr.c_str())->getCString());
//    Json *jsonObj = Json_create(jsonStr.c_str());
//    if( jsonObj == nullptr ){
//        CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPName","-1");
//        CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPUid", "-1");
//        CCUserDefault::sharedUserDefault()->setBoolForKey("notLoginGPAgain", false);
//        CCUserDefault::sharedUserDefault()->flush();
//        return;
//    }
//    string _msgId=Json_getString(jsonObj, "msgId", "");
//    string _userName=Json_getString(jsonObj, "userName", "");
//    string _displayName=Json_getString(jsonObj, "displayName", "");
//    string _userId=Json_getString(jsonObj, "userId", "");
//    string _platform=Json_getString(jsonObj, "platform", "");
//    string _accessToken=Json_getString(jsonObj, "accessToken", "");
//    string _refreshToken=Json_getString(jsonObj, "refreshToken", "");
//    CCLOG("platform login %s, %s, %s, %s , %s ,%s", _msgId.c_str(), _userName.c_str(), _userId.c_str(), _platform.c_str(), _accessToken.c_str(), _refreshToken.c_str());
//    Json_dispose(jsonObj);
//    if (_msgId != ""){//有数据
//        if (_msgId=="login_sucess_google") {
//            //使用此用户名，绑定到游戏
//            if (_userName != ""){//注意userName可以为空
//                
//                CCLOG(CCString::createWithFormat("login_sucess_google account:%s,%s m_operation_type:%d",_userName.c_str(),_userId.c_str(),6)->getCString());
//                GlobalData::shared()->platformUID = _userId;
//                CCLOG("xzz justlogin platform google = %s",_userId.c_str());
//                GlobalData::shared()->m_loading_loginGP_success = true;
//                GlobalData::shared()->platformChannel = "google";
//                CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPName",_displayName);
//                CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPUid", _userId);
//                //不管登录是否成功  都不再继续登录  登录的时间点只有一个就是清缓存
//                CCUserDefault::sharedUserDefault()->setBoolForKey("notLoginGPAgain", false);
//                CCUserDefault::sharedUserDefault()->flush();
//                
//                CCLOG("~~loadingGPLoginCallback: %s", _displayName.c_str());
//            }else{
//                CCLOG("login_sucess_google: unkown");
//                GlobalData::shared()->m_loading_loginGP_success = true;
//            }
//        }else  if (_msgId=="login_failed_google") {
//            CCLOG(CCString::createWithFormat("login_failed_google account:%s,%s m_operation_type:%d",_userName.c_str(),_userId.c_str(),6)->getCString());
//            GlobalData::shared()->m_loading_loginGP_success = false;
//            CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPName","-1");
//            CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPUid", "-1");
//            CCUserDefault::sharedUserDefault()->setBoolForKey("notLoginGPAgain", false);
//            CCUserDefault::sharedUserDefault()->flush();
//        }else  if (_msgId=="login_canceled_google") {
//            GlobalData::shared()->m_loading_loginGP_success = false;
//            CCLOG("login_failed_google..");
//            CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPName","-1");
//            CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPUid", "-1");
//            CCUserDefault::sharedUserDefault()->setBoolForKey("notLoginGPAgain", true);
//            CCUserDefault::sharedUserDefault()->flush();
//            
//            
//        }else if(_msgId=="login_sucess_gamecenter"){
//            //使用此用户名，绑定到游戏
//            if (_userId != ""){
//                CCLOG(CCString::createWithFormat("login_sucess_gamecenter account:%s m_operation_type:%d",_userName.c_str(),1)->getCString());
//                
//                CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPName",_userName);
//                CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPUid", _userId);
//                GlobalData::shared()->m_loading_loginGP_success = true;
//                CCUserDefault::sharedUserDefault()->setBoolForKey("notLoginGPAgain", true);
//                CCUserDefault::sharedUserDefault()->flush();
//                
//            }else{
//                CCLOG("login_sucess_gamecenter: unkown");
//            }
//        }else if(_msgId=="login_failed_gamecenter"){
//            CCLOG("login_failed_gamecenter");
//            
//            GlobalData::shared()->m_loading_loginGP_success = false;
//            CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPName","-1");
//            CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPUid", "-1");
//            CCUserDefault::sharedUserDefault()->setBoolForKey("notLoginGPAgain", true);
//            CCUserDefault::sharedUserDefault()->flush();
//            
//        }else if(_msgId=="logout_sucess_gamecenter"){
//            
//        }
//        else{
//            GlobalData::shared()->m_loading_loginGP_success = false;
//            CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPName","-1");
//            CCUserDefault::sharedUserDefault()->setStringForKey("loadingGPUid", "-1");
//            CCUserDefault::sharedUserDefault()->setBoolForKey("notLoginGPAgain", true);
//            CCUserDefault::sharedUserDefault()->flush();
//        }
//    }
}

/**
 *第三方平台登录消息响应
 */
void LoadingScene::onResponsed_3rdPlatform(CCObject *obj)
{
    CCString* jsonCCStr=dynamic_cast<CCString*>(obj);
    string jsonStr=jsonCCStr->getCString();
    
    CCLOG(CCString::createWithFormat("onResponsed3rdPlatform:%s",jsonStr.c_str())->getCString());
    
    Json *jsonObj = Json_create(jsonStr.c_str());
    if( jsonObj == nullptr )
        return;
    string _msgId=Json_getString(jsonObj, "msgId", "");
    string _userName=Json_getString(jsonObj, "userName", "");
    string _userId=Json_getString(jsonObj, "userId", "");
    string _platform=Json_getString(jsonObj, "platform", "");
    string _accessToken=Json_getString(jsonObj, "accessToken", "");
    string _refreshToken=Json_getString(jsonObj, "refreshToken", "");
    string _gmail = Json_getString(jsonObj, "gmail", "");  //google账户邮箱
    CCLOG("platform login %s, %s, %s, %s , %s ,%s", _msgId.c_str(), _userName.c_str(), _userId.c_str(), _platform.c_str(), _accessToken.c_str(), _refreshToken.c_str());
    Json_dispose(jsonObj);
    if (_msgId != "")
    {//有数据
       
        if(_msgId=="login_sucess_gamecenter")
        {
            GameController::getInstance()->removeWaitInterface();
            //使用此用户名，绑定到游戏
            if (_userId != "")
            {
                CCLOG(CCString::createWithFormat("login_sucess_gamecenter account:%s m_operation_type:%d",_userName.c_str(),1)->getCString());
                
                string oneUID=CCUserDefault::sharedUserDefault()->getStringForKey("tmpGooglePlay_uid", "");
                
                string oneUName=CCUserDefault::sharedUserDefault()->getStringForKey("tmpGooglePlayName", "");
                
                string onePlatformName=CCUserDefault::sharedUserDefault()->getStringForKey("GameCenterPlayerName", "");
                
                bool  haveChange=false;
                if(oneUID.compare(_userId)!=0)
                {
                   CCUserDefault::sharedUserDefault()->setStringForKey("tmpGooglePlay_uid", _userId);
                    haveChange=true;
                }
                if(oneUName.compare(_userName)!=0)
                {
                    CCUserDefault::sharedUserDefault()->setStringForKey("tmpGooglePlayName",_userName);
                    haveChange=true;
                }
                if(onePlatformName.compare(_userName)!=0)
                {
                    CCUserDefault::sharedUserDefault()->setStringForKey("GameCenterPlayerName",_userName);
                    haveChange=true;
                }
                if(haveChange)
                {
                    CCUserDefault::sharedUserDefault()->flush();
                }
                
                AppLibHelper::updatePlatformScore(FunBuildController::getInstance()->getMainCityLv());
            }else
            {
                CCLOG("login_sucess_gamecenter: unkown");
            }
        }else if(_msgId=="login_failed_gamecenter")
        {
            GameController::getInstance()->removeWaitInterface();
            
        }else if(_msgId=="logout_sucess_gamecenter"){
        }
        else
        {
                GameController::getInstance()->removeWaitInterface();
                CCLOG("login_sucess_oicq: unkown");
        }
            
    }
}
void LoadingScene::showLoading(string port, string zone, string ip, string gameUid)
{
    if (port.empty()) {
        port = CC_ITOA(CCTypeDefinition::getServerPort());
    }
    if (zone.empty()) {
        zone = CCTypeDefinition::getServerZone();
    }
    if (ip.empty()) {
        ip = CCTypeDefinition::getServerIP();
    }
    int country = 8000;
    string sid = zone.substr(3);
    string _uuid = cocos2d::extension::CCDevice::getDeviceUid();
    
    GlobalData::shared()->loginServerInfo.recommandCountry = country;
    CCUserDefault::sharedUserDefault()->setStringForKey(ACCOUNT_UUID, _uuid);
    CCCommonUtils::setStringWithEncBySharedUser(ACCOUNT_IP, ip);
    CCCommonUtils::setStringWithEncBySharedUser(ACCOUNT_ZONE, zone);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(ACCOUNT_PORT,atoi(port.c_str()));
    
    CCUserDefault::sharedUserDefault()->setStringForKeyWithEnc(ACCOUNT_PORT, Value(port).asString());
    
    CCUserDefault::sharedUserDefault()->flush();
    CCCommonUtils::setStringWithEncBySharedUser(GAME_UID, gameUid);
    
    NetController::shared()->setIp(ip);
    NetController::shared()->setPort(atoi(port.c_str()));
    NetController::shared()->setZone(zone);
    
    CCSafeNotificationCenter::sharedNotificationCenter()->postNotification(MSG_GameStart);
}

void LoadingScene::forceDoHttpGlobeSwitchCallback(float dt) {
    this->getHttpGlobeSwitchCallback(nullptr, nullptr);
}

void LoadingScene::getHttpGlobeSwitchCallback(CCHttpClient* client, CCHttpResponse* response)
{
    if( m_hasDoHttpGlobalSwitchCallback ) {
        return;
    }
    m_hasDoHttpGlobalSwitchCallback = true;
    
    GameController::getInstance()->setLoadingLog("LoadingScene", "getHttpGlobeSwitchCallback");
                    //如果没有缓存的时候 看强制登录开关m_force_gp_login状态 1-强制登录 0-不登录
                    //如果强制登录开关打开 就登录 如果关着 就怎么都不登录
        //doLoginGP();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        //android的情况需要给google登陆留出时间
//    scheduleOnce(schedule_selector(LoadingScene::showLoading), 1.1f);
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   scheduleOnce(schedule_selector(LoadingScene::showLoading), 0.1f);
//#endif

}
void LoadingScene::doLoginGP()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (cocos2d::extension::CCDevice::isAvailable_Platform(0)) {
        cocos2d::extension::CCDevice::login_Platform_InChildThread(0);
    }
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    string key=CCUserDefault::sharedUserDefault()->getStringForKey("ios_name_open", "true");
    if(key.compare("true")==0)
    {
        PlatformUtilies::login_Platform(0,true);
    }

#endif
    
}
void LoadingScene::clearCacheOK(CCObject *obj)
{
    m_bShowConfirmPanel = true;
    GlobalData::shared()->shortItemType = "";
    CCCommonUtils::clearGameCache();
    GameController::getInstance()->quitGame();
}

void LoadingScene::clearCacheCancel(CCObject *obj)
{
    m_bShowConfirmPanel = true;
    GlobalData::shared()->shortItemType = "";
    onEnterInit();
}

void LoadingScene::onExit()
{
    currentLoading = nullptr;
    if(GlobalData::shared()->isInDataParsing){
        printDebugKeyInfo("LoadingError2", true);
        printBackTraceTolog("LoadingScene Should Not Removed!");
    }
    Director::sharedDirector()->setAnimationInterval(1.0 / 40);
    g_isInLoadingScene = false;
    g_isLoadingSceneInit = false;
    this->unscheduleUpdate();
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, "ar_get_sdcard_permit");
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, "LOADING_SHOW_CHANGESERVER");
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_TEMP_PUSH_CACHE_INIT);
//    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, "onResponsed3rdPlatformLoading");
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, "NetworkAvailable");
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, "antiAddiction_loginerror");
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_LoginInitError);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_LoginSucess);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_GameStart);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_INIT_FINISH);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, LOCAL_UNZIP_FINISH);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_RELOGIN);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, LOADING_RELOAD);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_SHOW_LOADINGS_FQA);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, "server_offline");
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_RESPONSED_3RD_PLATFORM);

    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this,"msg_net_current_status");
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, "show_password_ui");
    if (_enableCheckNet) {
        CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, NET_CONNECTED);
        CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, SFS_CONNECT_ERROR);
    }
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_FBLoginSucess);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_USER_BIND_OK);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_GameLoading);
    setTouchEnabled(false);
    Director::getInstance()->getScheduler()->unschedule("schedule_loadingbar_progress",m_tempLoadingNode);
    CC_SAFE_RELEASE_NULL(m_tempLoadingNode);
    CCLayer::onExit();
    
    if(loginCmd) {
        loginCmd->setFailCallback(nullptr);
        loginCmd = nullptr;
    }
}

void LoadingScene::update(float delta) {
    static float nTime = 0;
    if(m_loadingTotalTime < 1.0) {
        nTime = 0;
    }
    m_loadingTotalTime += delta;
    if(m_FAQ && (m_loadingTotalTime > 10.0) && !m_FAQ->isVisible() && m_updateFAQTips) {    //TODO:
        // 加载时间超过10秒，可以让玩家用Helpshift反馈
        m_loadtips->setVisible(true);
        m_FAQ->setVisible(true);
        m_line->setVisible(true);
        string theUuid = cocos2d::extension::CCDevice::getDeviceUid();
        std::string ip = CCCommonUtils::getStringWithEncBySharedUser(ACCOUNT_IP);
        if(ip.empty()) {
            ip = CCTypeDefinition::getServerListIP();
        }
        cocos2d::extension::CCDevice::testNetworkAndSendToHelpshift(theUuid, ip);
    }
    if(m_loadingTotalTime - nTime > 1.0) {
        nTime = m_loadingTotalTime;
    }
    if(!m_isAiService){
        bool isDisableAI = CCUserDefault::getInstance()->getBoolForKey("NOAIHelper", false);
        if( !isDisableAI ) {
            m_isAiService = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            ECServiceCocos2dx::init("4ef5afbeeb914f578e835ff781602cf2","im30.cs30.net","724912cc76e6e0e0b3426d0f83a88832");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            ECServiceCocos2dx::init("4ef5afbeeb914f578e835ff781602cf2","im30.cs30.net","lcyd_platform_20150630021209965-edefcf5f44a595e");
#endif
            ECServiceCocos2dx::setUserId(CCCommonUtils::getStringWithEncBySharedUser(GAME_UID));
            ECServiceCocos2dx::setName("Last Empire War Z");
            string server_id = CCCommonUtils::getServerIdBySharedUser();
            ECServiceCocos2dx::setServerId(Value(server_id).asInt());
        }
    }
}

void LoadingScene::onEnterFrame(CCObject* p)
{
    CCLOG("LoadingScene::onEnterFrame %.2f", m_loadingTotalTime);
    if(m_FAQ && !m_FAQ->isVisible()) {
        m_loadtips->setVisible(true);
        m_FAQ->setVisible(true);
        m_line->setVisible(true);
        string theUuid = cocos2d::extension::CCDevice::getDeviceUid();
        std::string ip = CCCommonUtils::getStringWithEncBySharedUser(ACCOUNT_IP);
        if(ip.empty()) {
            ip = CCTypeDefinition::getServerListIP();
        }
        cocos2d::extension::CCDevice::testNetworkAndSendToHelpshift(theUuid, ip);
    }
    //同时具有确定/反馈按钮   确定->取消当前面板   反馈->跳转到helpshift
    if (m_bShowConfirmPanel){
        this->m_bShowConfirmPanel = false;
        YesNoDialog::show2BtnsDiaLog(_lang("E100085").c_str(),
                                     CCCallFunc::create([this](){
            this->m_bShowConfirmPanel = true;
        }),
                                     CCCallFuncO::create(this, callfuncO_selector(LoadingScene::onGoToHelpShift), nullptr),
                                     _lang("101274").c_str(),
                                     _lang("101204").c_str());
    }
}

void LoadingScene::setLoadingTips(){
    int level = CCUserDefault::sharedUserDefault()->getIntegerForKey(FUN_BUILD_MAIN_LEVEL);
    if(level<=0){
        level = 1;
    }
    auto tipsDict = LocalTextController::shared()->getGroupByKey("loadingTips");
    if(!tipsDict){
        return;
    }
    
    string loadingTip;
    m_delayTime = 2;
    m_tips.clear();
    m_tipsCache.clear();
    CCDictElement *pObj = nullptr;
    CCDICT_FOREACH(tipsDict, pObj) {
        auto infoDict = _dict(pObj->getObject());
        auto levelRange = string(infoDict->valueForKey("level_range")->getCString());
        m_delayTime = infoDict->valueForKey("delay_time")->intValue();
        if(m_delayTime == 0){m_delayTime = 2;}
        auto id = string(infoDict->valueForKey("id")->getCString());
        auto description = string(infoDict->valueForKey("description")->getCString());
        
        vector<string> levels;
        CCCommonUtils::splitString(levelRange, ";", levels);
        if( levels.size()<2 )
            continue;
        if (level < atoi(levels[0].c_str()) || level > atoi(levels[1].c_str())) {
            continue;
        }
        CCCommonUtils::splitString(description, ";", m_tips);
        CCCommonUtils::splitString(description, ";", m_tipsCache);
    }
    
    srand(time(nullptr));
    auto index = 0;
    this->runAction(RepeatForever::create(Sequence::create(CCCallFunc::create([&](){
        if(m_tips.size()>0)
        {
            auto index = rand()%m_tips.size();
            m_loadingTips->setString(_lang(m_tips[index].c_str()).c_str());
            m_tips.erase(m_tips.begin()+index);
            if(m_tips.size() == 0){m_tips = m_tipsCache;}
        }
    }),DelayTime::create(m_delayTime), nullptr)));
}

void LoadingScene::doLoginInit(float t)
{
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "doLoginInit");
    if (!GlobalData::shared()->isInitFlag && !GlobalData::shared()->isInDataParsing)
    {
        GlobalData::shared()->loadingRecordTime = GlobalData::shared()->getWorldTime();
        CCCommonUtils::recordStepForLoading("3",0,"loading");
        CCLOG("loadingRecord_3");
        
        GameController::getInstance()->setLoadingLog("LoadingScene", "doLoginInit-false");
        InitCommand* cmd=new InitCommand();
        cmd->sendAndRelease();
    }
    else
    {
        unschedule(schedule_selector(LoadingScene::doLoginInit));
    }
}

void LoadingScene::doLoginantiAddiction(CCObject* p){
    unschedule(schedule_selector(LoadingScene::doLoginInit));
    ExchangeControll::getInstance()->pushAddictionView(8);
}

void LoadingScene::doLoginInitError(CCObject* p){
    CCLOG("LoadingScene::doLoginInitError %.2f", m_loadingTotalTime);
    unschedule(schedule_selector(LoadingScene::doLoginInit));
    //同时具有确定/反馈按钮   确定->取消当前面板   反馈->跳转到helpshift
    if (m_bShowConfirmPanel){
        m_bShowConfirmPanel = false;
        YesNoDialog::show2BtnsDiaLog(_lang("114141").c_str(),
                                     CallFunc::create([this](){
            this->m_bShowConfirmPanel = true;
        }),
                                     CCCallFuncO::create(this, callfuncO_selector(LoadingScene::onGoToHelpShift), nullptr),
                                     _lang("101274").c_str(),
                                     _lang("101204").c_str());
    }
    
    checkNetStep3Error(nullptr);
}

void LoadingScene::doXMLParserInit(CCObject* p){
    if (GlobalData::shared()->isForceDownloadXml) {
        GlobalData::shared()->xmlParseCheckNum += 1;
        //等于2意味着 xml初始化也完成了 然后pushinit的数据也缓存下来了
        if (GlobalData::shared()->xmlParseCheckNum == 2) {
            if (GlobalData::shared()->isINIInitFlag&&GlobalData::shared()->isReceivePushInitDataFlag) {
                GlobalData::shared()->isForceDownloadXml = false;
                PushInit::handleResponse(GlobalData::shared()->pushInitDataCache);
                GlobalData::shared()->pushInitDataCache = nullptr;
            }
        }
        else{
            CCLOG("doXMLParserInit error !");
        }
    }
}



void LoadingScene::doLogin(CCObject* p)
{
#if COCOS2D_DEBUG > 0
    
    Director::getInstance()->getScheduler()->unschedule("schedule_loadingbar_progress",m_tempLoadingNode);
    Director::getInstance()->getScheduler()->schedule([this](float dt) {
        onLoadingProgressNew(dt);
    }, m_tempLoadingNode, 0.0f, false, "schedule_loadingbar_progress");
#endif
    CCLOG("LoadingScene::doLogin %.2f", m_loadingTotalTime);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "doLogin");
    
    // set fabric login user
    std::string userId;
    userId = CCCommonUtils::getStringWithEncBySharedUser(GAME_UID);
    
    CrashController::setUser(userId.c_str());
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    CrashReport::setUserId(userId.c_str());
#endif
    
    sendCmdLogin();
}

void LoadingScene::sendCmdLogin()
{
    CCLOG("-----------------------------");
    std::string pushType = cocos2d::extension::CCDevice::getPushTypeData();
    CCLOG("xzz sendCmdLogin::pushType %s ", pushType.c_str());
    if (pushType != "") {
        string _deviceId = cocos2d::extension::CCDevice::getDeviceUid();
        string _gameUid = CCCommonUtils::getStringWithEncBySharedUser(GAME_UID);
        CCCommonUtils::recordPushNotify(pushType,"",_gameUid,_deviceId);//添加push的打点
        cocos2d::extension::CCDevice::setPushTypeData("");
    }
    
    CCCommonUtils::recordStepForLoading("5", 0,"",1);
    CCLOG("LoadingScene::sendCmdLogin %.2f", m_loadingTotalTime);
    // password retry count reset
    GlobalData::shared()->isLoginFlag = true;
    NetController::shared()->clearRequestQueue(true);
    if(loginCmd) {
        loginCmd->setFailCallback(nullptr);
        loginCmd = nullptr;
    }
    LoginCommand* cmd=new LoginCommand();
    cmd->setGPID();
    if(needAccountInfo)
        cmd->setAccountInfo();
    cmd->setDefaultUserName();
    cmd->setFailCallback(CCCallFuncO::create(this, callfuncO_selector(LoadingScene::onConnectionLost), nullptr));
    loginCmd = cmd;
    cmd->sendAndRelease();
}

void LoadingScene::onLoginTimeout(float t)
{
    CCCommonUtils::recordStepForLoading("7", 0,"",1);
    CCLOG("LoadingScene::onLoginTimeout %.2f", m_loadingTotalTime);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "onLoginTimeout");
    unschedule(schedule_selector(LoadingScene::onLoginTimeout));
    CCHttpRequest* request = new CCHttpRequest();
    CCString* url;
    string _uuid = cocos2d::extension::CCDevice::getDeviceUid();
    string _platformUID = GlobalData::shared()->platformUID;
    string _Country = GlobalData::shared()->fromCountry;
    string _gameUid = CCCommonUtils::getStringWithEncBySharedUser(GAME_UID);
    string _lang = LocalTextController::shared()->getLanguageFileName();
    string _serverId = CCCommonUtils::getServerIdBySharedUser();
    string _serverIp = CCCommonUtils::getStringWithEncBySharedUser(ACCOUNT_IP);
    
#if COCOS2D_DEBUG == 1 || COCOS2D_BETA == 1
    url = CCString::createWithFormat("http://%s:%d/probe.php?uuid=%s&loginFlag=%d&country=%s&gameuid=%s&lang=%s&serverId=%s&serverIp=%s",CCTypeDefinition::getServerIP(),CCTypeDefinition::getWebServerConfigPort(),_uuid.c_str(),1,_Country.c_str(),_gameUid.c_str(),_lang.c_str(),_serverId.c_str(),_serverIp.c_str());
#else
    if(GlobalData::shared()->isMiddleEast()){
        url = CCString::create("http://app1.im.medrickgames.com:80");
    }else{
        url = CCString::create("https://gslaz.im30app.com/");
    }
    
    url->appendWithFormat("/gameservice/probe.php?uuid=%s&loginFlag=%d&country=%s&gameuid=%s&lang=%s&serverId=%s&serverIp=%s",_uuid.c_str(),1,_Country.c_str(),_gameUid.c_str(),_lang.c_str(),_serverId.c_str(),_serverIp.c_str());
#endif
    CCLOG("probe URL: %s",url->getCString());
    
    request->setUrl(url->getCString());
    request->setRequestType(CCHttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(LoadingScene::onGetServerStatus));
    request->setTag("get_server_status");
    CCHttpClient::getInstance()->setTimeoutForConnect(10);
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void LoadingScene::onGetServerStatus(CCHttpClient* client, CCHttpResponse* response)
{
    //{"code":0,"message":"OK.","timelist":0}
    CCLOG("LoadingScene::onGetServerStatus %.2f", m_loadingTotalTime);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "onGetServerStatus");
    if (!response)
    {
        checkNetStep3Error(nullptr);
        getMainServerStatus();
        return;
    }
    
    auto code = response->getResponseCode();
    CCLOG("response code: %d", code);
    if (!response->isSucceed())
    {
        CCLOG("response failed!\nerror buffer: %s", response->getErrorBuffer());
        checkNetStep3Error(nullptr);
        getMainServerStatus();
        return;
    }
    std::vector<char>* iter = response->getResponseData();
    std::string serverInfo(iter->begin(),iter->end());
    Json *c = Json_create(serverInfo.c_str());
    if(!c){
        checkNetStep3Error(nullptr);
        getMainServerStatus();
        return;
    }
    int _code =Json_getInt(c,"code",0);
    if (_code != 0) {
        CCCommonUtils::recordStepForLoading("8", 0,"",1);
        std::string _message= Json_getString(c, "message", "");
        PopupViewController::getInstance()->addPopupView(AnnouncementView::create(_message));
        checkNetStep3Error(nullptr);
        getMainServerStatus();
        CCSafeNotificationCenter::sharedNotificationCenter()->postNotification("server_offline", CCBool::create(false));
    }
    Json_dispose(c);
}

//获取机房状态
void LoadingScene::getMainServerStatus()
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("https://speedtest.dal01.softlayer.com:8080/");
    request->setResponseCallback(this, httpresponse_selector(LoadingScene::onGetMainServerStatus));
    request->setTag("get_main_server_status");
    CCHttpClient::getInstance()->setTimeoutForConnect(30);
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void LoadingScene::onGetMainServerStatus(CCHttpClient* client, CCHttpResponse* response)
{
    if (!response)
    {
        checkNetStep3Error(nullptr);
        return;
    }
    
    auto code = response->getResponseCode();
    CCLOG("response code: %d", code);
    if (!response->isSucceed())
    {
        checkNetStep3Error(nullptr);
        return;
    }
}

bool LoadingScene::showServiceTerms(){
    bool showServiceTerms = false;
    if (GlobalData::shared()->analyticID == "onestore"){
        showServiceTerms = CCUserDefault::sharedUserDefault()->getStringForKey("service_terms_check","") == "";
    }
    return showServiceTerms;
}

bool LoadingScene::waitingForLogin(){
    if ((GlobalData::shared()->analyticID == "360"
         || GlobalData::shared()->is3rdAccountLogin())
        && GlobalData::shared()->platformUID == "") {
        return true;
    }
    return false;
}

//根据不同情况选择登录方式
void LoadingScene::selectLogin(float t){
    CCLOG("LoadingScene::selectLogin %.2f", m_loadingTotalTime);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "selectLogin");
    //根据平台判断是否需要先登录平台账号
    cocos2d::log("platformUID->%s",GlobalData::shared()->platformUID.c_str());
    bool loadingWait = waitingForLogin();
    //服务条款
    bool serviceTerms = showServiceTerms();
    if (loadingWait || serviceTerms){
        CCLOG("select login wait");
        if (!m_platformLoginFlag) {
            CCLOG("select login strat schedule");
            m_platformLoginFlag = true;
            schedule(schedule_selector(LoadingScene::selectLogin), 0.5f);
            if(serviceTerms){
                vector<std::string> serviceTermsStr = AppLibHelper::getServiceTerms(1);
                vector<std::string> personalTermsStr = AppLibHelper::getServiceTerms(2);
                PopupViewController::getInstance()->addPopupView(KoreaPermitPopUPView::create("", "", serviceTermsStr, "", personalTermsStr));
            }
        }
        //部分渠道无法监听登录取消时间，由java层判定是否拉起登录界面
        if(loadingWait){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            GamePublisher::doLogin();
#endif
        }
        return;
    }
    else if (m_platformLoginFlag)
    {
        m_platformLoginFlag = false;
        CCLOG("select login end schedule");
        unschedule(schedule_selector(LoadingScene::selectLogin));
    }
    // start Loading GA Timing
    GATrackingController::getInstance()->startTiming("System", "Loading", "LoadingTime");
    
    //1.判断本地缓存
    //读取本地缓存的密文 如果没有就强制写入 如果本地没有缓存就有getserverlist
    string gameUID = CCCommonUtils::getStringWithEncBySharedUser(GAME_UID);
    string ip = CCCommonUtils::getStringWithEncBySharedUser(ACCOUNT_IP);
    string zone = CCCommonUtils::getStringWithEncBySharedUser(ACCOUNT_ZONE);
    int port = CCUserDefault::sharedUserDefault()->getIntegerForKey(ACCOUNT_PORT);
    string portEnc = CCUserDefault::sharedUserDefault()->getStringForKeyWithEnc(ACCOUNT_PORT);
    string _uuid = CCUserDefault::sharedUserDefault()->getStringForKey(ACCOUNT_UUID,"");
    
    if(gameUID == "" && _uuid == "")
    {
        cocos2d::log("qq sendCmdGetServerList");
        //2.根据URL请求，选择登录方式
        sendCmdGetServerList(nullptr);
    }
    else
    {
        CCSafeNotificationCenter::sharedNotificationCenter()->postNotification(MSG_GameStart);
    }
}

void LoadingScene::onRelogin(CCObject* p)
{
    CCLOG("LoadingScene::onRelogin %.2f", m_loadingTotalTime);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "onRelogin");
    selectLogin(0.0);
}

void LoadingScene::sendCmdGetServerList(CCObject* p)
{
    string dbid;
    CCString* temp = dynamic_cast<CCString*>(p);
    if( temp == nullptr) {
        if(CCUserDefault::sharedUserDefault()->getBoolForKey("dbid_switch",true)) {
            IFUserRecord::queryDBID([this](string dbid) {
                sendCmdGetServerList(CCString::create(dbid));
            });
            cocos2d::log("qq sendCmdGetServerList_1");
            return;
        }
    }
    else {
        dbid = temp->getCString();
    }

    m_bShowConfirmPanel = true;
    CCCommonUtils::recordStepForLoading("4", 0,"",1);
    CCLOG("LoadingScene::sendCmdGetServerList %.2f", m_loadingTotalTime);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "sendCmdGetServerList");
    
    CCHttpRequest* request = new CCHttpRequest();
    CCString* url;
    string _uuid;
    if(m_loginUUID == ""){
        _uuid = cocos2d::extension::CCDevice::getDeviceUid();
        cocos2d::log("qq sendCmdGetServerList_m_loginUUID %s",_uuid.c_str());
    }else{
        _uuid = m_loginUUID;
        cocos2d::log("qq sendCmdGetServerList_m_loginUUID——2");
    }
    string _olduuid;
    string _accountInfo;
    auto currentTime = time(nullptr);
    std::string timeStr = CC_ITOA(double(currentTime));
    std::string md5Str;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _accountInfo = cocos2d::extension::CCDevice::getAllAccountInfo();
    _olduuid = _uuid;
    
#else
    
    _olduuid = _uuid;
    
#endif
    CCLOG("Account Info Get %s", _accountInfo.c_str());
    if(_accountInfo != "")
    {
        m_accountInfo = _accountInfo;
        _accountInfo = formatAccList(_accountInfo);     //format
        _accountInfo = cocos2d::extension::CCDevice::base64Encode(_accountInfo);    //encode
    }
    
    //MD5 signature
    currentTime = time(nullptr);
    timeStr = CC_ITOA(double(currentTime));
    if(_olduuid != "")
        _uuid = _olduuid;
    std::string key = _uuid + timeStr + _accountInfo+ "@Q0tASRFOTV9ESUIdHhUYbEtBTUVAAk9DQQ9PQ0";
    if(GlobalData::shared()->is3rdAccountLogin())
    {
         cocos2d::log("qq sendCmdGetServerList_2");
        key = _uuid + timeStr + ""+ "@Q0tASRFOTV9ESUIdHhUYbEtBTUVAAk9DQQ9PQ0";
    }
    MD5 md5(key);
    md5Str = md5.toString();
    std::string gpId = GlobalData::shared()->GPPlayerID;
    CCLOG("Get Old Uuid %s, accountInfo, %s", _olduuid.c_str(), _accountInfo.c_str());
    
    if(GlobalData::shared()->is3rdAccountLogin())
    {
         cocos2d::log("qq sendCmdGetServerList_3");
        _uuid = _uuid + "&accList=" + "" + "&gpid=" + "" + "&type=1&ver=2";
    }
    else
    {
        if(_olduuid != "")
            _uuid = _uuid + "&accList=" + _accountInfo + "&gpid=" + gpId + "&type=1&ver=2";
        else
            _uuid = _uuid + "&accList=" + _accountInfo + "&gpid=" + gpId + "&type=2&ver=2";
    }
    
    string _platformUID = GlobalData::shared()->platformUID;
    CCLOG("xzz platformUID = %s",GlobalData::shared()->platformUID.c_str());
    string _Country = GlobalData::shared()->fromCountry;
    string _PublishRegion = cocos2d::extension::CCDevice::getPublishRegion();
#if COCOS2D_DEBUG == 1 || COCOS2D_BETA == 1
    url = CCString::createWithFormat("http://%s:%d", CCTypeDefinition::getServerListIP(), CCTypeDefinition::getWebServerConfigPort());
#else
    if(GlobalData::shared()->isMiddleEast()){
        url = CCString::createWithFormat("http://app1.im.medrickgames.com:80");
    }else{
        url = CCString::createWithFormat("https://%s", CCTypeDefinition::getServerListIP());
        if (CCCommonUtils::isChina()){
            if (m_loginTimes % 2 == 1)
                url = CCString::createWithFormat("https://%s", "gslaz.im30app.com");
            else
                url = CCString::createWithFormat("https://%s", "ex1.im30app.com");
        }
    }
#endif
    if (_platformUID != "") {
        if (GlobalData::shared()->platformChannel == "google") {
            _PublishRegion = GlobalData::shared()->platformChannel;
        }
        string _referrer = GlobalData::shared()->referrer;
        if(GlobalData::shared()->is3rdAccountLogin())
        {
             cocos2d::log("qq sendCmdGetServerList_4");
            url->appendWithFormat("/gameservice/getserverlist.php?uuid=%s&loginFlag=%d&dlch=%s&pfId=%s&pf=%s&country=%s&t=%s&p2=%s&a2=%s&sig=%s", _uuid.c_str(),1,_PublishRegion.c_str(),_platformUID.c_str(),_PublishRegion.c_str(),_Country.c_str(), timeStr.c_str(), _PublishRegion.c_str(), _referrer.c_str(), md5Str.c_str());
        }
        else
        {
           url->appendWithFormat("/gameservice/getserverlist.php?uuid=%s&loginFlag=%d&dlch=%s&pfId=%s&pf=%s&country=%s&t=%s&p2=%s&a2=%s&sig=%s", _uuid.c_str(),1,_PublishRegion.c_str(),_platformUID.c_str(),_PublishRegion.c_str(),_Country.c_str(), timeStr.c_str(), _PublishRegion.c_str(), _referrer.c_str(), md5Str.c_str());
        }
    }
    else
    {
        url->appendWithFormat("/gameservice/getserverlist.php?uuid=%s&loginFlag=%d&dlch=%s&country=%s&t=%s&sig=%s",_uuid.c_str(),1,_PublishRegion.c_str(),_Country.c_str(), timeStr.c_str(), md5Str.c_str());
    }
    
    if(dbid != "" ) {
        url->appendWithFormat("&dbid=%s", dbid.c_str());
    }
    
    string gtype;
    string gameUID;
    gameUID = CCUserDefault::sharedUserDefault()->getStringForKeyWithEnc("NEW_GAMEUID");
    if(GlobalData::shared()->is3rdAccountLogin())
    {
        cocos2d::log("qq sendCmdGetServerList_3");
        gameUID="";
    }
    
    if (!gameUID.empty()){
        gtype = "2";
    } else {
        gameUID = CCCommonUtils::getStringWithEncBySharedUser(GAME_UID);
    }
    if (!gameUID.empty()) {
        string temp = url->getCString();
        url->initWithFormat("%s&gameuid=%s", temp.c_str(), gameUID.c_str());
    }
    if (!gtype.empty()) {
        string temp = url->getCString();
        url->initWithFormat("%s&gtype=%s", temp.c_str(), gtype.c_str());
    }
#if COCOS2D_DEBUG > 0
    if (!CCTypeDefinition::m_serverZone.empty()){
        string temp = url->getCString();
        int len = temp.find(CCTypeDefinition::getServerListIP());
        string tmp("10.0.0.16");
        temp.replace(len, strlen(CCTypeDefinition::getServerListIP()), tmp);
        url->initWithFormat("%s&forceSid=%s", temp.c_str(), CCTypeDefinition::m_serverZone.substr(3).c_str());
    }
#endif
    cocos2d::log("qq sendCmdGetServerList url = %s", url->getCString());
    CCCommonUtils::AZLog("xzz sendCmdGetServerList url = %s", url->getCString() );
    request->setUrl(url->getCString());
    request->setRequestType(CCHttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(LoadingScene::onGetServerList));
    request->setTag("get_server_list");
    CCHttpClient::getInstance()->setTimeoutForConnect(30);
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    if( IsFLOG() ) {
        FLOG("LOADING getserverlist %s", url->getCString());
    }
    if( IsLoadingInf() ) {
        prepareLoadingInfo("LOADING getserverlist %s", url->getCString());
    }
}

void LoadingScene::onGetServerList(CCHttpClient* client, CCHttpResponse* response)
{
    bool _errorRep = false;
    //用来做重新getserverlist
    if (!response->isSucceed()){
        _errorRep = true;
        g_gsl = "FAIL";
    }else{
//        std::vector<char>* iter = response->getResponseData();
//        std::string serverInfo(iter->begin(),iter->end());
//        if (serverInfo.compare("") == 0){
//            _errorRep = true;
//        }
    }
    if (_errorRep == true){
        m_loginTimes++;
        g_gsl = "EMT";
        scheduleOnce([this](float){
            sendCmdGetServerList(nullptr);
        }, 0.5, "retryGetServerList");
        return;
    }
    if( IsFLOG) {
        FLOG("LOADING getserverlist rece");
    }
     cocos2d::log("qq onGetServerList——1");
    bool bGameUid = false;
    //连接多少失败时，使用gameuid得到数据不对，还走以前逻辑
    if (NetController::shared()->isReachToConnectTimes()){
        bGameUid = true;
        if( IsFLOG()) {
            FLOG("NET Loading GetServerList Connect Time %d", CONNECT_TIMES+1);
        }
        CCUserDefault::sharedUserDefault()->setIntegerForKey("CONNECT_SEND", 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("CONNECT_TIMES", CONNECT_TIMES+1);
        CCUserDefault::sharedUserDefault()->flush();
    }
    CCLOG("LoadingScene::onGetServerList %.2f", m_loadingTotalTime);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "onGetServerList");
    string theUuid = cocos2d::extension::CCDevice::getDeviceUid();
    if (!response)
    {
        if( IsFLOG) {
            FLOG("LOADING getserverlist rece responese=null");
        }
        
        if (bGameUid) {
            return;
        }
        cocos2d::extension::CCDevice::sendTraceLogToHelpshift("loading", "call getserverlist.php fail[0]");
        cocos2d::extension::CCDevice::testNetworkAndSendToHelpshift(theUuid, CCTypeDefinition::getServerListIP());
         cocos2d::log("qq onGetServerList——2");
        return;
    }
    
    cocos2d::log("qq onGetServerList——3");
    
    auto code = response->getResponseCode();
    CCLOG("response code: %d", code);
    if (!response->isSucceed())
    {
        if( IsFLOG) {
            FLOG("LOADING getserverlist failed %d", code);
        }
        if (bGameUid) {
            return;
        }
        cocos2d::extension::CCDevice::sendTraceLogToHelpshift("loading", "call getserverlist.php fail[1]");
        cocos2d::extension::CCDevice::testNetworkAndSendToHelpshift(theUuid, CCTypeDefinition::getServerListIP());
        CCLOG("response failed!\nerror buffer: %s", response->getErrorBuffer());
        //        LocalController::shared()->init();
        g_http_status = 1;
        setNetCurrentStatus(nullptr);
        //同时具有确定/反馈按钮   确定->重新发送getserverlist   反馈->跳转到helpshift
        if (m_bShowConfirmPanel){
            m_bShowConfirmPanel = false;
            if( !AnnouncementView::isShowing()) {
                YesNoDialog::show2BtnsDiaLog(_lang("E100048").c_str(),
                                             CCCallFuncO::create(this, callfuncO_selector(LoadingScene::sendCmdGetServerList),nullptr),
                                             CCCallFuncO::create(this, callfuncO_selector(LoadingScene::onGoToHelpShift), nullptr),
                                             _lang("101274").c_str(),
                                             _lang("101204").c_str());
            }
        }
        return;
    }
    std::vector<char>* iter = response->getResponseData();
    std::string serverInfo(iter->begin(),iter->end());
    if(serverInfo == "")
    {
        if( IsFLOG) {
            FLOG("LOADING getserverlist failed serverinfo empty");
        }
        
        if (bGameUid) {
            return;
        }
        cocos2d::extension::CCDevice::sendTraceLogToHelpshift("loading", "call getserverlist.php fail[2]");
        CCLOG("response data is null!");
        g_http_status = 2;
        setNetCurrentStatus(nullptr);
        //同时具有确定/反馈按钮   确定->重新发送getserverlist   反馈->跳转到helpshift
        if (m_bShowConfirmPanel){
            m_bShowConfirmPanel = false;
            if( !AnnouncementView::isShowing()) {
                YesNoDialog::show2BtnsDiaLog(_lang("E100048").c_str(),
                                         CCCallFuncO::create(this, callfuncO_selector(LoadingScene::sendCmdGetServerList),nullptr),
                                         CCCallFuncO::create(this, callfuncO_selector(LoadingScene::onGoToHelpShift), nullptr),
                                         _lang("101274").c_str(),
                                         _lang("101204").c_str());
            }
        }
        
        return;
    }
    
    if(IsFLOG()) {
        FLOG("LOADING getserverlist content: %s", serverInfo.c_str());
    }
    if( IsLoadingInf() ) {
        prepareLoadingInfo("LOADING getserverlist content: %s", serverInfo.c_str());
    }
    
    Json *c = Json_create(serverInfo.c_str());
    if(!c){
        g_http_status = 7;
        setNetCurrentStatus(nullptr);
        if (bGameUid) {
            if( IsFLOG()) {
                FLOG("NET Loading GetServerList Connect Time %d", CONNECT_TIMES+1);
            }
            CCUserDefault::sharedUserDefault()->setIntegerForKey("CONNECT_TIMES", CONNECT_TIMES+1);
            CCUserDefault::sharedUserDefault()->flush();
        }
        if( IsFLOG) {
            FLOG("LOADING getserverlist failed serverinfo json error");
        }
        return;
    }
    Json *serverList=Json_getItem(c,"serverList");
    if(!serverList){
        g_http_status = 8;
        setNetCurrentStatus(nullptr);
        if (bGameUid) {
            if( IsFLOG()) {
                FLOG("NET Loading GetServerList Connect Time %d", CONNECT_TIMES+1);
            }
            CCUserDefault::sharedUserDefault()->setIntegerForKey("CONNECT_TIMES", CONNECT_TIMES+1);
            CCUserDefault::sharedUserDefault()->flush();
        }
        if( IsFLOG()) {
            FLOG("LOADING getserverlist failed serverinfo serverList error");
        }
        return;
    }
    int country=Json_getInt(c,"country",0);
    //get serverInfo
    Json *c2 = Json_getItemAt(serverList, 0);
    if(!c2){
        if( IsFLOG()) {
            FLOG("NET Loading GetServerList Connect Time %d", CONNECT_TIMES+1);
        }
        if( IsFLOG()) {
            FLOG("LOADING getserverlist failed serverinfo serverList 0 error");
        }
        if (bGameUid) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("CONNECT_TIMES", CONNECT_TIMES+1);
            CCUserDefault::sharedUserDefault()->flush();
        }
        return;
    }
    
    string id = Json_getString(c2,"id","-1");
    string port = Json_getString(c2, "port","-1");
    string zone = Json_getString(c2, "zone","-1");
    string sid = zone.substr(3);    //服id跟后台逻辑统一    COKxx
    //    string id = Json_getString(c2,"id","-1");
    string ip = Json_getString(c2, "ip","-1");
    string gameUid = Json_getString(c2, "gameUid", "");
#if COCOS2D_DEBUG > 0
    gameUid="";
#endif
    string _uuid = Json_getString(c2, "uuid", "");
    string serverStop = Json_getString(c2, "stop", "");
    string serverState = Json_getString(c2, "state", "");
    
    string targetInfo = Json_getString(c, "target", "");
    
    Json_dispose(c);
    
    if(serverStop == "1" || serverState == "999") {
        if( IsFLOG) {
            FLOG("LOADING getserverlist failed serverStop");
        }
        // 服务器维护中
        YesNoDialog::showVariableTitle(_lang("E100069").c_str(),
                                       CCCallFuncO::create(GameController::getInstance(), callfuncO_selector(GameController::quitGame), nullptr),
                                       _lang("confirm").c_str(),true);
        
        CCSafeNotificationCenter::sharedNotificationCenter()->postNotification("server_offline", CCBool::create(false));
        
        return;
    }
    
    CCCommonUtils::setStringWithEncBySharedUser(GAME_UID, gameUid);
    GlobalData::shared()->loginServerInfo.recommandCountry = country;
    CCUserDefault::sharedUserDefault()->setStringForKey(ACCOUNT_UUID, _uuid);
    CCCommonUtils::setStringWithEncBySharedUser(ACCOUNT_IP, ip);
    CCCommonUtils::setStringWithEncBySharedUser(ACCOUNT_ZONE, zone);
    
    cocos2d::log("qq onGetServerList——4 %s",zone.c_str());
    CCUserDefault::sharedUserDefault()->setIntegerForKey(ACCOUNT_PORT,atoi(port.c_str()));
    
    CCUserDefault::sharedUserDefault()->setStringForKeyWithEnc(ACCOUNT_PORT, port.c_str());
    CCUserDefault::sharedUserDefault()->flush();
    
    needAccountInfo = false;
    std::string oldAccountInfo = CCUserDefault::sharedUserDefault()->getStringForKey(ACCOUNT_INFO, "");
    std::string loadingTmpGPUid = CCUserDefault::sharedUserDefault()->getStringForKey("loadingGPUid", "-1");
    //    oldAccountInfo = "";
    if(targetInfo == "")
    {
        if (loadingTmpGPUid != "-1") {
            CCUserDefault::sharedUserDefault()->setStringForKey(ACCOUNT_INFO, loadingTmpGPUid);
            CCLOG("targetInfo Info Bind, %s", loadingTmpGPUid.c_str());
        }
        else{
            if(oldAccountInfo == ""){
                needAccountInfo = true;
                std::string selectAccount = getAccountFromAccountInfo();
                CCUserDefault::sharedUserDefault()->setStringForKey(ACCOUNT_INFO, selectAccount);
                CCLOG("Need Accoune Info Bind, %s", selectAccount.c_str());
            }
        }
    }
    else
    {
        targetInfo = formatAccList(cocos2d::extension::CCDevice::base64DEcode(targetInfo));
        if(targetInfo != oldAccountInfo)
            CCUserDefault::sharedUserDefault()->setStringForKey(ACCOUNT_INFO, targetInfo);
    }
    
    CCUserDefault::sharedUserDefault()->flush();
    
    NetController::shared()->setIp(ip);
    NetController::shared()->setPort(atoi(port.c_str()));
    NetController::shared()->setZone(zone);
    NetController::shared()->setServerId(atoi(sid.c_str()));
    
    if(m_isAiService){
        if( gameUid != "" ) {
            ECServiceCocos2dx::setUserId(CCCommonUtils::getStringWithEncBySharedUser(GAME_UID));
            string server_id = CCCommonUtils::getServerIdBySharedUser();
            ECServiceCocos2dx::setServerId(Value(server_id).asInt());
        }

    }
    string zn = zone;
    string uid = gameUid;
    if( uid.size() > 4) {
        uid.erase(uid.begin() + 4, uid.end());
    }
    else {
        uid = "null";
    }
    if( zn.length() > 3) {
        zn.erase(zn.begin(), zn.begin() + 3);
    }
    g_gsl = "";
    g_gsl.append(sid).append("#").append(uid).append(" ").append(zn);
    
    CCSafeNotificationCenter::sharedNotificationCenter()->postNotification(MSG_GameStart);
    
    if( IsFLOG) {
        FLOG("LOADING getserverlist success %s", gameUid.c_str());
    }
}
void LoadingScene::showLoading(float offsetTime)
{
    //TODO:DEBUG包登录时弹出选择服务器
#if COCOS2D_DEBUG > 0
    this->unscheduleUpdate();
    PopupViewController::getInstance()->addPopupView(ChangeServeView::create(true));
#else
    CCLOG("LoadingScene::showLoading %.2f", m_loadingTotalTime);
    loadingAni(0.0);
    
    selectLogin(0.0);
#endif
}

void LoadingScene::loadContinue(Ref* ref){
    this->scheduleUpdate();
    CCLOG("LoadingScene::showLoading %.2f", m_loadingTotalTime);
    schedule(schedule_selector(LoadingScene::loadingAni));
    
#if COCOS2D_DEBUG > 0
    if (!CCTypeDefinition::m_gameUID.empty()){
        int serverId = atoi(CCTypeDefinition::m_serverZone.substr(3).c_str());
        showLoading(serverId, CCTypeDefinition::m_gameUID);
        return;
    }
#endif
    selectLogin(0.0);
}

void LoadingScene::onLoadingProgressNew(float t)
{
    if (this->getChildByTag(CNSCENE_TAG)){
        return;
    }
    if (LOADING_PROGRESS_FINISH==m_progress) {
        return;
    }
    
    float pro = m_progress * 1.0 / 100;
    string proInfo = CC_ITOA(pro*100);
    // 更新血条
    if (pro >= 1) {
        pro = 1;
    }
    
    float curX = m_barSize.width*pro;
    m_clipNode->setContentSize(CCSizeMake(curX, m_barSize.height+30));
    float ContentX = curX-LOADING_BLOOD_OFFSET > 0 ? curX-LOADING_BLOOD_OFFSET : 0;
    m_barClipNode->setContentSize(CCSizeMake(ContentX, m_barSize.height+30));
    m_blood->setPositionX(curX-30-LOADING_BLOOD_OFFSET);
    m_headParticleNode->setPositionX(m_clipNode->getPositionX()+curX);
    //TODO:调整时间点
    if (m_progress <=88) {
        m_progress += rand_0_1()*1;
    }
    else if(m_progress >96 && m_progress < 99){
        m_progress = 96;
    }
    else{
        m_progress += rand_0_1()*0.1;
    }
}

void LoadingScene::setNetCurrentStatus(CCObject *pObject) {
    if (true) {
        char tmp[100] = {0};
        string tmpIP = g_sfs_serverIP;
        if (tmpIP.length() > 3) {
            
            auto dotPos = tmpIP.find_first_of('.');
            if (dotPos != string::npos) {
                tmpIP.erase(tmpIP.begin() + dotPos, tmpIP.end());
            }
            else {
                tmpIP.erase(tmpIP.begin() + 3, tmpIP.end());
            }
            if(use_kcp) {
                tmpIP.append("K");
            }
            else if(use_snc) {
                tmpIP.append("C");
            }
            if( tmpIP == "mqtt" ) {
                tmpIP = "t";
            }
            else if( tmpIP == "mqttcn" ) {
                tmpIP = "tn";
            }
            
        }
        if( g_http_status > 0 ) {
            sprintf(tmp, "(%d %s %d %d)", g_http_status, tmpIP.c_str(), g_sfs__serverPort, g_sfs_status);
        }
        else {
            sprintf(tmp, "(%s %d %d)", tmpIP.c_str(), g_sfs__serverPort, g_sfs_status);
        }
        
        string uid = CCCommonUtils::getStringWithEncBySharedUser(GAME_UID);
        if( uid.size() > 4) {
            uid.erase(uid.begin() + 4, uid.end());
        }
        string res;
        res.append("S:(").append(uid).append(")");
        res.append(tmp);
        
        if( g_gsl.length() > 0 ) {
            res.append("L:(").append(g_gsl).append(")");
        }
        
        if(g_login_error!="") {
            if( g_login_error_combine.rfind(g_login_error) != g_login_error_combine.size()-g_login_error
               .size()) {
                g_login_error_combine += g_login_error;
            }
            
            res.append("(").append(g_login_error_combine).append(")");
        }

        if( !g_isSuccessUnZip ) {
            char tmp[10] = {0};
            snprintf(tmp, 10, "%d/%d",g_currentNum,g_allNum);
            res.append("(UP:").append(tmp).append(")");
        }
        m_conStatusCode->setString(res);
    }
    
}

void LoadingScene::loadingAni(float t)
{
    SoundController::sharedSound()->playBGMusic(Music_Sfx_logo_loading);
    m_loadPerLabel->setVisible(true);
    m_underBarLabel->setVisible(false);
//    m_netBgNode->setVisible(false);
}

extern pthread_t MAIN_THREAD_ID;
void LoadingScene::loginInitFinsh( CCObject* p ) {
    m_initFinsh = true;
    
    //根据IP查看是否是外网调试
#if COCOS2D_DEBUG > 0
    string hostIP = CCCommonUtils::getStringWithEncBySharedUser(ACCOUNT_IP);
    if (hostIP.empty()) {
        hostIP = CCTypeDefinition::getServerIP();
    }
    if (!hostIP.empty())
    {
        string::size_type idx = hostIP.find("az.im30app.com");
        if(idx != string::npos)
        {
            ChatServiceCocos2dx::notifyExternaletworkebugFrom2dx(true);
        }
    }
#endif
    
    if (this->getChildByTag(CNSCENE_TAG)){
        return;
    }
    // 这句话让血条走到了头
    m_progress = 99;
    if(CCCommonUtils::checkIsOpenByKey("loading_facebook")){
        if(GlobalData::shared()->isBindAcount){
            GlobalData::shared()->showFaceBookUi = false;
        }else{
            GlobalData::shared()->showFaceBookUi = true;
            m_updateFAQTips = false;
        }
    }else{
        GlobalData::shared()->showFaceBookUi = false;
    }

    //不是中国地区才开启
    if(CCCommonUtils::isChina()){
        GlobalData::shared()->showFaceBookUi = false;
    }
    this->scheduleOnce([this](float dt){
        stepLoading(nullptr);
    }, 0.01f, "StepLoading");
}

extern bool g_isSuccessUnZip;

void LoadingScene::localUnzipFinsh( CCObject* p ) {
    if(m_isNetStep3Pass && g_isSuccessUnZip){
        gotoMainScene(0.0f);
    }
}

void LoadingScene::stepLoading(CCObject* p)
{
    CCLOG("LoadingScene::stepLoading %.2f", m_loadingTotalTime);
    
    //服务器数据都正常返回了
    checkNetStep3Ok(nullptr);
    
    //loadingLog统计
    time_t worldTime = GlobalData::shared()->getWorldTime();
    GameController::getInstance()->setLoadingLog("LoadingScene", CCString::createWithFormat("stepLoading:serverTime:%s ",CCCommonUtils::timeStampToDate(worldTime).c_str())->getCString());
    unschedule(schedule_selector(LoadingScene::doLoginInit));
    //提示更新版本
    std::string str;
    GlobalData::shared()->lang = cocos2d::extension::CCDevice::getLanguage();
    GlobalData::shared()->platform = "ios";
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    GlobalData::shared()->platform = "android";
    //根据平台获得提示语
    if(GlobalData::shared()->analyticID == "market_global"){
        str = "GOOGLE";
    }else{
        /**
         tstore
         nstore
         amazon
         cafebazaar
         **/
        str = GlobalData::shared()->analyticID;
    }
#else
#ifdef Channel_91
    str = "91Store";
    GlobalData::shared()->analyticID = "91Store";
#else
    str = "AppStore";
    GlobalData::shared()->analyticID = "AppStore";
    if (cocos2d::extension::CCDevice::isArab()){
        str = "AppStoreAR";
        GlobalData::shared()->analyticID = "AppStoreAR";
    }
#endif
#endif

    // 欧盟
    if (CCCommonUtils::checkIsOpenByKey("GDPR_switch") && GlobalData::shared()->eu_state < GlobalData::EU_STATE_AGREE ){
        CCLOG("GlobalData::shared()->eu_state=%d", GlobalData::shared()->eu_state);
        if (m_bShowConfirmPanel){
            m_bShowConfirmPanel = false;
            PopupViewController::getInstance()->addPopupView(EUReview::create(),false,true,false);

        }

        return;
    }

    // 欧盟CCCommonUtils::checkIsOpenByKey("GDPR_switch") &&
    if ( CCCommonUtils::checkIsOpenByKey("GDPR_switch_high") && GlobalData::shared()->eu_state < GlobalData::EU_STATE_AGREE ){
        CCLOG("GlobalData::shared()->eu_state=%d", GlobalData::shared()->eu_state);
        if (m_bShowConfirmPanel){
            m_bShowConfirmPanel = false;
            PopupViewController::getInstance()->addPopupView(EUSelectCountry::create(),false,true,false);

        }

        return;
    }

    if ( CCCommonUtils::checkIsOpenByKey("GDPR_switch_low") && GlobalData::shared()->eu_state < GlobalData::EU_STATE_AGREE ){
        CCLOG("GlobalData::shared()->eu_state=%d", GlobalData::shared()->eu_state);
        if (m_bShowConfirmPanel){
            m_bShowConfirmPanel = false;
            PopupViewController::getInstance()->addPopupView(EUReviewNew::create(),false,true,false);

        }

        return;
    }


#if COCOS2D_DEBUG == 0
    if (GlobalData::shared()->updateType==1)
    {
        if (m_bShowConfirmPanel){
            m_bShowConfirmPanel = false;
            auto _dialog = YesNoDialog::show(CCString::createWithFormat(_lang("77779900").c_str(), str.c_str())->getCString(),
                                             CCCallFuncO::create(this, callfuncO_selector(LoadingScene::forceUpdate), nullptr),0,
                                             true,
                                             CCCallFuncO::create(this, callfuncO_selector(LoadingScene::offerUpdate), nullptr));
            _dialog->showCancelButton();
            _dialog->setCloseCallYes(true);
        }
        
        return;
    }
    if (GlobalData::shared()->updateType==2)
    {
        CCCommonUtils::recordStepForLoading("10", 0,"",1);
        if (m_bShowConfirmPanel){
            m_bShowConfirmPanel = false;
            auto _dialog = YesNoDialog::showVariableTitle(CCString::createWithFormat(_lang("77779900").c_str(), str.c_str())->getCString(),CCCallFuncO::create(this, callfuncO_selector(LoadingScene::forceUpdate),nullptr), _lang("confirm").c_str(),true);
            
            _dialog->setCloseCallYes(true);
        }
        
        return;
    }
#endif
    
    
    if(GlobalData::shared()->showFaceBookUi && CCCommonUtils::checkIsOpenByKey("loading_facebook")){
        showFaceBookUI(nullptr);
        return;
    }else{
        hideFaceBookUI(nullptr);
    }
    
    if( !GlobalData::shared()->lordInfo.agreeUserAgreementFlag) {
        // popup user agreement
        
        string currentLang;
        currentLang.append(";").append(LocalTextController::shared()->getLanguageFileNameBasedOnUserSystem()).append(";");
        string agreement_push_val;
        agreement_push_val.append(";").append(GlobalData::shared()->agreement_push).append(";");
        
        bool isOpen = false;
        if( agreement_push_val.find("all") != string::npos ) {
            isOpen = true;
        }
        else if (agreement_push_val.find(currentLang) != string::npos) {
            isOpen = true;
        }
        if(isOpen) {
            auto uap = UserAgreementPopup::create();
            uap->setYesCallback(CCCallFuncO::create(this, callfuncO_selector(LoadingScene::userAgree),nullptr));
            PopupViewController::getInstance()->addPopupView(uap);
            return;
        }

    }
    //loadings公告
    if(GlobalData::shared()->lordInfo.loadingNoticeFlag) {
        if(GlobalData::shared()->m_loadingNotice.size() > 0){
            auto uap = LoadingNoticePopView::create();
            uap->setYesCallback(CCCallFuncO::create(this, callfuncO_selector(LoadingScene::closeNotice),nullptr));
            PopupViewController::getInstance()->addPopupView(uap);
            return;
        }
    }
   
    /*if(GlobalData::shared()->lordInfo.loadingNoticeFlag) {
        //loadings更新公告
        //    system_notice
        string  system_noticeId="9080000";
        string _lanuageStr="";
        CCDictionary* _dict = LocalController::shared()->DBXMLManager()->getGroupByKey("system_notice");
        if(_dict)
        {
            CCDictionary* param=dynamic_cast<CCDictionary*>(_dict->objectForKey(system_noticeId.c_str()));//取出内容
            if(param)
            {
                bool isNeedPop = true;
                if(param->objectForKey("time")){
                    int _time = param->valueForKey("time")->intValue();
                    if(_time == 0){
                        isNeedPop=false;
                    }else{
                        int _rTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("notice_time",0);
                        if(_rTime>0){
                            if(_rTime/100 == CCCommonUtils::getTodayTime()){//是今天
                                if(_rTime % CCCommonUtils::getTodayTime() >= _time){ //今天第几次
                                    isNeedPop = false;
                                }
                            }
                        }
                    }
                }
                
                if(param->objectForKey("openTime") && param->objectForKey("endTime")){
                    double nowTime = GlobalData::shared()->getWorldTime();
                    double openT = param->valueForKey("openTime")->doubleValue()/1000;
                    double endT = param->valueForKey("endTime")->doubleValue()/1000;
                    if(nowTime < openT || nowTime > endT){
                        isNeedPop = false;
                    }
                }
                
                string lang = CCCommonUtils::getLanguage();
                string country = GlobalData::shared()->fromCountry;
                
                CCString *PStr=nullptr;
                string _lang;
                string _cou;
                PStr=dynamic_cast<CCString*>(param->objectForKey("language"));
                if(PStr)
                {
                    _lanuageStr=PStr->getCString();
                }
                PStr=dynamic_cast<CCString*>(param->objectForKey("lang"));
                if(PStr)
                {
                    _lang=PStr->getCString();
                }
                
                PStr=dynamic_cast<CCString*>(param->objectForKey("country"));
                if(PStr)
                {
                    _cou=PStr->getCString();
                }
                string::size_type _found1 = _lang.find(lang);
                string::size_type _found2 = _cou.find(country);
                if (isNeedPop && (_found1!=string::npos ||_lang=="all") && (_found2!=string::npos || _cou=="all"))
                {
                    auto uap = LoadingNoticePopView::create(_lanuageStr);
                    uap->setYesCallback(CCCallFuncO::create(this, callfuncO_selector(LoadingScene::closeNotice),nullptr));
                    PopupViewController::getInstance()->addPopupView(uap);
                    
                    int _rTime = CCUserDefault::sharedUserDefault()->getIntegerForKey("notice_time",0);
                    if(_rTime == 0){
                        _rTime++;
                        int nT = CCCommonUtils::getTodayTime() * 100;
                        CCUserDefault::sharedUserDefault()->setIntegerForKey("notice_time",nT+_rTime);
                    }else{
                        _rTime++;
                        CCUserDefault::sharedUserDefault()->setIntegerForKey("notice_time",_rTime);
                    }
                    
                    return;
                }
            }
        }
    }*/
    //发送launch打点消息
    CCCommonUtils::recordStepByHttp("4");
    
    if(CCUserDefault::sharedUserDefault()->getBoolForKey(MSG_3DWorld, true)){
        CCCommonUtils::recordStepByHttp("13", "function");
    }

    
    
    
    
    //    this->scheduleOnce([this](float dt){
    if(g_isSuccessUnZip){
        gotoMainScene(0.0f);
    }
    //    }, 0.1f, "gotoMainScene");

}

void LoadingScene::gotoMainScene(float t)
{
    if (GlobalData::shared()->forceStop)
        return;
    Director::getInstance()->getScheduler()->unschedule("schedule_loadingbar_progress",m_tempLoadingNode);
    
    //    CCLOG("LoadingScene::gotoMainScene %.2f", m_loadingTotalTime);
    unschedule(schedule_selector(LoadingScene::loadingAni));
    
    m_progress = 100;
    unschedule(schedule_selector(LoadingScene::onLoadingProgressNew));

    //清除开始新游戏
    CCUserDefault::sharedUserDefault()->setStringForKeyWithEnc("NEW_GAMEUID", "");
    CCUserDefault::sharedUserDefault()->flush();
    
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    double tempstart =(double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
    CCCommonUtils::recordStep("5");
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "gotoMainScene");
    unschedule(schedule_selector(LoadingScene::doLoginInit));
    unschedule(schedule_selector(LoadingScene::gotoMainScene));
    m_barClipNode->setContentSize(m_barSize);
    m_clipNode->setContentSize(m_barSize);
    m_headParticleNode->setPositionX(m_clipNode->getPositionX()+m_barSize.width);

    AppLibHelper::tutorialCompleteAppsflyer(GlobalData::shared()->playerInfo->uid, 3);
    
    if (CCCommonUtils::checkIsOpenByKey("resource_downloading_switch")){
        auto _downType = GlobalData::shared()->m_downloadType;
        int iNeedNum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(_downType);
        if( iNeedNum <= 0 )
        {
            SceneController::getInstance()->addGUI();
        }
    }
    else if (CCCommonUtils::checkIsOpenByKey("battlefield_download_pic")){//竞技场地图下载
        auto _downType = ArenaController::getInstance()->getArenaDownLoadMapType();
        int iNeedNum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(_downType);
        if( iNeedNum <= 0 )
        {
            SceneController::getInstance()->addGUI();
        }
    }
    else{
        if ( !CCCommonUtils::checkIsOpenByKey("ar_guide_switch") && !GlobalData::shared()->show_guide_video )
            SceneController::getInstance()->addGUI();
    }
    
    //3Dtouch 调用的功能
    std::string _shortItemType = GlobalData::shared()->shortItemType;
    bool _is3Dtouch = false;
    if(GlobalData::shared()->shortItem_switch && !(GuideController::share()->isInTutorial() || (GlobalData::shared()->playerInfo->level == 1 && GlobalData::shared()->playerInfo->exp == 0)))
    {
        if (!_shortItemType.compare(shortItemType_chat))
        {
            GlobalData::shared()->isUiInti = false;
            
            UIComponent::getInstance()->showAllianceChat();
            //                CCDirector::sharedDirector()->setVisitFlag(true);
            schedule(schedule_selector(LoadingScene::onEnterMainScene), 0.1);
            return;
        }
        
        if (!_shortItemType.compare(shortItemType_mail))
        {
            GlobalData::shared()->isUiInti = false;
            //                CCDirector::sharedDirector()->setVisitFlag(false);
            UIComponent::getInstance()->showMailUI();
            //                CCDirector::sharedDirector()->setVisitFlag(true);
            schedule(schedule_selector(LoadingScene::onEnterMainScene), 0.1);
            return;
        }
        
        if (!_shortItemType.compare(shortItemType_world))
        {
            _is3Dtouch = true;
            SceneController::getInstance()->addGUI();
            SceneController::getInstance()->gotoScene(SCENE_ID_WORLD);
        }
    }
    
    if(SceneController::getInstance()->showBG){
        SceneController::getInstance()->showBG->release();
        SceneController::getInstance()->showBG = nullptr;
        SceneController::getInstance()->addGUI();
        SceneController::getInstance()->gotoScene(SCENE_ID_WORLD);
        if(SubsidiaryCityController::getInstance()->checkIsShowPutTipsView()){//分城落城提示
            PopupViewController::getInstance()->addPopupView(SubSidiaryCityPutTipsView::create(),false,true,false);
            SubsidiaryCityController::getInstance()->flagShowPutTips = true;
        }
        
    }else if(!_is3Dtouch)
    {
        showMainScene();
    }
    // end Loading GA Timing
    GATrackingController::getInstance()->endTiming("System", "Loading", "LoadingTime");
    //    }
}

void LoadingScene::showMainScene()
{
    //    bool showServiceTerms = false;
    //    showServiceTerms = CCUserDefault::sharedUserDefault()->getStringForKey("service_terms_check","") == "";
    //    if (showServiceTerms) {
    //        if (GlobalData::shared()->permitiCountry != "") {
    //            vector<std::string> mTmpV;
    //            bool showService =true;
    //            CCCommonUtils::splitString(GlobalData::shared()->permitiCountry, "|", mTmpV);
    //            for (int i = 0; i < mTmpV.size(); i++) {
    //                if (GlobalData::shared()->playerInfo->regCountry == mTmpV[i]) {
    //                    showService = false;
    //                    this->unschedule(schedule_selector(LoadingScene::show45SecondAlert));
    //                    UIComponent::getInstance()->setVisible(false);
    //                    PopupViewController::getInstance()->addPopupView(PermitionForServicePopupView::create());
    //                    break;
    //                }
    //            }
    //            if (showService) {
    //                SceneController::getInstance()->gotoScene(SCENE_ID_MAIN);
    //            }
    //        }
    //        else
    //            SceneController::getInstance()->gotoScene(SCENE_ID_MAIN);
    //    }
    //    else
    
    if(GlobalData::shared()->isInDataParsing) {
        printDebugKeyInfo("LoadingError1", true);
        printBackTraceTolog("LoadingScene Should Not GotoScene!");
    }
    auto _showScene = [=]() -> bool{
        if(CCCommonUtils::checkIsOpenByKey("resource_downloading_switch")){
            auto _downType = GlobalData::shared()->m_downloadType;
            int iNeedNum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(_downType);
            if( iNeedNum <= 0 )
            {
                CCLoadSprite::removeImperialResourceCacheWhenLownload();
            }
        }
        
        //检测当前如果是google包，签名是否对应
        if (CCCommonUtils::checkIsOpenByKey("gp_login_contrast") && GlobalData::shared()->analyticID.compare("market_global") == 0){
            std::string keyStoreMd5 = cocos2d::extension::CCDevice::getKeyStoreMD5();
            std::string googleMd5 = "C8:26:AF:AA:53:78:CB:A5:24:D3:F5:B1:90:58:53:B5:71:EB:B5:15";
            if (keyStoreMd5.compare(googleMd5) != 0){
                auto _dialog = YesNoDialog::showVariableTitle(CCString::createWithFormat(_lang("77779900").c_str(), "Google")->getCString(),CCCallFuncO::create(this, callfuncO_selector(LoadingScene::forceUpdate),nullptr), _lang("confirm").c_str(),true);
                _dialog->setCloseCallYes(true);
                return false;
            }
        }
        
        auto firstGuideStr = GlobalData::shared()->playerInfo->uid + "firstTimeEnterGuideWorld";
        auto firstTimeEnterGuideWorld = CCUserDefault::sharedUserDefault()->getBoolForKey(firstGuideStr.c_str(), false);
        if (firstTimeEnterGuideWorld == false && GuideController::share()->needGuide() && GlobalData::shared()->show_guide_video && !GlobalData::shared()->isMiddleEast())
        {
            if (AZCommonUtils::isChinaCountry()){
                SceneController::getInstance()->addGUI();
                SceneController::getInstance()->gotoScene(SCENE_ID_MAIN);
            } else {
                SceneController::getInstance()->gotoScene(SCENE_ID_GUIDE_MANGA);//SCENE_ID_GUIDE_MANGA
            }
        }else if (firstTimeEnterGuideWorld == false && GuideController::share()->needGuide() && (CCCommonUtils::checkIsOpenByKey("ar_guide_switch")) && !cocos2d::extension::CCDevice::canNotUseAR()){
            if (AZCommonUtils::isChinaCountry()){
                SceneController::getInstance()->addGUI();
                SceneController::getInstance()->gotoScene(SCENE_ID_MAIN);
            }else{
                PopupViewController::getInstance()->addPopupView(GuideViewBlackMask::create());
            }
        }
        else
        {
            SceneController::getInstance()->addGUI();
            SceneController::getInstance()->gotoScene(SCENE_ID_MAIN);
        }
        return true;
    };
    
    auto showArenaScene = [=]() -> bool{
        
        SceneController::getInstance()->addGUI();
        SceneController::getInstance()->gotoScene(SCENE_ID_MAIN);
        return true;
    };
    
    if (CCCommonUtils::checkIsOpenByKey("resource_downloading_switch")){
        auto _downType = GlobalData::shared()->m_downloadType;
        int iNeedNum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(_downType);
        if( iNeedNum > 0 )
        {
            DynamicResourceFuDaoController::getInstance()->initDownLoadData(nullptr,_downType); //开启下载
            PopupViewController::getInstance()->addPopupView(UpdatePopUp::create(-1,0,_downType,_showScene));
            //五分钟后,直接进入游戏
//            scheduleOnce([=](float){
//                _showScene();
//            }, 300, "goToScene");
        }
        else
        {
            CCLoadSprite::removeImperialResourceCacheWhenLownload();
            _showScene();
        }
    }
    else if(CCCommonUtils::checkIsOpenByKey("battlefield_download_pic")){
        
        auto _downType = ArenaController::getInstance()->getArenaDownLoadMapType();
        int iNeedNum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(_downType);
        if( iNeedNum > 0 )
        {
            DynamicResourceFuDaoController::getInstance()->initDownLoadData(nullptr,_downType); //开启下载
            PopupViewController::getInstance()->addPopupView(UpdatePopUp::create(-1,0,_downType,showArenaScene));
            //五分钟后,直接进入游戏
            scheduleOnce([=](float){
                showArenaScene();
            }, 300, "goToArenaScene");
        }
        else
        {
            CCLoadSprite::removeImperialResourceCacheWhenLownload();
            _showScene();
        }
        
    }
    else{
        _showScene();
    }
    
    
}

void LoadingScene::onEnterMainScene(float t)
{
    unschedule(schedule_selector(LoadingScene::onEnterMainScene));
    //行云log
    //    GameController::getInstance()->trackVisit();
    //    SceneController::getInstance()->addGUI();
    
    if(SceneController::getInstance()->showBG){
        SceneController::getInstance()->showBG->release();
        SceneController::getInstance()->showBG = nullptr;
        SceneController::getInstance()->addGUI();
        SceneController::getInstance()->gotoScene(SCENE_ID_WORLD);
    }else{
        showMainScene();
    }
    
    //    CCDirector::sharedDirector()->setVisitFlag(true);
}

void LoadingScene::forceUpdate(CCObject* p) {
    m_bShowConfirmPanel = true;
    //服务器下发地址为空
    bool isUrlNull =  GlobalData::shared()->downloadUrl.empty() || GlobalData::shared()->downloadUrl=="null";
    
    if (isUrlNull)
        GameController::getInstance()->quitGame(nullptr);
    else
        GameController::getInstance()->updateVersion();
}

void LoadingScene::onConnectionLost(cocos2d::CCObject *obj)
{
    if( !this->getParent() ) {
        printDebugKeyInfo("LoadingSceneOOM2", true);
        printBackTraceTolog("LoadingScene::onConnectionLost Call Abnormal");
        return;
    }
    
    CCLOG("ConnectionLost");
    CCCommonUtils::recordStepForLoading("12", 0,"",1);
    auto ret = dynamic_cast<NetResult*>(obj);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "onConnectionLost");
    GameController::getInstance()->setLoginErrorLog("LoadingScene", "onConnectionLost");
    //连接失败次数小于N时，不用弹出直接连接下一次
    if (NetController::shared()->isReachToConnectTimes()){//直接走GetServerList
        return;
    }
    int connectTimes = CCUserDefault::sharedUserDefault()->getIntegerForKey("CONNECT_TIMES", 0);
    if (CONNECT_TIMES * 2 > connectTimes) {
        if(IsFLOG()) {
            FLOG("Loading doLogin from onConnectionLost CT %d", connectTimes);
        }
        doLogin(nullptr);
        return;
    }
}

void LoadingScene::doResourceUpdate(CCObject* p) {
    CCLOG("LoadingScene::doResourceUpdate %.2f", m_loadingTotalTime);
    //loadingLog统计
    GameController::getInstance()->setLoadingLog("LoadingScene", "doResourceUpdate");
}

void LoadingScene::offerUpdate(CCObject* p)
{
    m_bShowConfirmPanel = true;
    GlobalData::shared()->updateType=0;
    stepLoading(nullptr);
}

void LoadingScene::closeNotice(CCObject* p){
    GlobalData::shared()->lordInfo.loadingNoticeFlag = 0;
    this->scheduleOnce([this](float dt){
        stepLoading(nullptr);
    }, 0.01f, "StepLoading");
}

void LoadingScene::userAgree(CCObject* p) {
    GlobalData::shared()->lordInfo.agreeUserAgreementFlag = -1;
    
    this->scheduleOnce([this](float dt){
        stepLoading(nullptr);
    }, 0.01f, "StepLoading");
}

//DOTO:jinpeng 网络监测三部曲
void LoadingScene::checkNetStep1(CCObject* p)
{
    if (!_enableCheckNet) {
        return;
    }
    if (NetController::shared()->isConnectedToNetwork()) {  //网络可用
        m_checkNetLog += "checkNetStep1 ok;";
    }
    else {  //不可用
        m_checkNetLog += "checkNetStep1 error;";
    }
}

void LoadingScene::checkNetStep2Ok(CCObject* p)
{
    if (!_enableCheckNet) {
        return;
    }
    
    //再监测一次
    checkNetStep1(nullptr);
    
    if (NetController::shared()->isConnected()) {
        CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, NET_CONNECTED);
        m_checkNetLog += "checkNetStep2 ok;";
    }
    else {
        checkNetStep2Error(nullptr);
    }
}

void LoadingScene::checkNetStep2Error(CCObject* p)
{
    CCCommonUtils::recordStepForLoading("6", 0,"",1);
    if (!_enableCheckNet) {
        return;
    }
    
    CCSafeNotificationCenter::sharedNotificationCenter()->removeObserver(this, SFS_CONNECT_ERROR);
    if (!NetController::shared()->isConnected()) {
        m_checkNetLog += "checkNetStep2 error;";
        //开始监测服务器是否正常
        onLoginTimeout(0);
        
        m_checkNetLog += "begin onLoginTimeout;";
    }
}

void LoadingScene::checkNetStep3Ok(CCObject* p)
{
    if (!_enableCheckNet) {
        return;
    }
    m_isNetStep3Pass = true;
    m_checkNetLog += "checkNetStep3 ok";
}

void LoadingScene::checkNetStep3Error(CCObject* p)
{
    if (!_enableCheckNet) {
        return;
    }
    //服务器连接失败
    m_isNetStep3Pass = false;
    m_checkNetLog += "checkNetStep3 error";
}

void LoadingScene::onNetworkAvailable(CCObject* p)
{
    //连接服务器CONNECT_TIMES次时，发送getserverlist
    if (NetController::shared()->isReachToConnectTimes()){
        sendCmdGetServerList(nullptr);
        return;
    }
    CCLOG("post onNetworkAvailable");
    string ip = CCCommonUtils::getStringWithEncBySharedUser(ACCOUNT_IP);
    if(ip != ""){
        NetController::shared()->connect();
    }else{
        sendCmdGetServerList(nullptr);
    }
}

static std::string XORkey="FEgXWRZIEVkNSAxZ";
std::string LoadingScene::formatAccList(std::string arg)
{
    int length = arg.length();
    int keylength = XORkey.length();
    const char* source = arg.c_str();
    const char* keySource = XORkey.c_str();
    std::string result;
    int i,j, test1, test2;
    char inner;
    for(i = 0; i < length; i++)
    {
        result += char(source[i] ^ 44);
    }
    CCLOG("%s", result.c_str());
    return result;
    
}

std::string LoadingScene::getAccountFromAccountInfo()
{
    if(m_accountInfo == "")
        return "";
    std::vector<std::string> accountList;
    CCCommonUtils::splitString(m_accountInfo, "#", accountList);
    std::string matchName = "";
    std::string account;
    int account_level = 0;
    
    for(auto iter = accountList.begin(); iter!= accountList.end(); iter++)
    {
        if(iter->find("com.google") != -1)
        {
            account = *iter;
            break;
        }
        else if(iter->find("com.fasebook.auth.login"))
        {
            account = *iter;
            account_level = 2;
        }
        else if(iter->find("com.android.mail") != -1)
        {
            if(account_level < 2)
                account = *iter;
        }
        else if(iter->find("com.skype.contacts.sync"))
        {
            if(account_level < 2)
                account = *iter;
        }
    }
    return account;
}

void LoadingScene::showPasswordUI( CCObject* object ) {
    CCInteger* type = dynamic_cast<CCInteger*>(object);
    if( !type ) {
        return;
    }
    int hasPassWord = type->getValue();

    Application::getInstance()->runInBackThread([this, hasPassWord]{
        BACK_PROCESS_THREAD_ID = pthread_self();
        CCDirector::getInstance()->setAutoReleasePoolEnable(false);
        
        scheduleOnce([=](float dt){
            if( hasPassWord ) {
                PopupViewController::getInstance()->addPopupView(PasswordInputPopupView::create(1),false,true,false);
                
            }
            else {
                PopupViewController::getInstance()->addPopupView(PasswordInputPopupView::create(2),false,true,false);
            }
        }, 0.001, "showPasswordUI");
        
        CCDirector::getInstance()->setAutoReleasePoolEnable(true);
    });
    

}
