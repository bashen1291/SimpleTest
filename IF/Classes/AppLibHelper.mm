
//
//  AppLibHelper.m
//  IF
//
//  Created by chenliang on 14/12/2.
//
//

#include "AppLibHelper.h"
//#include "HelpshiftCocos2dx.h"
//#import "Adjust.h"
#import <FBSDKCoreKit/FBSDKCoreKit.h>

#import <GameKit/GameKit.h>

//#import <Chartboost/Chartboost.h>
//#import <Chartboost/CBNewsfeed.h>
#import <CommonCrypto/CommonDigest.h>
#import <AdSupport/AdSupport.h>

//#import "InMobi.h"
//#import "IMConstants.h"
//#import <Partytrack/Partytrack.h>
#include "ACTReporter.h"
//#import <Fabric/Fabric.h>
//#import <NanigansSDK/NanigansSDK.h>
//#import <TwitterKit/TwitterKit.h>
// -- FCM -- below
//#import <Parse/Parse.h>
#import "Firebase.h"
// -- FCM -- above
#import <Foundation/NSTimeZone.h>
#include "GlobalData.h"
#import <MobileAppTracker/MobileAppTracker.h>
#import "AppsFlyerTracker.h"

#include "PayController.h"
#import "TrackingIO.h"
extern bool g_isSavedUserInfo;

void AppLibHelper::initLibs(){
//    //helpshift
//    HelpshiftCocos2dx::install("724912cc76e6e0e0b3426d0f83a88832",
//                               "lcyd.helpshift.com",
//                               "lcyd_platform_20150630021209965-edefcf5f44a595e");
//    //adjust
//    NSString *yourAppToken = @"meqtfaeq9yqy";
//    NSString *environment = ADJEnvironmentProduction;
//    ADJConfig *adjustConfig = [ADJConfig configWithAppToken:yourAppToken environment:environment];
//    [adjustConfig setLogLevel:ADJLogLevelVerbose];
//    [Adjust appDidLaunch:adjustConfig];
//  //chartboost
//    [Chartboost startWithAppId:@"5477e29543150f10bae6f022"
//                  appSignature:@"cca2c9bbdbd7e935a82cea1569e7950ff45528dd"
//                      delegate:NULL];
//    //inmobi
//    [InMobi initialize:@"81b50f9c47454f5abd0b5844aa161152"];
//  //party
    //[[Partytrack sharedInstance] startWithAppID:4419 AndKey:@"2f4cf9ad914f2042b48cf8e994c6e95c"];
//    //adwords
//    [ACTConversionReporter reportWithConversionID:@"988731911" label:@"FNpUCKCNv1gQh7S71wM" value:@"0.00" isRepeatable:NO];
//    //twitter
//    [[Twitter sharedInstance] startWithConsumerKey:@"SwpZfIehpp9LR6jWVHbOBExPI"
//                                    consumerSecret:@"HvzPRLmIsELDmSh8LFSclDsvDKwftgrIi5V3Tpmzt9KG3mArKm"];
//    [Fabric with:@[[Twitter sharedInstance]]];
//    [NANTracking setNanigansAppId:@"217314" fbAppId:@"713457855362204"];
//    string deviceUid = cocos2d::extension::CCDevice::getDeviceUid();
//    [NANTracking setUserId:[NSString stringWithUTF8String:deviceUid.c_str()]];
//    [NANTracking trackAppLaunch: nil];
    
    
    firstOpenGoogleConversion();

    // 再营销打点
    // Enable automated usage reporting.
    [ACTAutomatedUsageTracker enableAutomatedUsageReportingWithConversionID:@"941350813"];
    googleRemarketingReporter("applaunches");

    //国内ReYun渠道数据统计

    if(CCCommonUtils::isChina()){
        [TrackingIO setPrintLog:false];
        [TrackingIO initWithappKey:@"6391c7f9c1dbed2d20ca5c6e8c39e81c" withChannelId:@"_default_"];
    }


    //firebase
    [FIROptions defaultOptions].deepLinkURLScheme = @"warz";
    [FIRApp configure];
    [FIRAnalytics logEventWithName:@"first open new" parameters:nullptr];
}

void AppLibHelper::firstOpenGoogleConversion() {
    //中东打点
    if(cocos2d::extension::CCDevice::isArab()){
        [ACTConversionReporter reportWithConversionID:@"941350813"
                                                label:@"PSaYCIemkW8Qnb_vwAM"
                                                value:@"0.00"
                                         isRepeatable:NO];
    }else{
        [ACTConversionReporter reportWithConversionID:@"941350813"
                                                label:@"Nz5vCOj5vmwQnb_vwAM"
                                                value:@"0.00"
                                         isRepeatable:NO];
    }
}

