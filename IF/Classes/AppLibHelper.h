//
//  AppLibHelper.h
//  IF
//
//  Created by chenliang on 14/12/2.
//
//

#ifndef IF_AppLibHelper_h
#define IF_AppLibHelper_h

#include "CommonInclude.h"

class AppLibHelper
{
public:
    
    static void sendAdjustTrack(const string &track, const string &eventValue = "");
    static void relogin();
    static void updatePlatformScore(int score);

    static void triggerEventPurchase(const string &cost,const string &itemId,const string &orderId,const string &userId);
    static void triggerEventLoginComplete(const string &userId,const string &userName,const string &userLevel);
    static void triggerEventCompletedRegistration(const string &userId,const string &userName);
    static void fbEventCompletedTutorial();
    static void fbEventMainBuildingLevel(int level);
    static void fbEventAchievedLevel(int level);
    static void triggerEventPurchaseInit(const string &cost,const string &itemId);
    static void fbEventDone(std::string event, std::string data);
       static vector<std::string> getServiceTerms(int type);
    
    static void saveDataToParse();
    
    /**
     Appsflyer 打点

     @param data 需要传递的数据
     @param _type 传递的类型
     */
    static void tutorialCompleteAppsflyer(const string & data, int _type);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static void sendToBranch(std::string cmd, std::string value);
    static void initLibs();
    static void firstOpenGoogleConversion();
    static void paymentGoogleConversion(const string & price);
    static void firstOpenAppsflyer(std::string uid);
    static void appLaunchGoogleConversion(std::string cid, std::string context);
    static void activateAppsflyer();
    static void paymentAppsflyer(const string & price,const string & productId);
    
    static string getLocalCountry();
    static string getIDFA();
    static bool getAdvertisingTrackingEnabled();
    static void triggerEventExistUser();
    static void fbEventActivate();
    static void triggerEventForeground();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#endif
    
    // google再营销
    static void googleRemarketingReporter(const string type, const string value="", std::string spe = "");
    
};

#endif
