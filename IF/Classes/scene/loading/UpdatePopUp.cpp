//
//  UpdatePopUp.h
//  IF
//  进入副岛时的资源更新界面
//  Created by wcx on 16-8-25.
//
//

#include "UpdatePopUp.h"
#include "ParticleController.h"
#include "PopupViewController.h"
#include "FunBuildController.h"
#include "DynamicResourceFuDaoController.h"
#include "SceneController.h"
#include "CCLoadSprite.h"
#include "AZMissileAttackLayer.h"

using namespace cocos2d;

//UpdatePopUp
UpdatePopUp* UpdatePopUp::create(int cityIndex,int serverId,DownLoadType type,std::function<bool()> finishFunc)
{
    UpdatePopUp *pRet = new UpdatePopUp();
    if (pRet && pRet->init(cityIndex,serverId,type,finishFunc))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL(pRet);
    }
    return pRet;
}

void UpdatePopUp::setTitleName(string name)
{
    if (name.empty()){
        return;
    }
    if (m_Title){
        m_Title->setString(name);
    }
}

void UpdatePopUp::setFinishCallFunc(CCCallFunc* selector)
{
    m_selector = selector;
}

UpdatePopUp::UpdatePopUp()
:m_totalFiles(0)
,m_currentFiles(1)
,m_pro(0.0f)
,m_cityIndex(-1)
,m_serverId(0)
,m_type(kFuDao)
,m_selector(nullptr)
,m_finishFunc(nullptr)
{
}

UpdatePopUp::~UpdatePopUp()
{
}

bool UpdatePopUp::init(int cityIndex,int serverId,DownLoadType type,std::function<bool()> finishFunc)
{
    if (!PopupBaseView::init())
    {
        return false;
    }
    m_serverId = serverId;
    m_cityIndex = cityIndex;
    m_type = type;
    m_finishFunc = finishFunc;
    CCLoadSprite::autoDoResourceByCommonIndex(COMMON_15, this);
    if(m_type == kGreatLaunchCenter)
    {
        CCLoadSprite::autoDoResourceByCommonIndex(COMMON_16, this);
    }
    CCNode*  iccb = CCBLoadFile("UpdatePopUp",this,this);
    this->setContentSize(iccb->getContentSize());
    if (m_closeNode != nullptr && !CCCommonUtils::checkIsOpenByKey("SWITCH_0523")){
        m_closeNode->setEnabled(false);
        m_closeNode->setVisible(false);
    }
    m_totalFiles = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(m_type);
    {
        if(m_type == kGreatLaunchCenter)
        {
            m_Title->setString(_lang("171738"));
        }else if(m_type == kHeFu){
            m_Title->setString(_lang("79001052"));
        }else if(m_type == kHeFuEx){
            m_Title->setString(_lang("79001052"));
        }
        else if(m_type == kXML){
            m_Title->setString(_lang("100989"));

        }else if(m_type >= kArenaMap0 && m_type < kArenaMapEnd){
            m_Title->setString(_lang("172268"));
        }else if(m_type == kBattlePerformance){
            m_Title->setString(_lang("84000161"));
        }else if(m_type == kSubsidiary){
            m_Title->setString(_lang("174530"));
        }
        else
        {
            m_Title->setString(_lang("190000"));
        }
    }
    {
        m_Loading->setString(_lang("190003"));
    }
    
    if(m_showSpr)
    {
        m_showSpr->setVisible(false);
        if(m_type == kGreatLaunchCenter)
        {
            m_showSpr->setVisible(true);
        }
    }
    
    if(m_showDesert)
    {
        m_showDesert->setVisible(false);
        if(m_type == kHeFu || m_type == kHeFuEx)
        {
            m_showDesert->setVisible(true);
        }
    }

    if (m_showAnimation){
        m_showAnimation->setVisible(false);
        if(m_type == kBattlePerformance)
        {
            m_showAnimation->setVisible(true);
        }
    }
    
    {
        m_ProgressText = LabelTTF::create();
        m_ProgressText->setString(_lang("190003"));
        m_ProgressText->setFontSize(18);
        m_ProgressNode->addChild(m_ProgressText);
    }
    
    {
        m_LoadingText = LabelTTF::create();
        m_LoadingText->setString("");
        m_LoadingText->setFontSize(18);
        m_LoadingNode->addChild(m_LoadingText);
    }
    {
        m_CompleteText1->setString(_lang("190006"));//下载完成
        m_CompleteText2->setString(_lang("190007"));
        m_infobtnTxt->setString(_lang("190008"));//立即前往
    }
    m_CompleteNode->setVisible(false);
    m_backNode->setVisible(false);
    if (m_type != DownLoadType::kHeFu){
        m_backNode->setVisible(true);
        m_backbtnTxt->setString(_lang("81000764"));
    }
    m_UnCompleteNode->setVisible(false);
    return true;
}

