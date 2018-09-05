//
//  AppLibHelper.cpp
//  IF
//
//  Created by chenliang on 14/12/11.
//
//
#include "AppLibHelper.h"
#include "GlobalData.h"
#include "PlayerInfo.h"
#include "CCDevice.h"

#define CATCH_MAINBUILDING_LEVEL "catch_mb_level"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include "GamePublisher.h"

extern bool g_isSavedUserInfo;

void AppLibHelper::triggerEventCompletedRegistration(const string &userId,const string &userName){
    GamePublisher::triggerEventCompletedRegistration(userId,userName);
}

void AppLibHelper::triggerEventLoginComplete(const string &userId, const string &userName, const string &userLevel){
    GamePublisher::triggerEventLoginComplete(userId,userName,userLevel);
}

void AppLibHelper::triggerEventPurchase(const string &cost,const string &itemId,const string &orderId,const string &userId){
    GamePublisher::triggerEventPurchase(cost,itemId,orderId,userId);
}


void AppLibHelper::sendAdjustTrack(const string &track, const string &eventValue){
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "com/clash/of/jni/Jni", "trackEvent", "(Ljava/lang/String;Ljava/lang/String;)V") ) {
        CCLOG("JNI: AppLibHelper method trackEvent not found!");
        return;
    }
    jstring tmpTrack = minfo.env->NewStringUTF(track.c_str());
    jstring tmpValue = minfo.env->NewStringUTF(eventValue.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,tmpTrack, tmpValue);
    minfo.env->DeleteLocalRef(tmpTrack);
    minfo.env->DeleteLocalRef(minfo.classID);
}
void AppLibHelper::tutorialCompleteAppsflyer(const string &data, int _type) {
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/ext/CppCallJava","tutorialCompleteAppsflyer","(Ljava/lang/String;I)V") ) {
        CCLOG("JNI: AppLibHelper method tutorialCompleteAppsflyer not found!");
        return;
    }
    jstring tmpplayerUid = minfo.env->NewStringUTF(data.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,tmpplayerUid, _type);
    minfo.env->DeleteLocalRef(tmpplayerUid);
    minfo.env->DeleteLocalRef(minfo.classID);
}
//////////////
void AppLibHelper::updatePlatformScore(int score){
    if(GlobalData::shared()->analyticID != "market_global")
        return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "com/clash/of/util/MyGooglePlusUtil", "submitScore", "(I)V") ) {
        CCLOGFUNC("jni: no method");
        return;
    }
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, score);
    minfo.env->DeleteLocalRef(minfo.classID);
#endif
}

void AppLibHelper::fbEventCompletedTutorial(){
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/stac/empire/sns/FBUtil", "fbEventCompletedTutorial", "()V") ) {
        CCLOG("JNI: fbEvent method fbEventCompletedTutorial not found!");
        return;
    }
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void AppLibHelper::fbEventAchievedLevel(int level){
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/stac/empire/sns/FBUtil", "fbEventAchievedLevel", "(I)V") ) {
        CCLOG("JNI: fbEvent method fbEventAchievedLevel not found!");
        return;
    }
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, level);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void AppLibHelper::fbEventDone(std::string event, std::string data){
    JniMethodInfo minfo;
    if (! JniHelper::getStaticMethodInfo(minfo, "org/hcg/stac/empire/sns/FBUtil", "fbEventDone", "(Ljava/lang/String;Ljava/lang/String;)V") ) {
        CCLOG("JNI: fbEvent method fbEventAchievedLevel not found!");
        return;
    }
    jstring tmpevent = minfo.env->NewStringUTF(event.c_str());
    jstring tmpdata = minfo.env->NewStringUTF(data.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, tmpevent, tmpdata);
    minfo.env->DeleteLocalRef(tmpevent);
    minfo.env->DeleteLocalRef(tmpdata);
    minfo.env->DeleteLocalRef(minfo.classID);
}

void AppLibHelper::googleRemarketingReporter(const string type, const string value, const string spe){
    JniMethodInfo minfo;
    if (!JniHelper::getStaticMethodInfo(minfo, "com/clash/of/util/MyGooglePlusUtil", "googleRemarketingReporter", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V") ) {
        CCLOG("JNI: googleRemarketing method googleRemarketingReporter not found!");
        return;
    }
    jstring eventType = minfo.env->NewStringUTF(type.c_str());
    jstring eventValue = minfo.env->NewStringUTF(value.c_str());
    jstring eventSpe = minfo.env->NewStringUTF(spe.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, eventType, eventValue, eventSpe);
    minfo.env->DeleteLocalRef(eventType);
    minfo.env->DeleteLocalRef(eventValue);
    minfo.env->DeleteLocalRef(eventSpe);
    minfo.env->DeleteLocalRef(minfo.classID);
}


void AppLibHelper::saveDataToParse() {
    return;//by dxm 可能造成聊天切回卡顿，暂时注释数据打点，如果需要打开请确保在游戏退出时打开
    if(g_isSavedUserInfo || !(GlobalData::shared()->isInitFinish)) {
        return;
    }
    g_isSavedUserInfo = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //1. 获取activity静态对象
    JniMethodInfo minfo;
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    //jobject activityObj;
    if(!JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/ext/CppCallJava","gamescore","(Ljava/lang/String;)V"))
    {
        return;
    }
    char tmp[265] = {0};
    string msg = "{";
    tmp[sprintf(tmp, "\"name\":\"%s\",", GlobalData::shared()->playerInfo->name.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"uid\":\"%s\",", GlobalData::shared()->playerInfo->uid.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"level\":%d,", GlobalData::shared()->playerInfo->level)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"pic\":\"%s\",", GlobalData::shared()->playerInfo->pic.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"nickName\":\"%s\",", GlobalData::shared()->playerInfo->nickName.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"country\":%d,", GlobalData::shared()->playerInfo->country)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"roomName\":\"%s\",", GlobalData::shared()->playerInfo->roomName.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"allianceRank\":%d,", GlobalData::shared()->playerInfo->allianceRank)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"gold\":%ld,", GlobalData::shared()->playerInfo->gold)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"payTotal\":%ld,", GlobalData::shared()->playerInfo->payTotal)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"exp\":%ld,", GlobalData::shared()->playerInfo->exp)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"openedSystem\":\"%s\",", GlobalData::shared()->playerInfo->openedSystem.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"gmFlag\":%d,", GlobalData::shared()->playerInfo->gmFlag)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"renameTime\":%d,", GlobalData::shared()->playerInfo->renameTime)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"protectTimeStamp\":%lf,", GlobalData::shared()->playerInfo->protectTimeStamp)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"resourceProtectTimeStamp\":%lf,", GlobalData::shared()->playerInfo->resourceProtectTimeStamp)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"vipPoints\":%ld,", GlobalData::shared()->playerInfo->vipPoints)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"vipEndTime\":%ld,", GlobalData::shared()->playerInfo->vipEndTime)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"nextDayLoginVipReward\":%ld,", GlobalData::shared()->playerInfo->nextDayLoginVipReward)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"consecutiveLoginDays\":%d,", GlobalData::shared()->playerInfo->consecutiveLoginDays)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"isfirstJoin\":%d,", GlobalData::shared()->playerInfo->isfirstJoin)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"sciencePower\":%lf,", GlobalData::shared()->playerInfo->sciencePower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"battleLose\":%d,", GlobalData::shared()->playerInfo->battleLose)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"armyDead\":%d,", GlobalData::shared()->playerInfo->armyDead)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"armyPower\":%lf,", GlobalData::shared()->playerInfo->armyPower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"fortPower\":%lf,", GlobalData::shared()->playerInfo->fortPower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"armyCure\":%ld,", GlobalData::shared()->playerInfo->armyCure)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"questpower\":%lf,", GlobalData::shared()->playerInfo->questpower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"playerPower\":%lf,", GlobalData::shared()->playerInfo->playerPower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"armyKill\":%d,", GlobalData::shared()->playerInfo->armyKill)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"buildingPower\":%lf,", GlobalData::shared()->playerInfo->buildingPower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"defenseWin\":%d,", GlobalData::shared()->playerInfo->defenseWin)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"heroPower\":%lf,", GlobalData::shared()->playerInfo->heroPower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"attackLose\":%d,", GlobalData::shared()->playerInfo->attackLose)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"detectNum\":%d,", GlobalData::shared()->playerInfo->detectNum)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"cityDes\":%d,", GlobalData::shared()->playerInfo->cityDes)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"attackWin\":%d,", GlobalData::shared()->playerInfo->attackWin)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"battleWin\":%d,", GlobalData::shared()->playerInfo->battleWin)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"power\":%lf,", GlobalData::shared()->playerInfo->power)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"isApplied\":\"%s\",", GlobalData::shared()->playerInfo->isApplied ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"invited\":\"%s\",", GlobalData::shared()->playerInfo->invited ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"bindFlag\":\"%s\",", GlobalData::shared()->playerInfo->bindFlag ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"rank\":%d,", GlobalData::shared()->playerInfo->rank)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"pointId\":%d,", GlobalData::shared()->playerInfo->pointId)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"mainCityLv\":%d,", GlobalData::shared()->playerInfo->mainCityLv)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"officer\":\"%s\",", GlobalData::shared()->playerInfo->officer.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"relinquishFlag\":\"%s\",", GlobalData::shared()->playerInfo->relinquishFlag ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"relinquishEndTime\":%lf,", GlobalData::shared()->playerInfo->relinquishEndTime)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"isInAlliance\":\"%s\",", GlobalData::shared()->playerInfo->isInAlliance() ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"lastBattlePower\":%lf,", GlobalData::shared()->playerInfo->lastBattlePower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"battlePower\":%lf,", GlobalData::shared()->playerInfo->battlePower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"addPower\":%lf,", GlobalData::shared()->playerInfo->addPower)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"getTotalPower\":%lf,", GlobalData::shared()->playerInfo->getTotalPower())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"getPic\":\"%s\",", GlobalData::shared()->playerInfo->getPic().c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"getBodyPic\":\"%s\",", GlobalData::shared()->playerInfo->getBodyPic().c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"isChatView\":\"%s\",", GlobalData::shared()->playerInfo->isChatView ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"selfServerId\":%d,", GlobalData::shared()->playerInfo->selfServerId)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"currentServerId\":%d,", GlobalData::shared()->playerInfo->currentServerId)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"serverName\":\"%s\",", GlobalData::shared()->playerInfo->serverName.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"regCountry\":\"%s\",", GlobalData::shared()->playerInfo->regCountry.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"isInSelfServer\":\"%s\",", GlobalData::shared()->playerInfo->isInSelfServer() ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"isMOD\":\"%s\",", GlobalData::shared()->playerInfo->isMOD() ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"inviCode\":\"%s\",", GlobalData::shared()->playerInfo->inviCode.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"picVer\":%d,", GlobalData::shared()->playerInfo->picVer)] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"getCustomPicUrl\":\"%s\",", GlobalData::shared()->playerInfo->getCustomPicUrl().c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"isUseCustomPic\":\"%s\",", GlobalData::shared()->playerInfo->isUseCustomPic() ? "true" : "false")] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"analyticID\":\"%s\",", GlobalData::shared()->analyticID.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"platformUID\":\"%s\",", GlobalData::shared()->platformUID.c_str())] = '\0';
    msg.append(tmp);
    tmp[sprintf(tmp, "\"fromCountry\":\"%s\",", GlobalData::shared()->fromCountry.c_str())] = '\0';
    msg.append(tmp);

    int nBuildMainLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("FUN_BUILD_MAIN", 1);
    tmp[sprintf(tmp, "\"mainBuildLevel\":%d,", nBuildMainLevel)] = '\0';
    msg.append(tmp);

    std::string preferredLanguage = CCUserDefault::sharedUserDefault()->getStringForKey(KEY_PREFERRED_LANGUAGE, "");
    tmp[sprintf(tmp, "\"lang\":\"%s\"", preferredLanguage.c_str())] = '\0';
    msg.append(tmp);

    msg.append("}");
    //CCLOG("%s", msg.c_str());
    jstring jmsg = minfo.env->NewStringUTF(msg.c_str());
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jmsg);
    minfo.env->DeleteLocalRef(jmsg);
    minfo.env->DeleteLocalRef(minfo.classID);