void AppLibHelper::paymentGoogleConversion(const string &price) {
    NSString* value = [NSString stringWithUTF8String:price.c_str()];
    if(cocos2d::extension::CCDevice::isArab()){
        [ACTConversionReporter reportWithConversionID:@"941350813"
                                                label:@"tPUACJKokW8Qnb_vwAM"
                                                value:value
                                         isRepeatable:YES];
    }else{
        [ACTConversionReporter reportWithConversionID:@"941350813"
                                                label:@"VVtPCILD_2EQnb_vwAM"
                                                value:value
                                         isRepeatable:YES];
    }
    auto dict = new NSDictionary();
    NSNumber *priceNum= [[NSNumber alloc] initWithDouble:atof(price.c_str())];
    [FIRAnalytics logEventWithName:@"purchase_new" parameters:@{
                                                                kFIRParameterPrice: priceNum,
                                                                kFIRParameterCurrency: @"USD"
                                                                }];
    
}

void AppLibHelper::firstOpenAppsflyer(std::string uid) {
    [AppsFlyerTracker sharedTracker].appsFlyerDevKey = @"XpMfFaBzny3wNYiCPcAwq6";
    [AppsFlyerTracker sharedTracker].appleAppID = @"1040083067";
    [[AppsFlyerTracker sharedTracker] trackAppLaunch];
    [[AppsFlyerTracker sharedTracker] setCustomerUserID:[NSString stringWithUTF8String:uid.c_str()]];

}
void AppLibHelper::appLaunchGoogleConversion(std::string cid, std::string context) {
    [ACTConversionReporter reportWithConversionID:[NSString stringWithUTF8String:cid.c_str()]
                                            label:[NSString stringWithUTF8String:context.c_str()]
                                            value:@"0.00"
                                     isRepeatable:NO];

}
//void AppLibHelper::activateAppsflyer() {
//    [[AppsFlyerTracker sharedTracker] trackAppLaunch];
//}

void AppLibHelper::paymentAppsflyer(const string &price,const string & productId) {
    NSString *purchaseItem = [NSString stringWithUTF8String:productId.c_str()];
    NSString *purchaseDollar = [NSString stringWithUTF8String:price.c_str()];
    NSDictionary *afObj = @{AFEventParamContentId:purchaseItem,
                            AFEventParamRevenue:purchaseDollar,
                            AFEventParamCurrency:@"USD"};
    [[AppsFlyerTracker sharedTracker] trackEvent:AFEventPurchase withValues:afObj];
}

void AppLibHelper::tutorialCompleteAppsflyer(const string &data, int _type) {
    NSString *pData = [NSString stringWithUTF8String:data.c_str()];
    if (_type == 0){ //新手结束
        NSDictionary *afObj = @{AFEventParamCustomerUserId:pData};
        [[AppsFlyerTracker sharedTracker] trackEvent:AFEventTutorial_completion withValues:afObj];
    }else if (_type == 1){ //大本六级
        NSDictionary *afObj = @{AFEventParamCustomerUserId:pData};
        [[AppsFlyerTracker sharedTracker] trackEvent:@"af_level_achieved_6level" withValues:afObj];
    }else if (_type == 2){ //登陆5次
        NSDictionary *afObj = @{AFEventParamCustomerUserId:pData};
        [[AppsFlyerTracker sharedTracker] trackEvent:@"login_5_times" withValues:afObj];
    }else if (_type == 3){ //loading条结束
        NSDictionary *afObj = @{AFEventParamCustomerUserId:pData};
        [[AppsFlyerTracker sharedTracker] trackEvent:@"loading_finish" withValues:afObj];
    }
}

string AppLibHelper::getLocalCountry(){
    NSLocale *locale = NSLocale.currentLocale;
    if(!locale){
        return "";
    }
    NSString *countryCode = [locale objectForKey:NSLocaleCountryCode];
    if(!countryCode){
        return "";
    }
    return [countryCode UTF8String];
}

string AppLibHelper::getIDFA(){
    NSString *IDFA = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
    return [IDFA UTF8String];
}

bool AppLibHelper::getAdvertisingTrackingEnabled(){
    return [[ASIdentifierManager sharedManager] isAdvertisingTrackingEnabled];
}