void UpdatePopUp::onEnter()
{
    PopupBaseView::onEnter();
	setTouchEnabled(true);
    addNotifyObserverWithParams(UpdatePopUp::onUpdateFinish, MSG_DYNAMIC_DOWNLOAD_FD_FINISH, nullptr);
    if (kXML == m_type){
        addNotifyObserverWithParams(UpdatePopUp::onXMLUpdateFinish, MSG_FORCE_XML_DOWNLOAD_FINISH, nullptr);
    }
    GlobalData::shared()->forbidRemove = ForbidRemoveAllView::kUpdatePopup;
    DynamicResourceFuDaoController::getInstance()->setUpdatePopupView(this);
}

void UpdatePopUp::onExit()
{
	setTouchEnabled(false);
    DynamicResourceFuDaoController::getInstance()->setUpdatePopupView(nullptr);
    CCSafeNotificationCenter::sharedNotificationCenter()->removeAllObserver(this);
    PopupBaseView::onExit();
    
    GlobalData::shared()->forbidRemove = ForbidRemoveAllView::kPayRewardNone;
}

void UpdatePopUp::onUpdateState(float dt, double  aMax, double  aCurrent)
{
    if(m_pro == dt)
    {
        return ;
    }
    CCLOG("%s 1", __FUNCTION__);
    m_CompleteNode->setVisible(false);
    if (m_type != DownLoadType::kHeFu){
        m_backNode->setVisible(true);
    }
    m_UnCompleteNode->setVisible(true );
    
    m_currentFiles = m_totalFiles-DynamicResourceFuDaoController::getInstance()->getLastNum() +1 ;
    if(m_currentFiles > m_totalFiles)
    {
        m_currentFiles = m_totalFiles;
    }
    
    if(m_currentFiles < 1)
    {
        m_currentFiles = 1;
    }
    
    char iarr[512] = {0};
    m_pro = dt;
    sprintf(iarr, "%0.2f%s", m_pro ,"%");
    string istr = string(iarr);
    
    CCLOG("%s 2", __FUNCTION__);
    m_ProgressText->setString(istr);
    CCLOG("%s 3", __FUNCTION__);
    m_Progress->setScaleX(m_pro/100.0f);
    CCLOG("%s 4", __FUNCTION__);

    float iCurrent = 0.0f;
    if(aCurrent > 0.0f)
    {
        iCurrent = aCurrent/1024.0f/1024.0f;
    }
    
    float iMax = 0.0f;
    if(aMax > 0.0f)
    {
        iMax = aMax/1024.0f/1024.0f;
    }
    {
        char iarr[512] = {0};
        CCLOG("%s 4.1 ", __FUNCTION__);
        if(m_type == kXML){
            sprintf(iarr, "%0.2fMB/%0.2fMB", iCurrent , iMax);
        }
        else{
            sprintf(iarr, "%0.2fMB/%0.2fMB (%d/%d)", iCurrent , iMax , m_currentFiles, m_totalFiles);
        }

        
        CCLOG("%s 4.2 ", __FUNCTION__);
        if(m_LoadingText && m_LoadingText->getString().compare(iarr) != 0)
        {
            m_LoadingText->setString(string(iarr));
        }
        CCLOG("%s 4.3 ", __FUNCTION__);
    }
}

//当更新完成了
void UpdatePopUp::onUpdateFinish(CCObject *ccObj)
{
    auto obj = dynamic_cast<CCInteger*>(ccObj);
    if (obj && obj->getValue() != m_type){
        return;
    }
    if(DynamicResourceFuDaoController::getInstance()->getLastNum() > 1)
    {
        return ;
    }
    m_CompleteNode->setVisible(true);
    m_backNode->setVisible(false);
    m_UnCompleteNode->setVisible(false);
    m_ProgressText->setString(_lang("190002"));
}

