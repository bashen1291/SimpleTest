//
//  UpdatePopUp.h
//  IF
//  进入副岛时的资源更新界面
//  Created by wcx on 16-8-25.
//
//

#ifndef IF_UpdatePopUp_h
#define IF_UpdatePopUp_h

#include "CommonInclude.h"
#include "CCAniNode.h"
#include "PopupBaseView.h"


//UpdatePopUp
class UpdatePopUp: public PopupBaseView
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
{
public:
    static UpdatePopUp* create(int cityIndex = -1,int serverId = 0,DownLoadType type = kFuDao,std::function<bool()> finishFunc = nullptr);
    
    void onUpdateState(float dt, double  aMax, double  aCurrent);

    //设置标题名称
    void setTitleName(string name);
    //设置完成回调函数
    void setFinishCallFunc(CCCallFunc* selector);
    //当更新完成了
    void onUpdateFinish(CCObject *ccObj);
    //当XML更新完成了
    void onXMLUpdateFinish(CCObject *ccObj);
protected:
    UpdatePopUp();
    virtual ~UpdatePopUp();
    
    virtual bool init(int cityIndex,int serverId,DownLoadType type,std::function<bool()> finishFunc);

    virtual void onEnter();
    virtual void onExit();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName){return nullptr;}
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual bool onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    //updatePopUp
    void onCloseClick(CCObject * pSender, CCControlEvent pCCControlEvent);
    void onBackBtnClick(CCObject * pSender, CCControlEvent pCCControlEvent);
    //完成下载
    void onAccelerateClick(CCObject * pSender, CCControlEvent pCCControlEvent);
    //
    void finishCallFunc();
private:
    
    //updatePopUp
    CCSafeObject<CCLabelIF> m_Title;
    //进度条相关
    CCSafeObject<CCNode> m_progressNode;
    CCSafeObject<CCScale9Sprite> m_Progress;
    
    CCSafeObject<Node> m_ProgressNode;
    CCSafeObject<LabelTTF> m_ProgressText; //add by wcx
    
    //完成下载
    CCSafeObject<CCNode> m_CompleteNode;
    CCSafeObject<CCLabelIF> m_CompleteText1;
    CCSafeObject<CCControlButton> m_infobtn;
    CCSafeObject<CCControlButton> m_closeNode;
    CCSafeObject<CCLabelIF> m_CompleteText2;
    CCSafeObject<CCLabelIF> m_infobtnTxt;
    
    CCSafeObject<Node> m_backNode;
    CCSafeObject<CCControlButton> m_backbtn;
    CCSafeObject<CCLabelIF> m_backbtnTxt;
    
    //未完成下载
    CCSafeObject<CCNode> m_UnCompleteNode;
    CCSafeObject<CCLabelIF> m_Loading;
    CCSafeObject<CCLabelIF> m_Speed;
    CCSafeObject<CCLabelIF> m_Require;
    
    CCSafeObject<Node> m_LoadingNode;
    CCSafeObject<Node> m_SpeedNode;
    CCSafeObject<Node> m_RequireNode;
    
    CCSafeObject<LabelTTF> m_LoadingText;//add by wcx
    CCSafeObject<LabelTTF> m_SpeedText;//add by wcx
    CCSafeObject<LabelTTF> m_RequireText;//add by wcx
    
    CCSafeObject<CCScale9Sprite> m_showSpr;
    CCSafeObject<CCScale9Sprite> m_showDesert;
    CCSafeObject<Node> m_showAnimation;
    
    float m_pro; //进度百分比
    int m_totalFiles; //所有需要下载的文件个数
    int m_currentFiles; //已经下完的文件个数
    int m_cityIndex;
    int m_serverId;
    DownLoadType m_type;
    std::function<bool()> m_finishFunc;
    CCSafeObject<CCCallFunc> m_selector;
};

#endif