void AppLibHelper::triggerEventPurchase(const string &cost,const string &itemId,const string &orderId,const string &userId){
    NSString *nsUserId = [NSString stringWithUTF8String:userId.c_str()];
    NSString *nsOrderId = [NSString stringWithUTF8String:orderId.c_str()];
    double price = [[NSString stringWithUTF8String:cost.c_str()] doubleValue];
    [FBSDKAppEvents logPurchase:price/2 currency:@"USD"];
    
    string costCNY = PayController::getInstance()->getPriceCNY(cost);
    double priceCNY = [[NSString stringWithUTF8String:costCNY.c_str()] doubleValue];
    if(CCCommonUtils::isChina()){
        [TrackingIO	setryzf:nsOrderId	ryzfType:@"im30" currentType:@"CNY" currencyAmount:(double)priceCNY/10];
    }


}

void AppLibHelper::sendAdjustTrack(const string &track, const string &eventValue){
    NSString *eventToken = NULL;
    if("two_days_login" == track)
        eventToken = @"napcq5";
    if("tutorial_over" == track)
        eventToken = @"rt3ax4";
    if("first_pay" == track)
        eventToken = @"1pc0mi";
    if("reach_level_6" == track)
        eventToken = @"zawvhh";
    if(eventToken != NULL){
//        ADJEvent *event = [ADJEvent eventWithEventToken:eventToken];
//        [Adjust trackEvent:event];
    }
}

void AppLibHelper::updatePlatformScore(int score){
    if ([GKLocalPlayer localPlayer].isAuthenticated) {
        NSString *identifier = @"base";
        GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier: identifier];
        scoreReporter.value = score;
        scoreReporter.context = 0;
        
        NSArray *scores = @[scoreReporter];
        [GKScore reportScores:scores withCompletionHandler:^(NSError *error) {
            //Do something interesting here.
        }];
    }
}

//static PFObject *theLastSaveGameScore = nullptr;