#endif
}
#endif

void AppLibHelper::fbEventMainBuildingLevel(int level){
    int cacheLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey(CATCH_MAINBUILDING_LEVEL, 0);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(CATCH_MAINBUILDING_LEVEL, level);
    //无缓存的时候只有1级记录
    //有缓存的时候只有变化再记录
    if((cacheLevel == 0 && level == 1) || (cacheLevel != 0 && cacheLevel != level)){
        fbEventAchievedLevel(level);
        if(level == 6)
            sendAdjustTrack("reach_level_6");
    }
}


vector<std::string> AppLibHelper::getServiceTerms(int type){
    vector<std::string> serviceTerms = {
        "337 Technology Limited 게임 서비스 이용 약관",
        " ",
        "제 1 조 (목적)",
        "이 이용약관은 337 Technology Limited(이하 '회사')가 제공하는 모든 게임 및 제반 서비스의 이용과 관련하여 회원과 회사간의 가입 및 이용에 관한 제반 사항과 기타 필요한 사항을 구체적으로 규정함을 목적으로 합니다.",
        "제 2조 (용어의 정의)",
        "이 약관에서 사용하는 용어의 정의는 다음과 같습니다.",
        "1. '이용자'란 회사가 제공하는 모든 게임 및 제반 서비스를 이용하는 자(회원, 비회원 포함)를 말합니다.",
        "2. ‘회원’이라 함은 본 약관에 따라 회사와 이용계약을 체결하고 회사가 제공하는 계정를 부여 받은 이용자를 말합니다. ‘회원’의 종류는 아래와 같이 구분 됩니다.",
        "1) 일반회원 : 이용자가 입력한 E-mail(계정) 및 Password(비밀번호)를 사용하여 회사가 제공하는 서비스를 이용하는 자",
        "2) 게스트회원 : 이용자의 E-mail(계정) 및 Password(비밀번호)의 신청 없이, 회사가 랜덤하게 부여하는 계정을 통해 서비스를 이용하는 자. (단, 게스트회원은 계정, 비밀번호 정보를 받지 않기 때문에 디바이스(기기) 초기화 시 데이터도 초기화 됩니다.)",
        "3. '콘텐츠'란 회사가 제공하는 모든 게임 및 네트워크 서비스, 애플리케이션, 게임 머니 및 게임 아이템 등 서비스와 관련되어 디지털 방식으로 제작된 내용물 일체를 말합니다.",
        "4. ‘디바이스’란 콘텐츠를 다운로드 받거나 설치하여 사용할 수 있는 PC, 스마트폰, 태블릿, 등의 전자기기를 말합니다.",
        "5. ‘서비스’란 디바이스의 종류와 상관없이, 회사가 이용자에게 제공하는 네트워크 게임 이용에 관한 서비스 일체를 말합니다.",
        "6. \"애플리케이션\"이란 회사가 제공하는 서비스를 이용하기 위하여 본 조 제4항에서 설명한 디바이스를 통해 다운로드 받거나 설치하여 사용하는 프로그램 일체를 말합니다.",
        "7. \"오픈마켓사업자\"란 당사 게임을 설치하고 결제할 수 있도록 제공하는 오픈마켓 등 전자상거래 제공자 일체(게임 내 결제를 제공하는 사업자, 이동통신사 포함)를 제공하는 사업자를 말합니다. (예. 구글 플레이 앱스토어, 애플 앱스토어, 티스토어, 올레마켓, 유플러스 앱마켓 등)",
        "8. \"플랫폼사업자\"란 당사 게임을 알리거나 이용함에 있어서 회사와 제휴하여 서비스를 제공하는 사업자 및 관련 서비스 일체를 말합니다.",
        "9. ‘계정’이라 함은 서비스의 이용과 관련하여 회원 식별을 위하여 회원이 정하고 회사가 승인한 문자와 숫자의 조합을 말합니다.",
        "10. ‘캐시’라 함은 개별 애플리케이션 게임 내에서 사용되는 화폐로서, 회원이 구매/충전하여 각종 모바일앱게임 내 유료 서비스의 이용 및 콘텐츠, 상품의 구매 등에 사용할 수 있는 사이버 화폐를 말합니다.",
        "11. “In-App결제”란 회사가 서비스하는 애플리케이션 게임 내에서 다양한 아이템, 기능, 게임머니 등을 구매하기 위한 결제행위를 말합니다.",
        "12. 이 약관에서 사용하는 용어의 정의는 1항에서 정하는 것을 제외하고는 관계법령에서 정하는 바에 의합니다. 관계법령에서 정하지 않는 것은 일반적인 상관례에 의합니다.",
        "제3조 (약관의 효력과 변경)",
        "이 약관은 서비스 이용계약의 성격상 회사의 홈페이지 또는 서비스 이용을 위한 애플리케이션 내에 이 약관을 명시하고, 이용자가 회원가입 시 약관에 동의하거나, 회사가 제공하는 애플리케이션을 설치 및 실행하는 경우 효력이 발생하게 됩니다.",
        "1. 회사는 관련 법령의 변경이나 이용자의 권리 및 의무사항을 개선하기 위해 이 약관을 변경할 수 있으며, 변경된 약관은 적용 전 7일간(다만, 이용자의 권리∙의무에 중대한 영향을 미치는 사항에 대하여는 30일간) 홈페이지나, 제공하는 애플리케이션 등을 통해 이용자에게 고지하고 적용 일부터 효력이 발생됩니다.",
        "2. 이용자는 회사의 홈페이지를 방문하거나 애플리케이션 등을 확인하여 약관의 변경에 대하여 수시로 확인할 주의의무가 있으며, 변경된 약관에 대해 동의하지 않을 권리가 있습니다.",
        "3. 이용자가 변경된 약관에 동의하지 않을 경우, 본 이용계약을 해지할 수 있습니다. 다만, 이용자가 제1항의 방법 등으로 별도 고지한 바에 따라 변경된 약관의 적용일로부터 15일 이내에 회사에 대해 \"거부\"의 의사표시를 하지 아니하는 경우에는 변경된 약관에 동의한 것으로 간주합니다.",
        "제4조 (약관 이외의 준칙)",
        "이 약관에서 정하지 않은 사항은 회사가 정한 개별 서비스 이용약관 및 정보통신망 이용촉진 및 정보보호 등에 관한 법률, 전자상거래 등에서의 소비자보호에 관한 법률 등 관계법령에서 정하는 바에 따르며 개별 서비스 이용약관 및 관계법령에서 정하지 않는 것은 일반적인 상관례에 따릅니다.",
        "제5조 (이용 계약의 성립)",
        "1. 이용계약은 회원의 이 약관 내용에 대한 동의와 이용신청에 대하여 회사가 이용 승낙을 함으로써 성립합니다.",
        "2. 이 약관에 대한 동의는 이용신청 당시 해당 이용약관 동의 신청 여부에 동의 함으로써 이 약관에 동의하는 것으로 간주됩니다.",
        "3. 본 조 제1항에 따른 신청에 있어 회사는 이용자에게 전문기관을 통한 실명확인 및 본인인증을 요청할 수 있습니다.",
        "4. 이용자는 각 오픈마켓의 약관 및 정책에 따라 회사가 제공하는 애플리케이션을 다운로드 받아 이용 할 수 있습니다. 이용자와 각 오픈마켓사업자 간의 거래 또는 분쟁 등에 대하여는 각 오픈마켓사업자의 약관 및 정책이 적용되며, 회사는 이용자와 각 오픈마켓사업자 간의 거래 또는 분쟁에 개입하지 않으며, 이용자의 오픈마켓 이용과 관련하여 어떠한 책임도 부담하지 않습니다.",
        "제6조 (이용신청에 대한 승낙)",
        "1. 회사는 이용자의 이용신청에 대하여 업무상 또는 기술상의 문제가 없는 경우 승낙함을 원칙으로 합니다. 단, 회사는 다음 각 호에서 정하는 경우에는 승낙을 하지 않거나 승낙을 취소할 수 있습니다.",
        "1) 허위 또는 타인의 정보를 기재하거나 회사가 제시하는 양식에 필요한 정보를 기재하지 않는 경우",
        "2) 사회 안녕과 질서 또는 미풍양속을 저해하거나 저해할 목적으로 신청한 경우",
        "3) 부정한 용도로 서비스를 이용하고자 하는 경우",
        "4) 영리를 추구할 목적으로 서비스를 이용하고자 하는 경우",
        "5) 이 약관에서 규정한 사항을 위반하여 신청한 경우",
        "2. 회사는 다음 각 호의 경우에 그 원인이 해소될 때까지 승낙을 보류할 수 있습니다.",
        "1) 서비스 관련 설비에 여유가 없는 경우",
        "2) 업무상 또는 기술상 서비스를 제공하지 못할 장애 사항이 발생한 경우",
        "3) 최근 1개월 내 해지기록이 있고 회원가입을 재신청하려는 경우",
        "4) 기타 ‘회원’으로서 부적절한 행위를 할 우려가 있다고 인정되는 경우",
        "제7조 (회사의 의무)",
        "1. 회사는 이용자로부터 제기되는 의견이나 불만이 정당하다고 객관적으로 인정될 경우에는 합리적인 기간 내에 신속하게 처리하여야 합니다. 다만, 처리에 장기간이 소요되는 경우에는 이용자에게 그 사유와 처리일정을 공지사항으로 공지 합니다.",
        "2. 회사는 이용자의 계정정보를 포함한 일체의 개인정보가 회사가 관리하는 서비스 시스템으로부터 유출되지 않도록 하며, 제3자에게 공개 또는 제공되지 아니하도록 보호합니다.",
        "3. 회사는 계속적이고 안정적인 서비스의 제공을 위하여 서비스 개선을 하던 중 설비에 장애가 생기거나 데이터 등이 멸실된 때에는 천재지변, 비상사태, 해결이 곤란한 기술적 결함 등 부득이한 사유가 없는 한 지체 없이 이를 수리 또는 복구하도록 최선의 노력을 다합니다.",
        "4. 회사는 이용계약의 체결, 계약사항의 변경 및 해지 등 이용자와의 계약관련 절차 및 내용 등에 있어 이용자에게 편의를 제공하도록 노력합니다.",
        "5. 회사는 개인정보 보호를 위해 개인정보취급방침 공시하고 준수합니다.",
        "제8조 (이용자의 의무)",
        "1. 이용자는 회사에서 제공하는 서비스를 게임 서비스 본래의 이용목적 이외의 용도로 사용하거나 다음에 해당하는 행위를 해서는 안됩니다.",
        "1) 고객 문의, 유료콘텐츠 복구 및 환불요청, 이벤트 당첨 등으로 인해 회사에 개인정보 제공 시 실명이 아닌 정보 또는 다른 사람의 정보를 사용하거나, 허위 사실 기재하는 행위",
        "2) 타인으로 가장하거나 타인과의 관계를 허위로 명시하는 행위, 다른 이용자의 계정 및 비밀 번호를 도용, 부정하게 사용하거나, 타인의 신용카드, 유/무선전화, 은행 계좌 등을 무단으로 도용하여 유료콘텐츠를 구매하는 행위",
        "3) 회사가 제공하지 않는 서비스를 통해 콘텐츠 등을 타인과 거래하거나 매매하는 행위",
        "4) 회사의 서비스 및 제공된 애플리케이션을 이용하여 얻은 정보를 회사의 사전 승낙 없이 복제, 유통, 조장하거나 상업적으로 이용, 또한 알려지거나 알려지지 않은 버그를 악용하여 서비스를 이용하는 행위.",
        "5) 회사의 서비스 및 제공된 애플리케이션을 이용하여 자기 또는 타인에게 재산상의 이익을 발생시키는 행위",
        "6) 타인의 명예를 훼손하거나 손해를 가하는 행위",
        "7) 회사의 지적재산권, 제3자의 지적재산권, 초상권 등 기타 권리를 침해하거나 회사의 승인을 받지 않고 다른 이용자의 개인정보를 수집, 저장, 유포, 게시하는 행위",
        "8) 제3자를 기만하여 이득을 취하거나 회사가 제공하는 서비스를 불건전하게 이용하거나 하여, 제3자에게 피해를 주는 행위",
        "9) 음란, 저속한 정보를 교류, 게재하거나 음란사이트를 연결(링크)하거나 승인되지 않은 광고 및 홍보물 게재하는 행위",
        "10) 재물을 걸고 도박하는 등 사행 행위를 유도하거나 참여하는 행위",
        "11) 수치심이나 혐오감 또는 공포심을 일으키는 말이나 음향, 글이나 화상 또는 영상을 상대방에게 전송, 도달, 유포하는 행위",
        "12) 관련 법령에 의하여 그 전송 또는 게시가 금지되는 정보(컴퓨터프로그램) 또는 컴퓨터소프트웨어, 하드웨어, 전기통신 장비의 정상적인 가동을 방해, 파괴할 목적으로 고안된 소프트웨어 바이러스, 기타 다른 컴퓨터 코드, 파일, 프로그램을 포함하고 있는 자료를 전송, 게시, 유포, 사용하는 행위",
        "13) 회사의 애플리케이션을 회사에 동의 없이 임의로 변경 또는 변조하거나, 불법 변조한 애플리케이션을 유포 및 사용하는 행위",
        "14) 회사의 직원이나 운영자를 가장하거나 사칭하거나 또는 타인의 명의를 도용하여 글을 게시하거나 메일을 발송하는 행위",
        "15) 회사의 사전 승낙 없이 서비스를 이용하여 영업활동을 하는 행위 (영업활동의 결과 및 약관에 위반한 영업활동을 하여 발생한 결과에 대한 책임은 회원에게 있으며, 회원은 이와 같은 영업활동으로 회사에 손해를 끼친 경우, 회원은 회사에 대해 손해배상의무를 집니다.)",
        "16) 회사의 명시적 동의가 없이 서비스의 이용권한, 기타 이용계약상의 지위를 타인에게 양도, 증여, 담보로 제공하는 행위",
        "17) 기타 공공질서 및 미풍양속을 위반하거나 불법적, 부당한 행위 및 관계법령에 위배되는 행위",
        "2. 이용자는 회사(게임) 공지 사항 및 이용약관의 수정사항을 수시로 확인하여야 합니다.",
        "제9조 (서비스 이용 시간)",
        "1. 회사는 업무상 또는 기술상 특별한 지장이 없는 한 연중무휴 1일 24시간 서비스 제공을 원칙으로 합니다. 다만, 시스템 정기점검, 서버의 증설 및 교체, 새로운 게임 내용의 추가, 각종 버그 패치, 새로운 서비스로의 교체 등 운영상 필요한 경우, 일정기간 동안 서비스를 일시 중지시킬 수 있으며, 이러한 경우 회사는 그 내용 및 시간을 회사 홈페이지나 애플리케이션 내에 공지합니다. 다만, 회사가 사전에 통지할 수 없는 부득이한 사유가 있는 경우 사후에 통지할 수 있습니다.",
        "2. 본 조 제1항에도 불구하고 회사의 긴급하고도 부득이한 사유로 인해 예고 없이 일시적으로 서비스가 정지될 수 있으며 이 경우에는 사후에 이를 공지할 수 있습니다.",
        "3. 회사는 서비스의 제공에 필요할 경우 정기점검을 실시할 수 있으며 정기점검 시간은 회사의 홈페이지나 애플리케이션에 공지하는 바에 의합니다.",
        "4. 회사는 서비스를 특정 단위로 구분하여 각 개별 서비스 이용시간을 다르게 운영할 수 있으며 이러한 사항은 사전에 공지합니다.",
        "제10조 (서비스 내용 및 변경)",
        "1. 회사는 새로운 게임 내용, 각종 버그 패치 등 서비스의 운영상 또는 기술상의 필요한 경우, 제공하고 있는 서비스의 전부 또는 일부를 상시적으로 수정, 추가, 폐지 등 변경할 수 있습니다. 변경될 서비스의 내용 및 제공일자 등에 대해서는 홈페이지나 애플리케이션을 통하여 통지합니다.",
        "2. 회사는 회원에게 서비스 운영상 및 기술상 필요한 다음 각 호의 서비스를 제공합니다.",
        "1) 회사는 원활한 게임 환경 제공을 위해 백그라운드 데이터 기능을 제공합니다. 백그라운드 데이터 기능 이용 시 데이터 요금이 발생될 수 있습니다.",
        "3. 회사는 서비스의 기획이나 운영상 또는 회사의 긴박한 상황 등에 의해 서비스 전부를 중단할 필요가 있는 경우 홈페이지나 애플리케이션 내 이를 공지하고 서비스의 제공을 중단할 수 있습니다. 이용자는 서비스 종료 시 사용 기간이 남아 있지 않은 유료콘텐츠에 대하여 환불을 요청할 수 없습니다.",
        "4. 회사는 다음 각호에 해당하는 경우 서비스의 전부 또는 일부를 제한하거나 중지할 수 있습니다.",
        "1) 전시, 사변, 천재지변 또는 국가비상사태 등 불가항력적인 사유가 있는 경우",
        "2) 정전, 제반설비의 장애 또는 이용량의 폭주 등으로 정상적인 서비스 이용에 지장이 있는 경우",
        "3) 서비스용 설비의 보수 등 공사로 인한 부득이한 경우",
        "4) 회사의 제반 사정(경영상의 이유 등)으로 서비스를 할 수 없는 경우",
        "5. 제3항에 의한 서비스 중단의 경우에는 회사가 제공하는 홈페이지나 애플리케이션 내에 게시하여 통지합니다. 다만, 회사가 통제할 수 없는 사유로 서비스의 중단이 발생하여 사전 통지가 불가능한 경우에는 그러하지 아니합니다.",
        "6. 회사는 서비스가 변경되거나 중지된 원인이 회사의 고의 또는 중과실로 인한 경우를 제외하고는 서비스의 변경 및 중지로 발생하는 문제에 대해서 책임을 지지 않습니다.",
        "제 11조 (유료 콘텐츠의 구매, 사용기간 및 이용)",
        "1. 이용자는 서비스를 사용하고 있는 단말기의 종류에 따른 각 오픈마켓사업자의 결제 운영정책에 따라 In-App결제를 통해 유료콘텐츠를 구매할 수 있습니다. (단, 해당 결제 정책의 차이로 인해 결제금액의 차이가 발생할 수 있습니다.) 또한 유료콘텐츠의 구매 대금은 오픈마켓사업자와 연계된 이동통신사나 플랫폼사업자 등이 정하는 방법 및 정책에 따라 부과되며, 납부방식 역시 해당 사업자의 정책을 따릅니다.",
        "2. 게임 서비스 내에서 In-App결제를 통해 이용자가 구매한 유료 콘텐츠는 해당 게임 서비스 애플리케이션을 다운로드 받거나 설치한 단말기에서만 이용할 수 있습니다.",
        "3. 이용자가 In-App결제를 통해 구매한 유료콘텐츠의 사용기간은 기본적으로 1년이며 이 기간이 경과한 후에는 이용자는 해당 유료콘텐츠에 대한 사용권을 상실합니다. 단, 사용기간이 별도로 명시된 유료콘텐츠의 경우는 구매 시 명시된 사용 기간에 따릅니다. 이용자는 회사가 정하여 별도로 고지한 방법 이외에는 유료 콘텐츠를 이용자 본인의 계정에서만 이용할 수 있으며, 제 3자에게 양도, 대여, 매매할 수 없습니다.",
        "제12조 (대금결제)",
        "1. In-App결제를 통해 구매한 콘텐츠에 대한 대금은 원칙적으로 이동통신사와 각 오픈마켓 등에서 정하는 정책, 방법 등에 따라 부과되며 납부 방법 역시 정해진 방법에 따라 납부해야 합니다. 단, 회사 및 결제업체(이동통신사, 오픈마켓 등)의 정책, 정부의 방침 등에 따라 각 결제수단별로 한도가 부여 또는 조정될 수 있습니다.",
        "2. 이용자가 단말기 및 오픈마켓의 비밀번호 설정 기능 등을 이용하지 않거나 부주의하게 노출하여 발생하는 제3자의 결제에 대하여는 회사가 어떠한 책임도 부담하지 않습니다.",
        "3. 이용자가 이동통신사에서 제공하는 청소년 요금제 등에 가입한 경우, 해당 단말기에서의 In-App결제는 법정대리인의 동의가 있는 것으로 간주됩니다.",
        "4. 이용자는 In-App결제 대금을 성실히 납부하여야 할 책임이 있습니다.",
        "5. 캐시형 아이템의 구매 또는 사용내역에 대해 확인은 회사로 문의 주시면 답변 받으실 수 있습니다.",
        "제13조 (이벤트 경품 및 상금)",
        "1. 회원이 회사에 제공한 개인정보에 허위로 기재한 사항 및 불법 적인 방법을 사용하여 이벤트에 참여 하는 경우 경품이나 상금을 지급하는 이벤트에 당첨되더라도 그 사실이 발견된 시점에서 취소될 수 있습니다.",
        "2. 회사는 별도로 정한 기준에 따라 제세공과금의 원천징수 등의 절차를 마친 뒤에 경품 또는 상금을 지급합니다.",
        "3. 해당 이용자가 만 20세 미만인 경우 부모님(법정대리인)의 동의를 받은 뒤에 경품을 지급합니다.",
        "4. 회사의 귀책 사유가 없이, 이벤트 당첨자 발표 후 1개월이 지나도 해당 이용자가 경품 또는 상품을 수령하지 않으면 이벤트 당첨을 취소할 수 있습니다.",
        "5. 경품이나 상금 배송을 위하여 개인정보를 수집 하는 경우 회사의 개인정보취급방침에 따릅니다.",
        "제14조 (광고에 대한 동의 등)",
        "1. 회사는 홈페이지 또는 애플리케이션 게임 내 개별 서비스에 광고를 게재할 수 있으며, 이용자의 본 약관에 대한 동의는 홈페이지 또는 서비스 이용 시 광고의 노출에 대한 동의를 포함합니다.",
        "2. 회사가 제공하는 제3자가 주체인 제1항의 광고에 이용자가 참여하거나 교신 또는 거래를 함으로써 발생하는 손실과 손해에 대해서는 회사가 책임을 지지 않으며, 이용자의 책임으로 합니다.",
        "3. 회사는 이용자의 이용신청 시에 SMS, 전자우편 등을 통한 정보수신에 동의하는 경우 이용자에게 홈페이지 및 서비스에 대한 정보를 제공합니다. 이용자는 홈페이지 또는 회사의 고객센터를 통하여 언제라도 정보수신 동의에 대한 의사표시를 철회할 수 있습니다.",
        "제15조 (캐시 및 포인트)",
        "1. 회원이 보유하고 있는 캐시 중 In-App결제를 통해 구매한 것이 아닌, 게임을 진행하면서 획득하거나, 이벤트로 지급하는 ‘캐시’에 경우 무료캐시라 정의합니다.",
        "2. 무료캐시와는 별도로 회사는 회원에게 무료 포인트(마일리지)를 제공할 수 있으며, 이를 “무료 포인트”라 정의 합니다.",
        "3. 획득한 무료 캐시 및 무료 포인트는 유효기간, 사용범위 등을 별도로 공지합니다.",
        "4. 무료 캐시 및 무료 포인트의 경우, 사용범위가 제한 될 수 있으며, 회원이 유료로 구매한 캐시와 무료캐시 및 무료 포인트를 함께 보유하고 있는 경우에는 무료 캐시 및 무료포인트가 우선 순위로 차감되며 그 이후 캐시가 차감됩니다.",
        "5. 무료캐시 및 무료포인트는 환불 또는 보상의 대상이 되지 않습니다.",
        "제16조 (청약 철회 및 미성년자 결제 취소)",
        "1. 이용자가 구매한 유료콘텐츠의 경우에는 해당 유료콘텐츠를 구매한 오픈마켓 사업자 또는 회사를 대상으로, 청약철회(구매취소)를 할 수 있습니다.",
        "2. 본 조 제1항에 따라 청약철회에 있어 오픈마켓 사업자를 대상으로 신청하는 경우, 해당 오픈마켓의 결제 정책에 따라 청약 철회절차가 진행 됩니다.",
        "3. 본 조 제1항에 따라 청약철회에 있어 회사를 대상으로 신청하는 경우, 구매일 또는 유료콘텐츠 이용가능일로부터 7일 이내에 청약철회를 신청해야 합니다. 단, 애플리케이션에서 판매되는 유료콘텐츠의 내용이 표시•광고 내용과 다르거나 계약 내용과 다르게 이행된 경우, 이용자는 해당 유료콘텐츠의 구매일로부터 3개월 이내 청약철회가 가능하고, 유료콘텐츠와 표시 내용의 상이함이나 하자 등이 있음을 알았거나 알 수 있었던 날로부터 30일 이내에 청약철회가 가능합니다.",
        "4. 선물 및 이벤트 등 회사나 제3자로부터 무상으로 제공받은 유료콘텐츠, 청약철회 요청 당시 이미 사용하였거나 사용한 것으로 간주되는 유료콘텐츠 등 이에 준하는 특성을 가진 일부 유료콘텐츠에 대하여는 관련 법령에 따라 청약철회(구매취소)가 제한될 수 있습니다. 이 경우 회사는 이용자가 청약철회(구매취소)가 제한되는 유료콘텐츠 구매 시 해당 유료콘텐츠에 대하여 이용자에게 고지하는 등 관련 법령에서 정한 바에 따른 조치를 취하기로 합니다.",
        "5. 각 애플리케이션에서 판매되는 유료콘텐츠를 미성년자가 법정대리인의 동의 없이 구매한 경우, 미성년자 또는 법정대리인은 In-App결제를 취소할 수 있습니다. 단, 미성년자의 In-App결제가 법정대리인으로부터 처분을 허락 받은 재산의 범위 내인 경우 또는 미성년자가 사술 등을 사용하여 성년자로 믿게 한 때에는 취소가 제한됩니다. 유료콘텐츠 구매자가 미성년자인지 여부는 In-App결제가 진행된 단말기 또는 신용카드 등 결제수단의 명의자를 기준으로 판단됩니다.",
        "6. 다음과 같은 경우 유료콘텐츠의 청약철회가 제한되며 회사는 청약철회가 제한되는 유료콘텐츠에 대해서 결제 전에 청약철회가 제한됨을 표시합니다.",
        "1) 구매 후 즉시 사용이 시작되거나 즉시 애플리케이션에 적용되는 아이템의 경우",
        "2) 애플리케이션의 정상적인 이용과정에서 결제 없이 획득한 아이템의 경우",
        "3) 추가적인 혜택이 제공되는 아이템에서 해당 추가 혜택이 사용된 경우",
        "4) 묶음형(패키지)으로 판매된 아이템의 일부가 사용된 경우",
        "5) 개봉행위를 사용으로 볼 수 있거나 개봉 시 효용이 결정되는 확률형 아이템의 경우",
        "제17조 (환불신청 및 절차)",
        "1. 환불은 서비스를 사용하고 있는 단말기의 운영체제 종류에 따라 각 오픈마켓사업자의 환불 운영정책에 따라 진행됩니다.",
        "2. 이용자가 실제 정상적인 구매내역이 기록되는 이용대금의 결제를 통하지 않고 게임 서비스 중에 보상으로 취득하거나, 회사가 내부 이벤트 혹은 외부 제휴 이벤트 등을 통하여 지급한 유료 콘텐츠는 환불하지 않습니다.",
        "3. 이용자가 오픈마켓 사업자가 아닌 회사를 상대로 청약철회 및 환불 등을 요구할 경우에는 회사는 이용자로부터 별도의 개인정보 취급 동의 과정을 거친 후 구매내역 확인에 필요한 정보를 고객으로부터 수령하고, 플랫폼사업자 또는 오픈마켓 사업자를 통해 구매내역을 확인하는 절차를 거친 다음 청약철회 및 환불 절차가 진행됩니다. 회사는 이 과정 중에서 이용자의 정당한 철회 사유를 확인하기 위해 필요 시 이용자에게서 제공받은 정보를 통해 이용자에게 연락하여 정확한 사실 확인을 할 수 있으며, 추가적으로 증빙을 요구할 수 있습니다.",
        "4. 미성년자 결제취소를 요청하시는 경우 회사의 필요에 따라 미성년자 및 법정대리인을 증명할 수 있는 서류를 제출하여야 합니다.",
        "5. 애플리케이션을 통한 결제는 오픈마켓사업자가 제공하는 결제방식에 따릅니다. 따라서 결제 과정에서 과오금이 발생하는 경우 원칙적으로 오픈마켓사업자에게 환급을 요청하여야 합니다. 단, 오픈마켓사업자의 정책, 시스템에 따라 가능한 경우 회사가 오픈마켓사업자에게 필요한 환급절차의 이행을 요청할 수도 있습니다.",
        "6. 선물하기 기능을 통하여 이루어진 유료콘텐츠 결제에 대하여는 구매한 유료콘텐츠에 하자가 있는 경우를 제외하고는 원칙적으로 결제 취소 및 환급이 불가하며, 유료콘텐츠의 하자로 인한 환급은 선물을 보낸 이용자에 한하여 가능합니다.",
        "7. 회사는 이용자로부터 환불에 필요한 관련 서류를 받은 날로부터 최대한 조속한 시일 내에 환불을 완료하도록 노력합니다.",
        "제18조 (계약 해지 및 서비스 이용 제한 등)",
        "1. 이용자는 언제든지 서비스 이용을 원하지 않는 경우 회원탈퇴를 통해 계약을 해지할 수 있습니다. 탈퇴는 즉시 처리되며 탈퇴 시 이용자가 보유한 콘텐츠 정보는 모두 삭제되어 복구가 불가능합니다.",
        "2. 이용자가 다음 각 호의 사유에 해당하는 행위를 한 경우, 회사는 사전통보 없이 이용계약을 해지하거나 또는 기간을 정하여 서비스 이용을 제한 할 수 있습니다.",
        "1) 서비스 신청 시에 허위 내용을 등록하거나 타인의 서비스 계정 및 비밀번호, 결제 정보 등을 도용한 경우",
        "2) 서비스 운영을 고의로 방해하거나 한 경우 또는 안정적 운영을 방해할 목적으로 다량의 정보를 전송하거나 광고성 정보를 전송하는 경우",
        "3) 정보통신설비의 오작동이나 정보 등의 파괴를 유발시키는 컴퓨터 바이러스 프로그램 등을 유포하는 경우",
        "4) 타인의 명예를 손상시키거나 불이익을 주는 행위를 한 경우",
        "5) 회사 및 다른 회원 또는 타인의 지적재산권을 침해하는 경우",
        "6) 정보통신윤리위원회 등 회부기관의 시정요청을 하는 경우",
        "7) 회사의 서비스 정보를 이용하여 얻은 정보를 회사의 사전 승낙 없이 복제 또는 유통시키거나 상업적으로 이용하는 경우 또는 회사의 서비스를 사칭하여 메시지 등을 발송한 경우",
        "8) 음란물을 게재하거나 음란사이트를 링크하는 경우",
        "9) 제8조 이용자의 주요한 의무 항목을 위배하여 회사의 서비스에 지장을 초래한 경우 및 기타 이에 준하는 사항",
        "3. 전항의 규정에 따라 회사가 이용계약을 해지하거나 중단하는 경우 이용자는 게임 서비스 로그아웃 및 다운로드 받은 애플리케이션을 삭제하여야 합니다.",
        "제19조 (개인정보의 보호 및 사용)",
        "1. 회사는 관계 법령이 정하는 바에 따라 회원 등록정보를 포함한 회원의 개인정보를 보호하기 위해 노력합니다. 회원 개인정보의 보호 및 사용에 대해서는 관련 법령 및 회사의 개인정보취급방침에 따릅니다.",
        "2. 회사는 서비스 개선 및 회원 대상 서비스 소개 등을 위한 목적으로 회원 개인에 대한 추가정보를 요구할 수 있으며, 동 요청에 대해 회원은 승낙하여 추가정보를 제공하거나 거부할 수 있습니다.",
        "제20조 (게시물의 관리)",
        "1. 회사는 이용자가 작성 또는 게시한 게시물을 관리상의 필요에 따라 사전 통지 없이 사이트 내에서 이동시킬 수 있으며, 회사의 시스템 상 저장용량의 초과 등 불가피한 사유가 있는 경우 사전 통지 없이 게시물을 삭제할 수 있습니다.",
        "2. 이용자의 게시물에 대한 책임은 이용자 개인의 책임이며 제3자의 권리를 침해하는 내용 또는 방법으로 게시물을 게시하여서는 아니 됩니다. 만약 회원이 게시한 게시물이 제3자의 권리를 침해하였음을 이유로 회사에 제3자가 이의, 항의 등을 제기한 경우 회사는 관련법령에서 정한 바에 따라 필요한 임시조치를 취할 수 있으며 회원에게 그 사실을 통지합니다.",
        "3. 이용자가 게시한 게시물이 제3자의 권리를 침해하였음을 이유로 회사가 손해배상청구를 당하는 등 법적 문제가 발생한 경우 이용자는 회사의 면책을 위하여 필요한 모든 협력을 제공하여야 하며, 회사에 귀책사유가 없는 한 이용자는 그로 인하여 발생한 모든 문제에 대하여 책임을 부담하여야 합니다.",
        "4. 회사는 다음 각 호에 해당하는 게시물이나 자료는 임의로 삭제하거나 이동 또는 등록 거부를 할 수 있습니다.",
        "1) 다른 회원 또는 제3자를 비방하거나 중상모략으로 명예를 손상시키는 내용인 경우",
        "2) 공공질서 및 미풍양속에 위반되는 내용인 경우",
        "3) 회원 계정 또는 포인트 매매에 관련된 내용인 경우",
        "4) 영리를 목적으로 하는 광고일 경우",
        "5) 범죄적 행위와 결부된다고 인정되는 내용일 경우",
        "6) 다른 회원 또는 제 3자의 저작권 등 기타 권리를 침해하는 내용인 경우",
        "7) 회사에서 규정한 게시물 원칙에 어긋나거나, 게시판 성격에 부합하지 않는 경우",
        "8) 회사나 서비스의 정상적인 운영을 방해하는 경우",
        "9) 범죄적 행위에 결부된다고 판단되는 경우",
        "10) 승인되지 않은 광고 및 홍보물을 게재하는 경우",
        "11) 동일한 내용을 중복하여 다수 게시하는 등 게시의 목적에 어긋나는 경우",
        "12) 불법복제나 해킹 등을 조장하는 내용",
        "13) 기타 관계법령에 위배된다고 판단되는 경우",
        "제21조 (면책)",
        "1. 회사는 전시, 사변, 천재지변, 국가비상사태, 해결이 곤란한 기술적 결함 기타 불가항력적 사유로 서비스를 제공할 수 없는 경우에는 책임이 면제됩니다.",
        "2. 회사는 이용자의 귀책사유로 인한 서비스의 중지/이용장애에 대하여 책임을 지지 아니하며, 회사는 기간 통신 사업자가 전기통신서비스를 중지하거나 정상적으로 제공하지 아니하여 이용자에게 손해가 발생한 경우에는 책임이 면제됩니다.",
        "3. 회사는 사전에 공지되거나 긴급하게 실시된 서비스용 설비의 보수, 교체, 정기점검, 공사 등 부득이한 사유로 서비스가 중지되거나 장애가 발생한 경우에 대해서는 책임이 면제됩니다.",
        "4. 회사는 이용자가 서비스를 이용하여 기대하는 점수, 순위 등을 얻지 못한 것에 대하여 책임을 지지 않으며 서비스에 대한 취사 선택 또는 이용으로 발생하는 손해 등에 대해서는 책임이 면제됩니다.",
        "5. 회사는 이용자가 본인의 개인정보 등(계정 포함)을 변경하여 얻는 불이익 및 정보상실에 대해서는 일체 책임을 지지 않습니다.",
        "6. 회사는 이용자의 단말기 환경으로 인하여 발생하는 제반 문제 또는 회사의 귀책사유가 없는 네트워크 환경으로 인하여 발생하는 문제에 대해서 책임을 지지 않습니다.",
        "7. 회사는 이용자 상호간 또는 이용자와 제3자 간에 서비스를 매개로 발생한 분쟁에 대해 개입할 의무가 없으며 이로 인한 손해를 배상할 책임도 없습니다.",
        "8. 회사가 제공하는 서비스 중 무료 서비스 및 콘텐츠의 경우에는 손해 배상의 대상에서 제외됩니다. 다만, 회사의 고의 또는 중대한 과실로 인하여 발생한 손해의 경우는 제외합니다.",
        "9. 회사는 이용자가 서비스 내 또는 홈페이지 상에 게시 또는 전송한 정보, 자료, 사실의 신뢰도, 정확성 등 내용에 대해서는 책임을 지지 않습니다.",
        "10. 회사는 라이선스가 한국으로 제한되어 있는 기능과 컨텐츠를 서비스로 제공하며 타 국가의 서비스와 동일하게 서비스를 제공할 책임이 없으며 카카오㈜ 정책으로 제한되는 기능과 컨텐츠는 서비스에서 제한될 수 있습니다.",
        "제22조 (손해배상 등)",
        "이용자가 본 약관의 규정을 위반함으로 인하여 회사에 손해가 발생하게 되는 경우, 이 약관을 위반한 이용자는 회사에 발생하는 모든 손해를 배상하여야 합니다.",
        "제23조 (재판권 및 준거법)",
        "1. 서비스 이용과 관련하여 회사와 이용자간에 발생한 분쟁에 대하여는 양 당사자 간의 합의에 의해 원만히 해결하여야 합니다.",
        "2. 만약 제1항의 분쟁이 원만히 해결되지 않는 경우, 콘텐츠 산업 진흥법에 따라 콘텐츠분쟁조정위원회에 분쟁조정을 신청할 수 있으며, 소송이 제기된 경우는 관련 법령에 정한 절차에 따른 법원을 관할 법원으로 합니다.",
        "3. 회사와 이용자간에 제기된 소송에는 대한민국 법을 적용합니다.",
        " ",
        "본 이용약관은 2015년 3월 1일부터 시행됩니다."
    };
    vector<std::string> personalTerms = {
        "\"337 Technology Limited\"는 (이하 '회사'는) 회원님의 개인정보를 중요시하며, \"개인정보 보호법\", \"정보통신망 이용촉진 및 정보보호\"에 관한 법률 등 관련 법규들을 준수하고 있습니다. 회사는 개인정보취급방침을 통하여 회원님께서 제공하시는 개인정보가 어떠한 용도와 방식으로 이용되고 있으며, 개인정보보호를 위해 어떠한 조치가 취해지고 있는지 알려드립니다.",
        "개인정보취급방침은 다음과 같은 내용을 담고 있습니다.",
        "제1조 수집하는 개인정보 항목 및 수집방법",
        "회사는 원활한 서비스 제공 및 고객상담, 각종 데이터 통계 등을 위해 다음과 같이 회원님의 개인정보를 수집하고 있습니다.",
        "1. 수집항목",
        "- 게임 이용기록, 접속 로그, 결제기록(회원이 구매한 아이템 아이디, 아이템 가격, 마켓 주문 번호), 게임버전, 단말기 정보(모델명, OS 종류 및 버전 등)",
        "2. 수집방법",
        "- 홈페이지, 서면양식, 팩스, 전화, E-mail, 이벤트 응모, 배송요청",
        "- 협력회사로부터의 제공",
        "- 계정 생성정보 툴을 통한 수집",
        " ",
        "제2조 개인정보의 수집 및 이용목적",
        "회사는 수집한 회원님의 개인정보를 다음의 목적과 같이 사용하며 이용자의 동의 없이는 해당 범위 밖으로 이용하거나 사용하지 않습니다.",
        "단, 이용자가 사전에 개인정보 공개에 대하여 동의한 경우나 관련 법규에 의한 경우 또는 수사기관의 정보제공 요청에 의한 경우에는 외부에 공개합니다.",
        "1) 회원 가입 시 수집하는 개인정보의 종류 및 이용목적",
        "- 종류 : E-mail(계정) ",
        "- 목적 : 회원 중복가입, 고객상담 및 이벤트 안내, 고지사항, 불량회원 제재.",
        "2) 어플리케이션 게임 이용 시 수집하는 개인정보의 종류 및 이용 목적",
        "- 종류 : 단말기 정보(모델명, OS종류 및 버전 등), 게임이용 및 접속로그, 게임버전",
        "- 목적 : 회원의 서비스 이용 내역 관리, 신규서비스 개발, 통계학적 특성에 따른 서비스 제공 및 광고의 게재, 서비스 유효성 확인, 이벤트 참여기회 제공, 접속빈도 파악, 고객의 서비스 이용에 대한 통계, 불량이용자 이용제한 등.",
        "3) 이벤트 운영시 수집되는 개인정보의 종류 및 이용목적",
        "- 종류 : 핸드폰, E-mail, 주소",
        "- 목적 : 이벤트 당첨 경품 배송/청소년 당첨 여부 확인",
        "4) 유료서비스 이용 시 수집되는 개인정보의 종류 및 이용목적",
        "- 종류 : 결제기록(회원이 구매한 아이템 아이디, 아이템 가격, 마켓 주문 번호)",
        "- 목적 : 결제 내역 관리/ 고객상담, 청약취소, 미충전 확인 등 고객 문의 요청 대응.",
        "제3조 수집한 개인정보의 공유 및 제공",
        "회사는 회원의 개인정보를 본 정책에서 고지한 범위 내에서 사용하며, 외부에 제공하지 않습니다. 다만 아래의 경우는 예외로 합니다.",
        "1) 전기통신기본법, 전기통신사업법 등 관계 법령의 규정에 의거하거나, 수사목적으로 법령에 정해진 절차와 방법에 따라 수사기관의 요구가 있는 경우",
        "2) 통계작성, 학술 연구 또는 시장조사를 위하여 필요한 경우로서, 특정 개인을 알아볼 수 없는 형태로 가공하여 제공하는 경우",
        "제4조 개인정보취급 위탁",
        "회사는 고객님의 소중한 개인정보 보호를 위하여 직접 고객님의 개인정보를 취급 관리합니다. 단, 회사는 고객님에서 전문적인 서비스를 제공하기 위하여 제3의 전문기관에 고객님의 개인정보를 위탁할 필요가 있다고 판단되는 경우, 제3자에게 고객님의 개인정보를 제공하는 것과 동일한 절차를 거친 후 제3의 전문기관에 고객님의 개인정보에 대한 취급을 위탁할 수 있습니다.",
        "회사는 서비스 이행을 위해서 아래와 같이 개인정보를 위탁하고 있으며, 관계 법령에 따라 위탁계약 시 개인정보가 안전하게 관리될 수 있도록 필요한 사항을 규정하고 있습니다.",
        "회사의 개인정보 위탁처리 기관 및 위탁업무 내용은 아래와 같습니다.",
        "수탁업체: 에코킹덤㈜",
        "위탁업무내용: 고객센터 위탁운영/커뮤니티, 홈페이지 위탁운영/이벤트 위탁운영",
        "개인정보의 보유 및 이용기간 : 위탁계약 종료 시",
        " ",
        "제5조 개인정보 보유 및 이용기간",
        "회사는 이용자의 회원가입 후 탈퇴 전까지 이용자의 개인정보를 보관합니다. 다만 회사는 내부 정책에 따라 부정이용 방지 및 상담기록 보존을 위하여 회원탈퇴 후 3개월 동안 개인정보를 보관 한 뒤에 파기 하게 됩니다. 또한 관련법령 규정에 의하여 보존할 필요가 있는 개인정보에 대해서 다음과 같이 일정기간 보관합니다. 단, 관련법령에 규정되지 않은 정보에 대해서는 수집목적이 달성되는 즉시 파기합니다.",
        "1) 보유하는 개인정보 항목",
        "- 본 개인정보 취급방침 1조에 명시된 수집항목 전체를 보관합니다.",
        "2) 정보 보관 사유",
        "상법, 전자상거래 등에서의 소비자보호에 관한 법률 등 관계법령의 규정에 의하여 보존할 필요가 있는 경우 회사는 관계법령에서 정한 일정기간 동안 회원정보를 보관합니다.",
        "이러한 경우 보존기간은 아래와 같습니다.",
        "(1) 계약 또는 청약철회 등에 관한 기록",
        "- 전자상거래 등에서의 소비자보호에 관한 법률, 보존 기간 : 5년",
        "(2) 대금결제 및 재화 등의 공급에 관한 기록",
        "- 전자상거래 등에서의 소비자보호에 관한 법률, 보존 기간 : 5년",
        "(3) 소비자의 불만 또는 분쟁처리에 관한 기록",
        "- 전자상거래 등에서의 소비자보호에 관한 법률, 보존 기간 : 3년",
        "(4) 방문에 관한 기록",
        "- 통신비밀보호법, 보존 기간 : 3개월",
        "(5) 본인확인에 관한 기록",
        "- 정보통신 이용촉진 및 정보보호 등에 관한 법률, 보존 기간 : 6개월",
        "제6조 개인정보 파기절차 및 방법",
        "이용자의 개인정보는 원칙적으로 이용자가 회원탈퇴를 하거나 개인정보의 수집 및 이용목적이 달성되면 지체 없이 파기합니다. 회사의 개인정보 파기절차 및 방법은 다음과 같습니다.",
        "1. 파기절차",
        "1) 이용자가 서비스 가입 등을 위해 입력한 정보는 목적이 달성된 후 별도의 DB로 옮겨져 내부 방침 및 기타 관련 법령에 의한 정보보호 사유에 따라(보유 및 이용기간 참조)일정 기간 저장된 후 파기됩니다.",
        "2) 개인정보는 법률에 의한 경우가 아니고서는 보유되는 이외의 다른 목적으로 이용되지 않습니다.",
        "2. 파기방법",
        "1) 종이에 출력된 개인정보는 분쇄기로 분쇄하거나 소각을 통하여 파기합니다.",
        "2) 전자적 파일 형태로 저장된 개인정보는 기록을 재생할 수 없는 기술적 방법을 사용하여 삭제합니다.",
        "제7조 개인정보의 기술적/관리적 보호 대책",
        "1) 회사는 회원의 개인정보에 대한 접근권한을 최소한의 인원으로 제한하고 있으며, 해당인원들은 개인정보관리 관련 교육을 받고 있습니다. 그에 해당하는 자는 다음과 같습니다.",
        "- 회원을 직접 상대로 하여 마케팅업무를 수행하는 자",
        "- 개인정보문의 처리 부서 및 담당자 등 개인정보관리업무를 수행하는 자",
        "- 기타 업무상 개인정보의 취급이 불가피한 자",
        "2) 해킹 등에 대비한 관리 대책",
        "- 암호화 통신 등을 통하여 네트워크상에서 개인정보를 안전하게 전송 및 보관 할 수 있도록 기술적 시스템 보안에 최선을 다하고 있습니다.",
        "3) 회원의 개인정보 관리 및 책임",
        "- 회사는 회원에 과실로 및 부주의로 발생한 문제에 대해서 책임을 지지 않으며, 회원은 본인의 개인정보를 보호하기 위해서 자신의 개인정보를 안전하게 관리를 해야 하며, 그에 대한 책임을 져야 합니다.",
        "제8조 개인정보 관리책임자 및 개인정보 담당부서",
        "회사는 개인정보를 보호하는데 있어 회사의 귀책 사유로 회원님에게 고지한 사항들에 반하는 사고가 발생할 시에 개인정보관리부서가 모든 책임을 집니다. 그러나 기술적인 보완조치를 했음에도 불구하고, 해킹 등 네트워크상의 위험성에 의해 발생하는 예기치 못한 사고로 인한 정보훼손, 침해, 누설되는 경우나 이용자 과실로 발생된 개인 정보 유출로 인한 문제에 대해 회사는 일체의 책임을 지지 않습니다.",
        "회사는 고객님의 개인정보를 보호하고 개인정보와 관련된 불만을 처리하기 위하여 아래와 같이 개인정보관리책임자 및 개인정보관리담당자를 지정하고 있습니다.",
        "1) 개인정보 관리책임자",
        "소속/직위 : 337 Technology Limited 마케팅팀 / 대리",
        "성명 : 왕석",
        "전화번호 : 0086 010 82800116",
        "E-mail : playhousekorea@gmail.com",
        " ",
        "2) 개인정보 관리담당자",
        "소속/직위 : 337 Technology Limited 마케팅팀 / 대리",
        "성명 : 왕석",
        "전화번호 : 0086 010 82800116",
        "E-mail : playhousekorea@gmail.com",
        " ",
        "제9조 청소년보호를 위한 활동",
        "회사는 각종 청소년 유해정보로부터 청소년을 보호하고자 관련법에 따라 19세미만의 청소년이 유해정보에 접근할 수 없도록 청소년보호정책을 마련하여 시행하고 있습니다. 또 회사는 청소년의 건전한 성장을 저해하는 음란, 불법 유해정보와 비윤리적, 반사회적 행위에 대해서는 엄격하게 제재하기 위하여 다음과 같이 활동하고 있습니다.",
        " ",
        "1. 청소년유해정보로부터의 청소년보호계획의 수립",
        "- 회사는 청소년이 아무런 제한장치 없이 청소년 유해정보에 노출되지 않도록 청소년유해매체물에 대해서는 별도의 인증장치를 마련, 적용하며 청소년 유해정보가 노출되지 않기 위한 예방 차원의 조치를 강구합니다.",
        "2. 청소년유해정보에 대한 청소년 접근제한 및 관리조치",
        "- 회사는 정보통신업무 종사자를 대상으로 청소년보호 관련 법령 및 제재기준, 유해정보 발견시 대처방법, 위반사항 처리에 대한 보고절차 등을 교육하고 있습니다.",
        "3. 정보통신업무 종사자에 대한 청소년유해정보로부터의 청소년보호를 위한 교육",
        "- 회사는 청소년보호담당자 및 각 서비스 담당자들을 대상으로 청소년 보호를 위한 각종 관련 법령 및 제재기준, 유해정보 발견 시 대처방법, 위반사항 처리에 대한 보고절차 등을 교육하고 있습니다.",
        "4. 청소년유해정보로 인한 피해상담 및 고충처리",
        "- 회사는 청소년 유해정보로 인한 피해상담 및 고충처리를 위한 전문인력을 배치하여 그 피해가 확산되지 않도록 하고 있습니다. 이용자 분들께서는 하단에 명시한 \"6. 청소년보호 책임자 및 담당자의 소속, 성명 및 연락처\" 항을 참고하여 전화나 메일을 통하여 피해상담 및 고충처리를 요청할 수 있습니다.",
        "5. 그 밖에 청소년유해정보로부터 청소년을 보호하기 위하여 필요한 사항",
        "- 이에 대해 회사는 청소년보호를 위한 인터넷기업의 공동노력에 동참합니다.",
        "1) 청소년보호를 위한 인터넷기업 윤리강령",
        "2) 청소년보호를 위한 인터넷기업 실천지침",
        " ",
        "6. 청소년 보호정책 관련 관리책임자 및 담당자",
        "1) 청소년 보호 관리책임자",
        "소속/직위 : 337 Technology Limited 마케팅팀 / 대리",
        "성명 : 왕석",
        "전화번호 : 0086 010 82800116",
        "E-mail : playhousekorea@gmail.com",
        " ",
        "2) 청소년 보호 관리담당자",
        "소속/직위 : 337 Technology Limited 마케팅팀 / 대리",
        "성명 : 왕석",
        "전화번호 : 0086 010 82800116",
        "E-mail : playhousekorea@gmail.com",
        " ",
        "제10조 고지의 의무",
        "회사는 개인정보취급방침의 내용 추가, 삭제 또는 수정이 있을 시에는 최소 7일 전에 공지사항을 통해 회원님에게 고지합니다.",
        "본 개인정보취급방침은 2015년 3월 1일부터 시행됩니다."
    };
    if(type == 1)
        return serviceTerms;
    else
        return personalTerms;
}