void UpdatePopUp::onXMLUpdateFinish(CCObject *ccObj)
{
    CCString* str = dynamic_cast<CCString*>(ccObj);
    if( str  ) {
        if( str->_string != "" ) {
            {
                m_ProgressText->setString("DOWNLOAD ERROR!!!");
            }
            return;
        }
    }
    closeSelf();
    finishCallFunc();
}

void UpdatePopUp::onCloseClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
    closeSelf();
    int inum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(m_type);
    if(inum <= 0) //如果下载完成，进入副岛
    {
        if(m_cityIndex == -1 && m_type == kFuDao){
            SceneController::getInstance()->gotoScene(SCENE_ID_MAIN_EX);
        }else if(m_cityIndex == -1 && m_type == kSubsidiary){
            SceneController::getInstance()->gotoScene(SCENE_ID_SUBSIDIARY);
        }
        finishCallFunc();
    }
}

void UpdatePopUp::onBackBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
    closeSelf();
    int inum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(m_type);
    if(inum <= 0) //如果下载完成，进入副岛
    {
        if(m_cityIndex == -1 && m_type == kFuDao){
            SceneController::getInstance()->gotoScene(SCENE_ID_MAIN_EX);
        }else if(m_cityIndex == -1 && m_type == kSubsidiary){
            SceneController::getInstance()->gotoScene(SCENE_ID_SUBSIDIARY);
        }
        finishCallFunc();
    }
}

void UpdatePopUp::finishCallFunc()
{
    if(m_finishFunc){
        m_finishFunc();
    }
    if (m_selector){
        CCSafeObject<CallFunc> fun(m_selector);
        fun->execute();
    }
}

//完成下载
void UpdatePopUp::onAccelerateClick(CCObject * pSender, CCControlEvent pCCControlEvent)
{
    closeSelf();
    int inum = DynamicResourceFuDaoController::getInstance()->getNeedDownLoadFileNume(m_type);
    if(inum <= 0)
    {
        if (m_type == kFuDao) {
            if(m_cityIndex == -1){
                SceneController::getInstance()->gotoScene(SCENE_ID_MAIN_EX);
            }
            else{
                PopupViewController::getInstance()->addPopupView(AZMissileAttackLayer::create(m_cityIndex,m_serverId),false,true,false);
            }
        }
        
        finishCallFunc();
    }
}

SEL_CCControlHandler UpdatePopUp::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseClick", UpdatePopUp::onCloseClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBackBtnClick", UpdatePopUp::onBackBtnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAccelerateClick", UpdatePopUp::onAccelerateClick);
    return nullptr;
}

bool UpdatePopUp::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
    //updatePopUp
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_Title", CCLabelIF*, this->m_Title);
    
    //进度条相关
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_progressNode", CCNode*, this->m_progressNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_Progress", CCScale9Sprite*, this->m_Progress);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_ProgressNode", Node*, this->m_ProgressNode);
    
    //完成下载
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_CompleteNode", CCNode*, this->m_CompleteNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_CompleteText1", CCLabelIF*, this->m_CompleteText1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_infobtn", CCControlButton*, this->m_infobtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_CompleteText2", CCLabelIF*, this->m_CompleteText2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_infobtnTxt", CCLabelIF*, this->m_infobtnTxt);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_backNode", CCNode*, this->m_backNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_backbtn", CCControlButton*, this->m_backbtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_backbtnTxt", CCLabelIF*, this->m_backbtnTxt);
    
    //未完成下载
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_UnCompleteNode", CCNode*, this->m_UnCompleteNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_Loading", CCLabelIF*, this->m_Loading);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_Speed", CCLabelIF*, this->m_Speed);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_Require", CCLabelIF*, this->m_Require);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_LoadingNode", Node*, this->m_LoadingNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_SpeedNode", Node*, this->m_SpeedNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_RequireNode", Node*, this->m_RequireNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_showSpr", CCScale9Sprite*, this->m_showSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_showDesert", CCScale9Sprite*, this->m_showDesert);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_showAnimation", Node*, this->m_showAnimation);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "m_closeNode", CCControlButton*, this->m_closeNode);
    return false;
}

bool UpdatePopUp::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (0 < PopupViewController::getInstance()->getCurrViewCount()) {
        return false;
    }
//    if (isTouchInside(m_touchNode, pTouch)) {
//        return true;
//    }
    return false;
}

void UpdatePopUp::onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
//    if (isTouchInside(m_touchNode, pTouch)) {
//    }
}