//void saveDataToParseInBackground(PFObject *gameScore)
//{
//    if(gameScore == nullptr) {
//        gameScore = [PFObject objectWithClassName:@"UserInfo"];
//    }
//    gameScore[@"name"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.name.c_str()];
//    gameScore[@"uid"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.uid.c_str()];
//    gameScore[@"pic"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.pic.c_str()];
//    gameScore[@"level"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.level];
//    gameScore[@"nickName"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.nickName.c_str()];
//    gameScore[@"country"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.country];
//    gameScore[@"roomName"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.roomName.c_str()];
//    gameScore[@"allianceRank"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.allianceRank];
//    gameScore[@"gold"] =[[NSNumber alloc] initWithLong:GlobalData::shared()->playerInfo.gold];
//    gameScore[@"payTotal"] = [[NSNumber alloc] initWithLong:GlobalData::shared()->playerInfo.payTotal];
//    gameScore[@"exp"] = [[NSNumber alloc] initWithLong:GlobalData::shared()->playerInfo.exp];
//    gameScore[@"openedSystem"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.openedSystem.c_str()];
//    gameScore[@"gmFlag"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.gmFlag];
//    gameScore[@"renameTime"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.renameTime];
//    gameScore[@"protectTimeStamp"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.protectTimeStamp];
//    gameScore[@"resourceProtectTimeStamp"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.resourceProtectTimeStamp];
//    gameScore[@"vipPoints"] = [[NSNumber alloc] initWithLong:GlobalData::shared()->playerInfo.vipPoints];
//    gameScore[@"vipEndTime"] = [[NSNumber alloc] initWithLong:GlobalData::shared()->playerInfo.vipEndTime];
//    gameScore[@"nextDayLoginVipReward"] = [[NSNumber alloc] initWithLong:GlobalData::shared()->playerInfo.nextDayLoginVipReward];
//    gameScore[@"consecutiveLoginDays"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.consecutiveLoginDays];
//    gameScore[@"isfirstJoin"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.isfirstJoin];
//    
//    gameScore[@"sciencePower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.sciencePower];
//    gameScore[@"battleLose"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.battleLose];
//    gameScore[@"armyDead"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.armyDead];
//    gameScore[@"armyPower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.armyPower];
//    gameScore[@"fortPower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.fortPower];
//    gameScore[@"armyCure"] = [[NSNumber alloc] initWithLong:GlobalData::shared()->playerInfo.armyCure];
//    gameScore[@"questpower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.questpower];
//    gameScore[@"playerPower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.playerPower];
//    gameScore[@"armyKill"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.armyKill];
//    gameScore[@"buildingPower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.buildingPower];
//    gameScore[@"defenseWin"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.defenseWin];
//    gameScore[@"heroPower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.heroPower];
//    gameScore[@"attackLose"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.attackLose];
//    gameScore[@"detectNum"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.detectNum];
//    gameScore[@"cityDes"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.cityDes];
//    gameScore[@"attackWin"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.attackWin];
//    gameScore[@"battleWin"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.battleWin];
//    gameScore[@"power"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.power];
//    gameScore[@"isApplied"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.isApplied];
//    gameScore[@"invited"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.invited];
//    gameScore[@"bindFlag"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.bindFlag];
//    
//    gameScore[@"rank"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.rank];
//    gameScore[@"pointId"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.pointId];
//    gameScore[@"mainCityLv"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.mainCityLv];
//    gameScore[@"officer"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.officer.c_str()];
//    gameScore[@"relinquishFlag"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.relinquishFlag];
//    gameScore[@"relinquishEndTime"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.relinquishEndTime];
//
//    gameScore[@"isInAlliance"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.isInAlliance()];
//    gameScore[@"lastBattlePower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.lastBattlePower];
//    gameScore[@"battlePower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.battlePower];
//    gameScore[@"addPower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.addPower];
//    gameScore[@"getTotalPower"] = [[NSNumber alloc] initWithDouble:GlobalData::shared()->playerInfo.getTotalPower()];
//    gameScore[@"getPic"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.getPic().c_str()];
//    gameScore[@"getBodyPic"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.getBodyPic().c_str()];
//    gameScore[@"isChatView"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.isChatView];
//    gameScore[@"selfServerId"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.selfServerId];
//    gameScore[@"currentServerId"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.currentServerId];
//    gameScore[@"serverName"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.serverName.c_str()];
//    gameScore[@"regCountry"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.regCountry.c_str()];
//    
//    gameScore[@"isInSelfServer"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.isInSelfServer()];
//    gameScore[@"isMOD"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.isMOD()];
//    gameScore[@"inviCode"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.inviCode.c_str()];
//    gameScore[@"picVer"] = [[NSNumber alloc] initWithInt:GlobalData::shared()->playerInfo.picVer];
//    gameScore[@"getCustomPicUrl"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->playerInfo.getCustomPicUrl().c_str()];
//    gameScore[@"isUseCustomPic"] = [[NSNumber alloc] initWithBool:GlobalData::shared()->playerInfo.isUseCustomPic()];
//    gameScore[@"deviceid"] = [[NSString alloc] initWithUTF8String:cocos2d::extension::CCDevice::getDeviceUid().c_str()];
//
//    gameScore[@"analyticID"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->analyticID.c_str()];
//    gameScore[@"platformUID"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->platformUID.c_str()];
//    string strParseInstallationId = cocos2d::extension::CCDevice::getParseInstallationId();
//    gameScore[@"parseRegisterId"] = [[NSString alloc] initWithUTF8String:strParseInstallationId.c_str()];
//    // 字符串检索太费时，追加一个整数判断是否存在推送ID
//    if(strParseInstallationId.empty()) {
//        gameScore[@"hasParseId"] = [[NSNumber alloc] initWithInt:0];
//    } else {
//        gameScore[@"hasParseId"] = [[NSNumber alloc] initWithInt:1];
//    }
//    gameScore[@"fromCountry"] = [[NSString alloc] initWithUTF8String:GlobalData::shared()->fromCountry.c_str()];
//    gameScore[@"systemTimeZone"] = [[NSString alloc] initWithFormat:@"GMT:%d", 1000 * [[NSTimeZone systemTimeZone] secondsFromGMT]];
//    gameScore[@"defaultTimeZone"] = [[NSString alloc] initWithFormat:@"GMT:%d", 1000 * [[NSTimeZone defaultTimeZone] secondsFromGMT]];
//    gameScore[@"localTimeZone"] = [[NSString alloc] initWithFormat:@"GMT:%d", 1000 * [[NSTimeZone localTimeZone] secondsFromGMT]];
//
//    int nBuildMainLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("FUN_BUILD_MAIN", 1);
//    gameScore[@"mainBuildLevel"] = [[NSNumber alloc] initWithInt:nBuildMainLevel];
//
//    std::string preferredLanguage = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_PREFERRED_LANGUAGE, "");
//    gameScore[@"lang"] = [[NSString alloc] initWithUTF8String:preferredLanguage.c_str()];
//
////    theLastSaveGameScore = gameScore;
//    //[gameScore saveInBackground];
//    [gameScore save];
////    [gameScore saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
////        if (succeeded){
////            NSLOG(@"Object Uploaded!");
////            NSString *objectId = theLastSaveGameScore.objectId;
////            string strParseObjectId = [objectId UTF8String];
////            CCUserDefault::sharedUserDefault()->setStringForKey("ParseUserInfoObjectId", strParseObjectId);
////            theLastSaveGameScore = nullptr;
////        } else {
////            NSString *errorString = [[error userInfo] objectForKey:@"error"];
////            NSLOG(@"Error: %@", errorString);
////        }  
////    }];
//    
//    NSString *objectId = gameScore.objectId;
//    if(objectId != nil) {
//        string strParseObjectId = [objectId UTF8String];
//    	CCUserDefault::sharedUserDefault()->setStringForKey("ParseUserInfoObjectId", strParseObjectId);
//    }
//    gameScore = nullptr;
//    g_isSavedUserInfo = true;
//}

