//
//  LoadingScene.h
//  IF
//
//  Created by 吴 凌江 on 13-8-28.
//
//

#ifndef __IF__LoadingScene__
#define __IF__LoadingScene__

#include "CommonInclude.h"
#include <spine/Json.h>


//LoadingScene
class LoadingScene :
public cocos2d::CCLayer
,public ITouchDelegate
{
public:
	~LoadingScene();
    CREATE_FUNC(LoadingScene);
    
    void removeCNScene();
    void showConnectInfo();
protected:
	LoadingScene(void);
    virtual bool init();
    
    void getSDcardPermit(CCObject* p);

    void doResourceUpdate(CCObject* p);
    void doLogin(CCObject* p);
    void doLoginGP();
    void doLoginInitError(CCObject* p);
    void doLoginantiAddiction(CCObject* p);//防沉迷的禁止登陆
    void doXMLParserInit(CCObject* p);
    void doLoginInit(float t);
    void stepLoading(CCObject* p);
    void loginInitFinsh(CCObject* p);
    void localUnzipFinsh(CCObject* p);
    void onConnectionLost(cocos2d::CCObject* obj);
    void onRelogin(CCObject* p);
    void forceUpdate(CCObject* p);
    void offerUpdate(CCObject* p);
    void userAgree(CCObject* p);
    void closeNotice(CCObject* p);
    void gotoMainScene(float t);
    void onEnterMainScene(float t); // 3dtouch
    void showMainScene();
    virtual void update(float delta);
    
    void setNetCurrentStatus(CCObject* pObject);

private:
    virtual void onEnter();
    void toOnEnter();
    virtual void onExit();
    void onEnterInit();
    void loadingGPLoginCallback(CCObject* p);

    void getHttpGlobeSwitchCallback(CCHttpClient* client, CCHttpResponse* response);
    void clearCacheOK(CCObject *obj);
    void clearCacheCancel(CCObject *obj);
    
    //在CN包的情况下在如果loading超过20s就弹出切换线路的icon
    void showChangeServer(CCObject* obj);
    
    virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void loadContinue(Ref* ref);
    void showLoading(float offsetTime);
    void sendCmdLogin();
    void loadingAni(float t);
    void selectLogin(float t);
    void sendCmdGetServerList(CCObject* p);
    void onGetServerList(CCHttpClient* client, CCHttpResponse* response);
    void onFacebookClick(CCObject *pSender, CCControlEvent event);
    void OpenLoginFB();
    void OpenLoginFBReally(float t);
    void bindFaceBook(CCObject *obj);
    void loginFacebookAction();
    void showFaceBookUI(CCObject *obj);
    void hideFaceBookUI(CCObject *obj);
    void FacebookCallback(CCObject *obj);
    void setLoadingTips();
    
    void onEnterFrame(CCObject* p);
    void onLoginTimeout(float t);
    void onGetServerStatus(CCHttpClient* client, CCHttpResponse* response);
    bool showServiceTerms();
    bool waitingForLogin();
    
    //ios 默认授权的登录处理
    void onResponsed_3rdPlatform(CCObject *obj);
    
    std::string formatAccList(std::string);
    
    //获取机房状态
    void getMainServerStatus();
    void onGetMainServerStatus(CCHttpClient* client, CCHttpResponse* response);
    
    void onGoToHelpShift(CCObject* p);
    
    //DOTO:jinpeng 网络监测三部曲
    void checkNetStep1(CCObject* p);
    void checkNetStep2Ok(CCObject* p);
    void checkNetStep2Error(CCObject* p);
    void checkNetStep3Ok(CCObject* p);
    void checkNetStep3Error(CCObject* p);
    
    void onNetworkAvailable(CCObject* p);
    void onLoadingProgressNew(float t);//新loading条
    //getAccountFromAccountInfo获取mail信息;
    std::string getAccountFromAccountInfo();
    
    // 初始化图片
    void initLoadingImageBg(CCSize size);
    
    bool m_platformLoginFlag;
    int m_steps;
    float m_progress;
    float m_currProgress;//当前的进度条的百分比
    bool m_isNetStep3Pass;
    bool m_bShowConfirmPanel;
    
    CCSafeObject<CCScale9Sprite> m_loadingProgress;
    CCSafeObject<CCLabelIF> m_loadingTips;
    CCSafeObject<CCLabelIF> m_loadPerLabel;
    CCSafeObject<CCLabelIF> m_loadtips;
    CCSafeObject<CCLabelIF> m_FAQ;
    CCSafeObject<CCLabelIF> m_conStatusCode;
    CCSafeObject<CCSprite > m_line;
    CCSafeObject<CCNode> m_FAQTouchNode;
    CCSafeObject<CCSprite > m_platformLogo;
    CCSafeObject<CCClipNode> m_clipNode;
    CCSafeObject<CCClipNode> m_barClipNode;
    CCSafeObject<CCNode> m_headParticleNode;
    CCSafeObject<CCNode> m_tempLoadingNode;
//    CCSafeObject<CCNode> m_netBgNode;
    CCSafeObject<CCSprite> m_underBarLabel;
    CCSize m_barSize;
    CCSafeObject<CCSprite > m_blood;
    CCSafeObject<CCControlButton> m_fbBindBtn;
    CCSafeObject<CCLabelIF> m_faceBookLater;
    CCSafeObject<CCNode> m_LaterTouchNode;
    CCSafeObject<CCLayerColor> m_laterLine;
    float m_loadingTotalTime;
    string m_loginUUID;
    
    bool m_isAiService;
    bool m_updateFAQTips;
    //网络监测log
    std::string m_checkNetLog;
    
    //accountInfo
    std::string m_accountInfo;
    bool needAccountInfo;
    
    vector<string> m_tips;//用来存储loadingtips
    vector<string> m_tipsCache;//用来存储loadingtips
    int m_delayTime;//用来间隔loadingtips
    
    //serverId大于0时，只有正式服可以用
    void showLoading(int serverId,string gameUid);
    //
    void showLoading(string port, string zone, string ip, string gameUid);
    
    bool m_hasDoHttpGlobalSwitchCallback{false};
    void forceDoHttpGlobeSwitchCallback(float dt);
    
    void showPasswordUI(CCObject* object);
    
    bool m_initFinsh{false};
    CCSafeObject<LoginCommand> loginCmd;
    int m_loginTimes{0};
    std::string m_facebookUid;
    std::string m_facebookName;
    int m_type;
    void onEnterProc();
    void createLoadingCN();
    //配置
    std::string loadingBg_config;
    std::string particle_config;
    std::string spine_config;
    std::string frame_config;
    bool isUseLoadingConfig();
    void initLoadingConfig();
};


//中国语言
class LoadingCNScene : public cocos2d::CCLayer
, public CCTouchClickNode
, public CCBMemberVariableAssigner
{
public:
    static LoadingCNScene* create(LoadingScene* scene);
    
protected:
    virtual void onEnter();
    virtual void onExit();
    
    LoadingCNScene(LoadingScene* scene);
    ~LoadingCNScene();
    float m_time;
    int m_opa; //透明度
    bool m_remove;
    virtual bool init();
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual bool onTouchClickNode(CCNode* node);
    
    CCSafeObject<CCNode> m_clickNode;
    CCSafeObject<CCLabelIF> m_tipsTitle;
    CCSafeObject<CCLabelIF> m_tipsContent;
    CCSafeObject<CCNode> m_copyrightNode;
    CCSafeObject<CCLabelIF> m_adviseLabel;
private:
    CCSafeObject<LoadingScene> m_scene;
    CCSafeObject<CCAZTouchNode> m_touchClickNode;
    void updateOpacity(int opa);
};


#endif /* defined(__IF__LoadingScene__) */