void AppLibHelper::saveDataToParse() {
    //by dxm 可能造成聊天切回卡顿，暂时注释数据打点，如果需要打开请确保在游戏退出时打开
    return;
//    if(g_isSavedUserInfo || !(GlobalData::shared()->isInitFinish)) {
//        return;
//    }
//    string thePFObjectId = CCUserDefault::sharedUserDefault()->getStringForKey("ParseUserInfoObjectId", "");
//    if(thePFObjectId.empty()) {
//        saveDataToParseInBackground(nullptr);
//        return;
//    }
//    PFQuery *query = [PFQuery queryWithClassName:@"UserInfo"];
//    NSString* NSPFObjectId = [[NSString alloc] initWithUTF8String:thePFObjectId.c_str()];
//    // Retrieve the object by id
//    [query getObjectInBackgroundWithId:NSPFObjectId block:^(PFObject *gameScore, NSError *error) {
//        // Now let's update it with some new data. In this case, only cheatMode and score
//        // will get sent to the cloud. playerName hasn't changed.
//        if(gameScore == nil) {
//            saveDataToParseInBackground(nullptr);
//        } else {
//            saveDataToParseInBackground(gameScore);
//        }
//    }];
}

void AppLibHelper::fbEventActivate(){
    [FBSDKAppEvents activateApp];
}

void AppLibHelper::triggerEventLoginComplete(const string &userId, const string &userName, const string &userLevel){
    NSString* nsUserId = [NSString stringWithUTF8String:userId.c_str()];
    if(CCCommonUtils::isChina()){
        [TrackingIO setLoginWithAccountID:nsUserId];
    }


}

void AppLibHelper::triggerEventForeground(){
//    [NANTracking trackAppLaunch:nil];
}

void AppLibHelper::triggerEventExistUser(){
    [Tune setExistingUser:true];
}

void AppLibHelper::triggerEventCompletedRegistration(const string &userId,const string &userName){
    NSString* nsUserId = [NSString stringWithUTF8String:userId.c_str()];
    NSString* nsUserName = [NSString stringWithUTF8String:userName.c_str()];
    [FBSDKAppEvents logEvent:FBSDKAppEventNameCompletedRegistration];
    if(CCCommonUtils::isChina()){
        [TrackingIO setRegisterWithAccountID:nsUserId];
    }
}

void AppLibHelper::fbEventCompletedTutorial(){
    [FBSDKAppEvents logEvent:FBSDKAppEventNameCompletedTutorial];
}

void AppLibHelper::fbEventAchievedLevel(int level){
    NSString *eventLevel = [NSString stringWithFormat:@"%d",level];
    [FBSDKAppEvents logEvent:FBSDKAppEventNameAchievedLevel
               parameters:@{ FBSDKAppEventParameterNameLevel : eventLevel}];
}

void AppLibHelper::fbEventDone(std::string event, std::string data){
    NSString* pEvent = [NSString stringWithUTF8String:event.c_str()];
    NSString *pData = [NSString stringWithUTF8String:data.c_str()];
    [FBSDKAppEvents logEvent:pEvent
                  parameters:@{ @"level" : pData}];
}

void AppLibHelper::googleRemarketingReporter(const string type, const string value, const string spe){
    NSString* actionType = [NSString stringWithUTF8String:type.c_str()];
    NSDictionary *customParameters = nullptr;
    if (value == "") {
        customParameters = @{@"action_type":actionType};
    }else{
        NSString* eventValue = [NSString stringWithUTF8String:value.c_str()];
        customParameters = @{@"action_type":actionType, @"value":eventValue};
    }
    
    if (spe.compare("true") == 0){
        NSString* label = [NSString stringWithUTF8String:value.c_str()];
        [ACTConversionReporter reportWithConversionID:@"941350813" label:label value:@"0.00" isRepeatable:YES];
        return;
    }
    
    if(cocos2d::extension::CCDevice::isArab())
    {
        [ACTRemarketingReporter reportWithConversionID:@"941350813" customParameters:customParameters];
    }
    else
    {
        [ACTRemarketingReporter reportWithConversionID:@"932337513" customParameters:customParameters];
    }
}

