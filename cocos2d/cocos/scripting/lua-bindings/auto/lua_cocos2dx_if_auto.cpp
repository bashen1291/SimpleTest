#include "lua_cocos2dx_if_auto.hpp"
#include "CCSafeNotificationCenter.h"
#include "CCFlagWaveSprite.h"
#include "ActivityEventObj.h"
#include "LuaController.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_if_CCSafeNotificationCenter_removeObserver(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::CCSafeNotificationCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCSafeNotificationCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::CCSafeNotificationCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_CCSafeNotificationCenter_removeObserver'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Ref* arg0;
        const char* arg1;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.CCSafeNotificationCenter:removeObserver"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCSafeNotificationCenter_removeObserver'", nullptr);
            return 0;
        }
        cobj->removeObserver(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCSafeNotificationCenter:removeObserver",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_CCSafeNotificationCenter_removeObserver'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_CCSafeNotificationCenter_postNotification(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::CCSafeNotificationCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCSafeNotificationCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::CCSafeNotificationCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_CCSafeNotificationCenter_postNotification'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.CCSafeNotificationCenter:postNotification"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCSafeNotificationCenter_postNotification'", nullptr);
            return 0;
        }
        cobj->postNotification(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        const char* arg0;
        cocos2d::Ref* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.CCSafeNotificationCenter:postNotification"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 3, "cc.Ref",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCSafeNotificationCenter_postNotification'", nullptr);
            return 0;
        }
        cobj->postNotification(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCSafeNotificationCenter:postNotification",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_CCSafeNotificationCenter_postNotification'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_CCSafeNotificationCenter_dumpAllNotificationObserver(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::CCSafeNotificationCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCSafeNotificationCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::CCSafeNotificationCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_CCSafeNotificationCenter_dumpAllNotificationObserver'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCSafeNotificationCenter_dumpAllNotificationObserver'", nullptr);
            return 0;
        }
        cobj->dumpAllNotificationObserver();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCSafeNotificationCenter:dumpAllNotificationObserver",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_CCSafeNotificationCenter_dumpAllNotificationObserver'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_CCSafeNotificationCenter_removeAllObserver(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::CCSafeNotificationCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CCSafeNotificationCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::CCSafeNotificationCenter*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_CCSafeNotificationCenter_removeAllObserver'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCSafeNotificationCenter_removeAllObserver'", nullptr);
            return 0;
        }
        cobj->removeAllObserver(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCSafeNotificationCenter:removeAllObserver",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_CCSafeNotificationCenter_removeAllObserver'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_CCSafeNotificationCenter_sharedNotificationCenter(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CCSafeNotificationCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCSafeNotificationCenter_sharedNotificationCenter'", nullptr);
            return 0;
        }
        cocos2d::extension::CCSafeNotificationCenter* ret = cocos2d::extension::CCSafeNotificationCenter::sharedNotificationCenter();
        object_to_luaval<cocos2d::extension::CCSafeNotificationCenter>(tolua_S, "cc.CCSafeNotificationCenter",(cocos2d::extension::CCSafeNotificationCenter*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CCSafeNotificationCenter:sharedNotificationCenter",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_CCSafeNotificationCenter_sharedNotificationCenter'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_CCSafeNotificationCenter_purgeNotificationCenter(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CCSafeNotificationCenter",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCSafeNotificationCenter_purgeNotificationCenter'", nullptr);
            return 0;
        }
        cocos2d::extension::CCSafeNotificationCenter::purgeNotificationCenter();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CCSafeNotificationCenter:purgeNotificationCenter",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_CCSafeNotificationCenter_purgeNotificationCenter'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_CCSafeNotificationCenter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::CCSafeNotificationCenter* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCSafeNotificationCenter_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::CCSafeNotificationCenter();
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.CCSafeNotificationCenter");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CCSafeNotificationCenter:CCSafeNotificationCenter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_CCSafeNotificationCenter_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_if_CCSafeNotificationCenter_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCSafeNotificationCenter)");
    return 0;
}

int lua_register_cocos2dx_if_CCSafeNotificationCenter(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.CCSafeNotificationCenter");
    tolua_cclass(tolua_S,"CCSafeNotificationCenter","cc.CCSafeNotificationCenter","",nullptr);

    tolua_beginmodule(tolua_S,"CCSafeNotificationCenter");
        tolua_function(tolua_S,"new",lua_cocos2dx_if_CCSafeNotificationCenter_constructor);
        tolua_function(tolua_S,"removeObserver",lua_cocos2dx_if_CCSafeNotificationCenter_removeObserver);
        tolua_function(tolua_S,"postNotification",lua_cocos2dx_if_CCSafeNotificationCenter_postNotification);
        tolua_function(tolua_S,"dumpAllNotificationObserver",lua_cocos2dx_if_CCSafeNotificationCenter_dumpAllNotificationObserver);
        tolua_function(tolua_S,"removeAllObserver",lua_cocos2dx_if_CCSafeNotificationCenter_removeAllObserver);
        tolua_function(tolua_S,"sharedNotificationCenter", lua_cocos2dx_if_CCSafeNotificationCenter_sharedNotificationCenter);
        tolua_function(tolua_S,"purgeNotificationCenter", lua_cocos2dx_if_CCSafeNotificationCenter_purgeNotificationCenter);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::CCSafeNotificationCenter).name();
    g_luaType[typeName] = "cc.CCSafeNotificationCenter";
    g_typeCast["CCSafeNotificationCenter"] = "cc.CCSafeNotificationCenter";
    return 1;
}

int lua_cocos2dx_if_CCFlagWaveSprite_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CCFlagWaveSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::SpriteFrame* arg0;
        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_CCFlagWaveSprite_create'", nullptr);
            return 0;
        }
        cocos2d::CCFlagWaveSprite* ret = cocos2d::CCFlagWaveSprite::create(arg0);
        object_to_luaval<cocos2d::CCFlagWaveSprite>(tolua_S, "cc.CCFlagWaveSprite",(cocos2d::CCFlagWaveSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CCFlagWaveSprite:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_CCFlagWaveSprite_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_if_CCFlagWaveSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCFlagWaveSprite)");
    return 0;
}

int lua_register_cocos2dx_if_CCFlagWaveSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.CCFlagWaveSprite");
    tolua_cclass(tolua_S,"CCFlagWaveSprite","cc.CCFlagWaveSprite","cc.CCSprite",nullptr);

    tolua_beginmodule(tolua_S,"CCFlagWaveSprite");
        tolua_function(tolua_S,"create", lua_cocos2dx_if_CCFlagWaveSprite_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::CCFlagWaveSprite).name();
    g_luaType[typeName] = "cc.CCFlagWaveSprite";
    g_typeCast["CCFlagWaveSprite"] = "cc.CCFlagWaveSprite";
    return 1;
}

int lua_cocos2dx_if_ActivityEventObj_getReward(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_getReward'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_getReward'", nullptr);
            return 0;
        }
        cocos2d::__Array* ret = cobj->getReward();
        object_to_luaval<cocos2d::__Array>(tolua_S, "cc.__Array",(cocos2d::__Array*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:getReward",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_getReward'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_setForceId(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_setForceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ActivityEventObj:setForceId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_setForceId'", nullptr);
            return 0;
        }
        cobj->setForceId(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:setForceId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_setForceId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_updateShowTypeStatus(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_updateShowTypeStatus'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_updateShowTypeStatus'", nullptr);
            return 0;
        }
        cobj->updateShowTypeStatus();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ActivityEventObj:updateShowTypeStatus");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_updateShowTypeStatus'", nullptr);
            return 0;
        }
        cobj->updateShowTypeStatus(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:updateShowTypeStatus",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_updateShowTypeStatus'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_setRound(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_setRound'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ActivityEventObj:setRound");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_setRound'", nullptr);
            return 0;
        }
        cobj->setRound(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:setRound",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_setRound'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_removeActIdFromList(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_removeActIdFromList'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_removeActIdFromList'", nullptr);
            return 0;
        }
        cobj->removeActIdFromList();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:removeActIdFromList",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_removeActIdFromList'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_getRound(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_getRound'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_getRound'", nullptr);
            return 0;
        }
        int ret = cobj->getRound();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:getRound",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_getRound'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_toDic(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_toDic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_toDic'", nullptr);
            return 0;
        }
        cocos2d::__Dictionary* ret = cobj->toDic();
        object_to_luaval<cocos2d::__Dictionary>(tolua_S, "cc.__Dictionary",(cocos2d::__Dictionary*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:toDic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_toDic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_getServerId(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_getServerId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_getServerId'", nullptr);
            return 0;
        }
        int ret = cobj->getServerId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:getServerId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_getServerId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_parse(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_parse'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::__Dictionary* arg0;

        ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 2, "cc.__Dictionary",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_parse'", nullptr);
            return 0;
        }
        cobj->parse(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:parse",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_parse'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_setReward(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_setReward'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::__Array* arg0;

        ok &= luaval_to_object<cocos2d::__Array>(tolua_S, 2, "cc.__Array",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_setReward'", nullptr);
            return 0;
        }
        cobj->setReward(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:setReward",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_setReward'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_setServerId(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_setServerId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ActivityEventObj:setServerId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_setServerId'", nullptr);
            return 0;
        }
        cobj->setServerId(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:setServerId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_setServerId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_getForceId(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_getForceId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_getForceId'", nullptr);
            return 0;
        }
        int ret = cobj->getForceId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:getForceId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_getForceId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_addActIdToList(lua_State* tolua_S)
{
    int argc = 0;
    ActivityEventObj* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActivityEventObj*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_ActivityEventObj_addActIdToList'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_addActIdToList'", nullptr);
            return 0;
        }
        cobj->addActIdToList();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ActivityEventObj:addActIdToList",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_addActIdToList'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_ActivityEventObj_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActivityEventObj",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_ActivityEventObj_create'", nullptr);
            return 0;
        }
        ActivityEventObj* ret = ActivityEventObj::create();
        object_to_luaval<ActivityEventObj>(tolua_S, "ActivityEventObj",(ActivityEventObj*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActivityEventObj:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_ActivityEventObj_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_if_ActivityEventObj_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActivityEventObj)");
    return 0;
}

int lua_register_cocos2dx_if_ActivityEventObj(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ActivityEventObj");
    tolua_cclass(tolua_S,"ActivityEventObj","ActivityEventObj","cc.CCObject",nullptr);

    tolua_beginmodule(tolua_S,"ActivityEventObj");
        tolua_function(tolua_S,"getReward",lua_cocos2dx_if_ActivityEventObj_getReward);
        tolua_function(tolua_S,"setForceId",lua_cocos2dx_if_ActivityEventObj_setForceId);
        tolua_function(tolua_S,"updateShowTypeStatus",lua_cocos2dx_if_ActivityEventObj_updateShowTypeStatus);
        tolua_function(tolua_S,"setRound",lua_cocos2dx_if_ActivityEventObj_setRound);
        tolua_function(tolua_S,"removeActIdFromList",lua_cocos2dx_if_ActivityEventObj_removeActIdFromList);
        tolua_function(tolua_S,"getRound",lua_cocos2dx_if_ActivityEventObj_getRound);
        tolua_function(tolua_S,"toDic",lua_cocos2dx_if_ActivityEventObj_toDic);
        tolua_function(tolua_S,"getServerId",lua_cocos2dx_if_ActivityEventObj_getServerId);
        tolua_function(tolua_S,"parse",lua_cocos2dx_if_ActivityEventObj_parse);
        tolua_function(tolua_S,"setReward",lua_cocos2dx_if_ActivityEventObj_setReward);
        tolua_function(tolua_S,"setServerId",lua_cocos2dx_if_ActivityEventObj_setServerId);
        tolua_function(tolua_S,"getForceId",lua_cocos2dx_if_ActivityEventObj_getForceId);
        tolua_function(tolua_S,"addActIdToList",lua_cocos2dx_if_ActivityEventObj_addActIdToList);
        tolua_function(tolua_S,"create", lua_cocos2dx_if_ActivityEventObj_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ActivityEventObj).name();
    g_luaType[typeName] = "ActivityEventObj";
    g_typeCast["ActivityEventObj"] = "ActivityEventObj";
    return 1;
}

int lua_cocos2dx_if_LuaController_ChatNoticeInView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_ChatNoticeInView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_ChatNoticeInView'", nullptr);
            return 0;
        }
        cobj->ChatNoticeInView();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_ChatNoticeInView'", nullptr);
            return 0;
        }
        cobj->ChatNoticeInView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:ChatNoticeInView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_ChatNoticeInView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_backToExchange(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_backToExchange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:backToExchange");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_backToExchange'", nullptr);
            return 0;
        }
        cobj->backToExchange(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:backToExchange",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_backToExchange'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_createExchangeIcon(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_createExchangeIcon'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:createExchangeIcon");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createExchangeIcon'", nullptr);
            return 0;
        }
        cobj->createExchangeIcon(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:createExchangeIcon",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createExchangeIcon'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_refreshRandView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_refreshRandView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:refreshRandView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_refreshRandView'", nullptr);
            return 0;
        }
        cobj->refreshRandView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:refreshRandView");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "LuaController:refreshRandView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_refreshRandView'", nullptr);
            return 0;
        }
        cobj->refreshRandView(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:refreshRandView",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_refreshRandView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_canTranslate(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_canTranslate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_canTranslate'", nullptr);
            return 0;
        }
        bool ret = cobj->canTranslate();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:canTranslate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_canTranslate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_recvGoldExchangeNetMsg(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_recvGoldExchangeNetMsg'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:recvGoldExchangeNetMsg");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_recvGoldExchangeNetMsg'", nullptr);
            return 0;
        }
        int ret = cobj->recvGoldExchangeNetMsg(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:recvGoldExchangeNetMsg",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_recvGoldExchangeNetMsg'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_backCMD(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_backCMD'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocos2d::__Dictionary* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:backCMD");

        ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 3, "cc.__Dictionary",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_backCMD'", nullptr);
            return 0;
        }
        cobj->backCMD(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:backCMD",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_backCMD'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showRescueView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showRescueView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showRescueView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->showRescueView();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showRescueView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showRescueView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_updateExchangeGiftInfo(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_updateExchangeGiftInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        double arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:updateExchangeGiftInfo");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:updateExchangeGiftInfo");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "LuaController:updateExchangeGiftInfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_updateExchangeGiftInfo'", nullptr);
            return 0;
        }
        cobj->updateExchangeGiftInfo(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:updateExchangeGiftInfo",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_updateExchangeGiftInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showCombatSliderSpeView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showCombatSliderSpeView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showCombatSliderSpeView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->showCombatSliderSpeView();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showCombatSliderSpeView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showCombatSliderSpeView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getAdvCellContainer(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getAdvCellContainer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getAdvCellContainer'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getAdvCellContainer();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getAdvCellContainer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getAdvCellContainer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getChatNoticeContainer(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getChatNoticeContainer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getChatNoticeContainer'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getChatNoticeContainer();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getChatNoticeContainer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getChatNoticeContainer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_changeUI(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_changeUI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_changeUI'", nullptr);
            return 0;
        }
        cobj->changeUI();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "LuaController:changeUI");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_changeUI'", nullptr);
            return 0;
        }
        cobj->changeUI(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:changeUI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_changeUI'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_closeChatNotice(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_closeChatNotice'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_closeChatNotice'", nullptr);
            return 0;
        }
        cobj->closeChatNotice();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:closeChatNotice",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_closeChatNotice'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_initLua(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_initLua'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_initLua'", nullptr);
            return 0;
        }
        bool ret = cobj->initLua();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:initLua",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_initLua'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getPayFun(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getPayFun'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getPayFun");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getPayFun'", nullptr);
            return 0;
        }
        std::function<void ()> ret = cobj->getPayFun(arg0);
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getPayFun",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getPayFun'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_checkLuaValid(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_checkLuaValid'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:checkLuaValid");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:checkLuaValid");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:checkLuaValid");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_checkLuaValid'", nullptr);
            return 0;
        }
        bool ret = cobj->checkLuaValid(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:checkLuaValid",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_checkLuaValid'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_ChatNoticeInSceen(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_ChatNoticeInSceen'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_ChatNoticeInSceen'", nullptr);
            return 0;
        }
        cobj->ChatNoticeInSceen();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_ChatNoticeInSceen'", nullptr);
            return 0;
        }
        cobj->ChatNoticeInSceen(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:ChatNoticeInSceen",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_ChatNoticeInSceen'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_canSendExchange(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_canSendExchange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:canSendExchange");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:canSendExchange");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:canSendExchange");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_canSendExchange'", nullptr);
            return 0;
        }
        bool ret = cobj->canSendExchange(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        int arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:canSendExchange");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:canSendExchange");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:canSendExchange");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:canSendExchange");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_canSendExchange'", nullptr);
            return 0;
        }
        bool ret = cobj->canSendExchange(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 5) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        int arg3;
        bool arg4;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:canSendExchange");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:canSendExchange");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:canSendExchange");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:canSendExchange");

        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "LuaController:canSendExchange");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_canSendExchange'", nullptr);
            return 0;
        }
        bool ret = cobj->canSendExchange(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:canSendExchange",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_canSendExchange'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getActExcData(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getActExcData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getActExcData'", nullptr);
            return 0;
        }
        cobj->getActExcData();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getActExcData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getActExcData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getLoginTime(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getLoginTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getLoginTime'", nullptr);
            return 0;
        }
        int ret = cobj->getLoginTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getLoginTime",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getLoginTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_checkResValid(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_checkResValid'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:checkResValid");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:checkResValid");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:checkResValid");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_checkResValid'", nullptr);
            return 0;
        }
        bool ret = cobj->checkResValid(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:checkResValid",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_checkResValid'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_addSystemUpdate(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_addSystemUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        double arg0;
        bool arg1;
        std::string arg2;
        int arg3;
        std::string arg4;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "LuaController:addSystemUpdate");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "LuaController:addSystemUpdate");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:addSystemUpdate");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:addSystemUpdate");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "LuaController:addSystemUpdate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addSystemUpdate'", nullptr);
            return 0;
        }
        cobj->addSystemUpdate(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:addSystemUpdate",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addSystemUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_recvLuaNetMessage(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_recvLuaNetMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:recvLuaNetMessage");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_recvLuaNetMessage'", nullptr);
            return 0;
        }
        int ret = cobj->recvLuaNetMessage(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:recvLuaNetMessage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_recvLuaNetMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_createActivityAdCell(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_createActivityAdCell'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ActivityEventObj* arg0;

        ok &= luaval_to_object<ActivityEventObj>(tolua_S, 2, "ActivityEventObj",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createActivityAdCell'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createActivityAdCell(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:createActivityAdCell",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createActivityAdCell'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getIconContainer(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getIconContainer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getIconContainer'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getIconContainer();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getIconContainer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getIconContainer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_isLuaOpen(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_isLuaOpen'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_isLuaOpen'", nullptr);
            return 0;
        }
        bool ret = cobj->isLuaOpen();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:isLuaOpen",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_isLuaOpen'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getAdvCell(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getAdvCell'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getAdvCell'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getAdvCell();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getAdvCell",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getAdvCell'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_createActivityListCellSprite(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_createActivityListCellSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ActivityEventObj* arg0;

        ok &= luaval_to_object<ActivityEventObj>(tolua_S, 2, "ActivityEventObj",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createActivityListCellSprite'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createActivityListCellSprite(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:createActivityListCellSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createActivityListCellSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showAllHireSoldiers(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showAllHireSoldiers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showAllHireSoldiers'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->showAllHireSoldiers();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showAllHireSoldiers",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showAllHireSoldiers'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_RandomForGift(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_RandomForGift'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "LuaController:RandomForGift");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_RandomForGift'", nullptr);
            return 0;
        }
        cobj->RandomForGift(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:RandomForGift",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_RandomForGift'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_createActivityView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_createActivityView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ActivityEventObj* arg0;

        ok &= luaval_to_object<ActivityEventObj>(tolua_S, 2, "ActivityEventObj",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createActivityView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createActivityView(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:createActivityView",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createActivityView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getPopupTop(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getPopupTop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getPopupTop'", nullptr);
            return 0;
        }
        int ret = cobj->getPopupTop();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getPopupTop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getPopupTop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_setPopupBot(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_setPopupBot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:setPopupBot");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setPopupBot'", nullptr);
            return 0;
        }
        cobj->setPopupBot(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:setPopupBot",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setPopupBot'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showCombatSliderView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showCombatSliderView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showCombatSliderView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->showCombatSliderView();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showCombatSliderView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showCombatSliderView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_addSoldierInfoView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_addSoldierInfoView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addSoldierInfoView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->addSoldierInfoView();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:addSoldierInfoView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addSoldierInfoView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getIsPaying(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getIsPaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getIsPaying'", nullptr);
            return 0;
        }
        bool ret = cobj->getIsPaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getIsPaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getIsPaying'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showSceneNotice(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showSceneNotice'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "LuaController:showSceneNotice");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showSceneNotice'", nullptr);
            return 0;
        }
        cobj->showSceneNotice(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showSceneNotice",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showSceneNotice'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_initExchangeGiftInfo(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_initExchangeGiftInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::__Array* arg0;

        ok &= luaval_to_object<cocos2d::__Array>(tolua_S, 2, "cc.__Array",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_initExchangeGiftInfo'", nullptr);
            return 0;
        }
        cobj->initExchangeGiftInfo(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:initExchangeGiftInfo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_initExchangeGiftInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_updateRandItem(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_updateRandItem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        GoldExchangeItem* arg0;

        ok &= luaval_to_object<GoldExchangeItem>(tolua_S, 2, "GoldExchangeItem",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_updateRandItem'", nullptr);
            return 0;
        }
        cobj->updateRandItem(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:updateRandItem",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_updateRandItem'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showGoldRandView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showGoldRandView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:showGoldRandView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showGoldRandView'", nullptr);
            return 0;
        }
        cobj->showGoldRandView(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        cocos2d::Node* arg0;
        std::string arg1;
        bool arg2;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:showGoldRandView");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "LuaController:showGoldRandView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showGoldRandView'", nullptr);
            return 0;
        }
        cobj->showGoldRandView(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showGoldRandView",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showGoldRandView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_unzipFinish(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_unzipFinish'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_unzipFinish'", nullptr);
            return 0;
        }
        cobj->unzipFinish();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:unzipFinish",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_unzipFinish'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_setIsPaying(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_setIsPaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "LuaController:setIsPaying");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setIsPaying'", nullptr);
            return 0;
        }
        cobj->setIsPaying(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:setIsPaying",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setIsPaying'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_setLoginTime(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_setLoginTime'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:setLoginTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setLoginTime'", nullptr);
            return 0;
        }
        cobj->setLoginTime(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:setLoginTime",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setLoginTime'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_changeChatNotice(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_changeChatNotice'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_changeChatNotice'", nullptr);
            return 0;
        }
        cobj->changeChatNotice();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_changeChatNotice'", nullptr);
            return 0;
        }
        cobj->changeChatNotice(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:changeChatNotice",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_changeChatNotice'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_downloadFinish(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_downloadFinish'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_downloadFinish'", nullptr);
            return 0;
        }
        cobj->downloadFinish();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:downloadFinish",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_downloadFinish'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_updateTroopsChange(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_updateTroopsChange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_updateTroopsChange'", nullptr);
            return 0;
        }
        cobj->updateTroopsChange(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:updateTroopsChange",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_updateTroopsChange'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showExchangeSale(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showExchangeSale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Node* arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:showExchangeSale");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:showExchangeSale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showExchangeSale'", nullptr);
            return 0;
        }
        cobj->showExchangeSale(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 4) 
    {
        cocos2d::Node* arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:showExchangeSale");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:showExchangeSale");

        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "LuaController:showExchangeSale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showExchangeSale'", nullptr);
            return 0;
        }
        cobj->showExchangeSale(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 5) 
    {
        cocos2d::Node* arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:showExchangeSale");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:showExchangeSale");

        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "LuaController:showExchangeSale");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "LuaController:showExchangeSale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showExchangeSale'", nullptr);
            return 0;
        }
        cobj->showExchangeSale(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showExchangeSale",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showExchangeSale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_clearChatNotice(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_clearChatNotice'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_clearChatNotice'", nullptr);
            return 0;
        }
        cobj->clearChatNotice();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:clearChatNotice",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_clearChatNotice'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_createExchangeRandIcon(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_createExchangeRandIcon'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:createExchangeRandIcon");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createExchangeRandIcon'", nullptr);
            return 0;
        }
        cobj->createExchangeRandIcon(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        cocos2d::Node* arg0;
        std::string arg1;
        bool arg2;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:createExchangeRandIcon");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "LuaController:createExchangeRandIcon");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createExchangeRandIcon'", nullptr);
            return 0;
        }
        cobj->createExchangeRandIcon(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:createExchangeRandIcon",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createExchangeRandIcon'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showHireArmyView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showHireArmyView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showHireArmyView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->showHireArmyView();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showHireArmyView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showHireArmyView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getPopupBot(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getPopupBot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getPopupBot'", nullptr);
            return 0;
        }
        int ret = cobj->getPopupBot();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getPopupBot",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getPopupBot'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_createExchangeAdvCell(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_createExchangeAdvCell'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:createExchangeAdvCell");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createExchangeAdvCell'", nullptr);
            return 0;
        }
        cocos2d::Rect ret = cobj->createExchangeAdvCell(arg0, arg1);
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:createExchangeAdvCell",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createExchangeAdvCell'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_createActivityRwdView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_createActivityRwdView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ActivityEventObj* arg0;

        ok &= luaval_to_object<ActivityEventObj>(tolua_S, 2, "ActivityEventObj",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createActivityRwdView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->createActivityRwdView(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:createActivityRwdView",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createActivityRwdView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showActRwdViewByActId(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showActRwdViewByActId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showActRwdViewByActId");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showActRwdViewByActId'", nullptr);
            return 0;
        }
        cobj->showActRwdViewByActId(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showActRwdViewByActId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showActRwdViewByActId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_setPopupTop(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_setPopupTop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:setPopupTop");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setPopupTop'", nullptr);
            return 0;
        }
        cobj->setPopupTop(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:setPopupTop",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setPopupTop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_sendCMD(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_sendCMD'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocos2d::__Dictionary* arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:sendCMD");

        ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 3, "cc.__Dictionary",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_sendCMD'", nullptr);
            return 0;
        }
        cobj->sendCMD(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:sendCMD",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_sendCMD'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_pushResItemToVec(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_pushResItemToVec'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_pushResItemToVec'", nullptr);
            return 0;
        }
        cobj->pushResItemToVec();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:pushResItemToVec");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_pushResItemToVec'", nullptr);
            return 0;
        }
        cobj->pushResItemToVec(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:pushResItemToVec");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:pushResItemToVec");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_pushResItemToVec'", nullptr);
            return 0;
        }
        cobj->pushResItemToVec(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:pushResItemToVec");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:pushResItemToVec");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:pushResItemToVec");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_pushResItemToVec'", nullptr);
            return 0;
        }
        cobj->pushResItemToVec(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:pushResItemToVec",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_pushResItemToVec'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_showCombatPopView(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_showCombatPopView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showCombatPopView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->showCombatPopView();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:showCombatPopView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showCombatPopView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_addChatNotice(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_addChatNotice'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::__Dictionary* arg0;

        ok &= luaval_to_object<cocos2d::__Dictionary>(tolua_S, 2, "cc.__Dictionary",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addChatNotice'", nullptr);
            return 0;
        }
        cobj->addChatNotice(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:addChatNotice",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addChatNotice'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_updateExchangeAdvCell(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_updateExchangeAdvCell'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::string arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:updateExchangeAdvCell");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_updateExchangeAdvCell'", nullptr);
            return 0;
        }
        cobj->updateExchangeAdvCell(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:updateExchangeAdvCell",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_updateExchangeAdvCell'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_checkActLuaValid(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_checkActLuaValid'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ActivityEventObj* arg0;

        ok &= luaval_to_object<ActivityEventObj>(tolua_S, 2, "ActivityEventObj",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_checkActLuaValid'", nullptr);
            return 0;
        }
        bool ret = cobj->checkActLuaValid(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:checkActLuaValid",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_checkActLuaValid'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_getSaleViewContainer(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_if_LuaController_getSaleViewContainer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getSaleViewContainer'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getSaleViewContainer();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:getSaleViewContainer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getSaleViewContainer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_if_LuaController_ShowInfoCellSprite(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        int arg0;
        std::string arg1;
        std::string arg2;
        bool arg3;
        bool arg4;
        int arg5;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:ShowInfoCellSprite");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:ShowInfoCellSprite");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:ShowInfoCellSprite");
        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "LuaController:ShowInfoCellSprite");
        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "LuaController:ShowInfoCellSprite");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:ShowInfoCellSprite");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_ShowInfoCellSprite'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::ShowInfoCellSprite(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:ShowInfoCellSprite",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_ShowInfoCellSprite'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showUseResToolView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showUseResToolView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showUseResToolView'", nullptr);
            return 0;
        }
        LuaController::showUseResToolView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showUseResToolView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showUseResToolView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getDiamondImm(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getDiamondImm");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:getDiamondImm");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getDiamondImm'", nullptr);
            return 0;
        }
        int ret = LuaController::getDiamondImm(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getDiamondImm",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getDiamondImm'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_isGM(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_isGM'", nullptr);
            return 0;
        }
        bool ret = LuaController::isGM();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:isGM",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_isGM'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_sendMsg(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:sendMsg");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:sendMsg");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_sendMsg'", nullptr);
            return 0;
        }
        LuaController::sendMsg(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:sendMsg",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_sendMsg'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showDetailPopup(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showDetailPopup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showDetailPopup'", nullptr);
            return 0;
        }
        LuaController::showDetailPopup(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showDetailPopup",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showDetailPopup'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addArmyToRescue(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:addArmyToRescue");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:addArmyToRescue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addArmyToRescue'", nullptr);
            return 0;
        }
        LuaController::addArmyToRescue(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addArmyToRescue",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addArmyToRescue'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getInstance'", nullptr);
            return 0;
        }
        LuaController* ret = LuaController::getInstance();
        object_to_luaval<LuaController>(tolua_S, "LuaController",(LuaController*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addItemIcon(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Node* arg0;
        std::string arg1;
        cocos2d::Label* arg2;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:addItemIcon");
        ok &= luaval_to_object<cocos2d::Label>(tolua_S, 4, "cc.Label",&arg2);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addItemIcon'", nullptr);
            return 0;
        }
        LuaController::addItemIcon(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addItemIcon",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addItemIcon'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_removePopupView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_removePopupView'", nullptr);
            return 0;
        }
        LuaController::removePopupView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:removePopupView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_removePopupView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_autoDoResourceItemIcon(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_autoDoResourceItemIcon'", nullptr);
            return 0;
        }
        LuaController::autoDoResourceItemIcon(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:autoDoResourceItemIcon",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_autoDoResourceItemIcon'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getGoodsInfo(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getGoodsInfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getGoodsInfo'", nullptr);
            return 0;
        }
        cocos2d::__Dictionary* ret = LuaController::getGoodsInfo(arg0);
        object_to_luaval<cocos2d::__Dictionary>(tolua_S, "cc.__Dictionary",(cocos2d::__Dictionary*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getGoodsInfo",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getGoodsInfo'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_SendCombatData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_SendCombatData'", nullptr);
            return 0;
        }
        LuaController::SendCombatData();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:SendCombatData",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_SendCombatData'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getFreeVipRefreshArmy(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getFreeVipRefreshArmy'", nullptr);
            return 0;
        }
        bool ret = LuaController::getFreeVipRefreshArmy();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getFreeVipRefreshArmy",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getFreeVipRefreshArmy'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createClipNode(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Size arg0;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "LuaController:createClipNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createClipNode'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::createClipNode(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createClipNode",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createClipNode'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createPopupView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createPopupView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::createPopupView();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createPopupView",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createPopupView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getLuaEncryptDownloadUrl(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getLuaEncryptDownloadUrl'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getLuaEncryptDownloadUrl();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getLuaEncryptDownloadUrl",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getLuaEncryptDownloadUrl'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getHireQueueInfo(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getHireQueueInfo'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getHireQueueInfo();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getHireQueueInfo",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getHireQueueInfo'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getTimeStamp(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getTimeStamp'", nullptr);
            return 0;
        }
        int ret = LuaController::getTimeStamp();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getTimeStamp",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getTimeStamp'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_setGoldItemParams(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:setGoldItemParams");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:setGoldItemParams");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:setGoldItemParams");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setGoldItemParams'", nullptr);
            return 0;
        }
        LuaController::setGoldItemParams(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:setGoldItemParams",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setGoldItemParams'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getLuaViewVersion(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getLuaViewVersion'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getLuaViewVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getLuaViewVersion",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getLuaViewVersion'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_removeAllPopup(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_removeAllPopup'", nullptr);
            return 0;
        }
        LuaController::removeAllPopup();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:removeAllPopup",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_removeAllPopup'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getPlayerCountryName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getPlayerCountryName'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getPlayerCountryName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getPlayerCountryName",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getPlayerCountryName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showUpgradeUnlockDetailView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showUpgradeUnlockDetailView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showUpgradeUnlockDetailView'", nullptr);
            return 0;
        }
        LuaController::showUpgradeUnlockDetailView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showUpgradeUnlockDetailView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showUpgradeUnlockDetailView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getUTF8SubString(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getUTF8SubString");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:getUTF8SubString");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:getUTF8SubString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getUTF8SubString'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getUTF8SubString(arg0, arg1, arg2);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getUTF8SubString",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getUTF8SubString'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getLanguage(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getLanguage'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getLanguage();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getLanguage",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getLanguage'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getRescueINfoData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getRescueINfoData'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getRescueINfoData();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getRescueINfoData",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getRescueINfoData'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getStringLength(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getStringLength");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getStringLength'", nullptr);
            return 0;
        }
        int ret = LuaController::getStringLength(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getStringLength",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getStringLength'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getCMDParams(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getCMDParams");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getCMDParams'", nullptr);
            return 0;
        }
        cocos2d::__Dictionary* ret = LuaController::getCMDParams(arg0);
        object_to_luaval<cocos2d::__Dictionary>(tolua_S, "cc.__Dictionary",(cocos2d::__Dictionary*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getCMDParams",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getCMDParams'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_postNotification(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:postNotification");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_postNotification'", nullptr);
            return 0;
        }
        LuaController::postNotification(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:postNotification",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_postNotification'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getWorldTime(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getWorldTime'", nullptr);
            return 0;
        }
        int ret = LuaController::getWorldTime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getWorldTime",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getWorldTime'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addSoldierSkillInfoPopUpView2(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        int arg3;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:addSoldierSkillInfoPopUpView2");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:addSoldierSkillInfoPopUpView2");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:addSoldierSkillInfoPopUpView2");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:addSoldierSkillInfoPopUpView2");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addSoldierSkillInfoPopUpView2'", nullptr);
            return 0;
        }
        LuaController::addSoldierSkillInfoPopUpView2(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addSoldierSkillInfoPopUpView2",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addSoldierSkillInfoPopUpView2'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_isPad(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_isPad'", nullptr);
            return 0;
        }
        bool ret = LuaController::isPad();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:isPad",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_isPad'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createSprite(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:createSprite");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createSprite'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = LuaController::createSprite(arg0);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createSprite",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createSprite'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showTipsView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showTipsView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showTipsView'", nullptr);
            return 0;
        }
        LuaController::showTipsView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        std::string arg0;
        cocos2d::TextHAlignment arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showTipsView");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showTipsView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showTipsView'", nullptr);
            return 0;
        }
        LuaController::showTipsView(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showTipsView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showTipsView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_flyText(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:flyText");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_flyText'", nullptr);
            return 0;
        }
        LuaController::flyText(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:flyText",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_flyText'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getToolInfoById(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getToolInfoById");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getToolInfoById'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getToolInfoById(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getToolInfoById",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getToolInfoById'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getCMDLang(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getCMDLang");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getCMDLang'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getCMDLang(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getCMDLang",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getCMDLang'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_callPaymentToFriend(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:callPaymentToFriend");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:callPaymentToFriend");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:callPaymentToFriend");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_callPaymentToFriend'", nullptr);
            return 0;
        }
        LuaController::callPaymentToFriend(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:callPaymentToFriend",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_callPaymentToFriend'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_removeAllPopupView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_removeAllPopupView'", nullptr);
            return 0;
        }
        LuaController::removeAllPopupView();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:removeAllPopupView",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_removeAllPopupView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getCombatINfoData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getCombatINfoData'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getCombatINfoData();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getCombatINfoData",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getCombatINfoData'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getResGlodByType(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:getResGlodByType");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:getResGlodByType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getResGlodByType'", nullptr);
            return 0;
        }
        int ret = LuaController::getResGlodByType(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getResGlodByType",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getResGlodByType'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addIconByType(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 5)
    {
        cocos2d::Node* arg0;
        std::string arg1;
        cocos2d::Label* arg2;
        int arg3;
        int arg4;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:addIconByType");
        ok &= luaval_to_object<cocos2d::Label>(tolua_S, 4, "cc.Label",&arg2);
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:addIconByType");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:addIconByType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addIconByType'", nullptr);
            return 0;
        }
        LuaController::addIconByType(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addIconByType",argc, 5);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addIconByType'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showHelpShiftFAQ(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showHelpShiftFAQ");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showHelpShiftFAQ'", nullptr);
            return 0;
        }
        LuaController::showHelpShiftFAQ(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showHelpShiftFAQ",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showHelpShiftFAQ'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_sendInfoToServer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_sendInfoToServer'", nullptr);
            return 0;
        }
        LuaController::sendInfoToServer();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:sendInfoToServer",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_sendInfoToServer'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_CombatClearDate(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_CombatClearDate'", nullptr);
            return 0;
        }
        LuaController::CombatClearDate();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:CombatClearDate",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_CombatClearDate'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addPopupInView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addPopupInView'", nullptr);
            return 0;
        }
        LuaController::addPopupInView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addPopupInView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addPopupInView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_setSpriteGray(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Sprite* arg0;
        bool arg1;
        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "LuaController:setSpriteGray");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setSpriteGray'", nullptr);
            return 0;
        }
        LuaController::setSpriteGray(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:setSpriteGray",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setSpriteGray'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addPopupView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addPopupView'", nullptr);
            return 0;
        }
        LuaController::addPopupView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addPopupView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addPopupView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_playEffects(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:playEffects");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_playEffects'", nullptr);
            return 0;
        }
        LuaController::playEffects(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:playEffects",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_playEffects'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_setTitleName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:setTitleName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setTitleName'", nullptr);
            return 0;
        }
        LuaController::setTitleName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:setTitleName",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setTitleName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getScale9SpriteSize(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::ui::Scale9Sprite* arg0;
        ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 2, "ccui.Scale9Sprite",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getScale9SpriteSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = LuaController::getScale9SpriteSize(arg0);
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getScale9SpriteSize",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getScale9SpriteSize'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_toCreateSliderView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:toCreateSliderView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_toCreateSliderView'", nullptr);
            return 0;
        }
        LuaController::toCreateSliderView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:toCreateSliderView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_toCreateSliderView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createParticleForLua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "LuaController:createParticleForLua"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createParticleForLua'", nullptr);
            return 0;
        }
        cocos2d::ParticleSystemQuad* ret = LuaController::createParticleForLua(arg0);
        object_to_luaval<cocos2d::ParticleSystemQuad>(tolua_S, "cc.ParticleSystemQuad",(cocos2d::ParticleSystemQuad*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createParticleForLua",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createParticleForLua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getPlayerCountryFlag(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getPlayerCountryFlag'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = LuaController::getPlayerCountryFlag();
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getPlayerCountryFlag'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = LuaController::getPlayerCountryFlag(arg0);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getPlayerCountryFlag",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getPlayerCountryFlag'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_autoDoResourceEquipIcon(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_autoDoResourceEquipIcon'", nullptr);
            return 0;
        }
        LuaController::autoDoResourceEquipIcon(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:autoDoResourceEquipIcon",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_autoDoResourceEquipIcon'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getRandPackage(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getRandPackage'", nullptr);
            return 0;
        }
        LuaController::getRandPackage();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getRandPackage",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getRandPackage'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createScale9Sprite(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "LuaController:createScale9Sprite"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createScale9Sprite'", nullptr);
            return 0;
        }
        cocos2d::ui::Scale9Sprite* ret = LuaController::createScale9Sprite(arg0);
        object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createScale9Sprite",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createScale9Sprite'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addSkeletonAnimation(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 5)
    {
        cocos2d::Node* arg0;
        const char* arg1;
        const char* arg2;
        const char* arg3;
        double arg4;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "LuaController:addSkeletonAnimation"); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "LuaController:addSkeletonAnimation"); arg2 = arg2_tmp.c_str();
        std::string arg3_tmp; ok &= luaval_to_std_string(tolua_S, 5, &arg3_tmp, "LuaController:addSkeletonAnimation"); arg3 = arg3_tmp.c_str();
        ok &= luaval_to_number(tolua_S, 6,&arg4, "LuaController:addSkeletonAnimation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addSkeletonAnimation'", nullptr);
            return 0;
        }
        LuaController::addSkeletonAnimation(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addSkeletonAnimation",argc, 5);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addSkeletonAnimation'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getLang(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getLang");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getLang'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getLang(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    if (argc == 2)
    {
        std::string arg0;
        bool arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getLang");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "LuaController:getLang");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getLang'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getLang(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getLang",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getLang'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_callPayRandRackage(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_callPayRandRackage'", nullptr);
            return 0;
        }
        LuaController::callPayRandRackage();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:callPayRandRackage",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_callPayRandRackage'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getResourceNameByType(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:getResourceNameByType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getResourceNameByType'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getResourceNameByType(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getResourceNameByType",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getResourceNameByType'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_removeLastPopup(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_removeLastPopup'", nullptr);
            return 0;
        }
        LuaController::removeLastPopup();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:removeLastPopup",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_removeLastPopup'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showAcceleratePropsView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showAcceleratePropsView");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showAcceleratePropsView");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showAcceleratePropsView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showAcceleratePropsView'", nullptr);
            return 0;
        }
        LuaController::showAcceleratePropsView(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showAcceleratePropsView",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showAcceleratePropsView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getBuildingInforByItemID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:getBuildingInforByItemID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getBuildingInforByItemID'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getBuildingInforByItemID(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getBuildingInforByItemID",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getBuildingInforByItemID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_luaToRandomGift(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_luaToRandomGift'", nullptr);
            return 0;
        }
        LuaController::luaToRandomGift();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:luaToRandomGift",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_luaToRandomGift'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_setPopupTitleName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:setPopupTitleName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setPopupTitleName'", nullptr);
            return 0;
        }
        LuaController::setPopupTitleName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:setPopupTitleName",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setPopupTitleName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showToastDescription(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showToastDescription");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showToastDescription'", nullptr);
            return 0;
        }
        LuaController::showToastDescription(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        std::string arg0;
        cocos2d::Node* arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showToastDescription");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showToastDescription'", nullptr);
            return 0;
        }
        LuaController::showToastDescription(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg0;
        cocos2d::Node* arg1;
        cocos2d::Node* arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showToastDescription");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showToastDescription'", nullptr);
            return 0;
        }
        LuaController::showToastDescription(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 4)
    {
        std::string arg0;
        cocos2d::Node* arg1;
        cocos2d::Node* arg2;
        std::string arg3;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showToastDescription");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2);
        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "LuaController:showToastDescription");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showToastDescription'", nullptr);
            return 0;
        }
        LuaController::showToastDescription(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 5)
    {
        std::string arg0;
        cocos2d::Node* arg1;
        cocos2d::Node* arg2;
        std::string arg3;
        std::string arg4;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showToastDescription");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2);
        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "LuaController:showToastDescription");
        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "LuaController:showToastDescription");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showToastDescription'", nullptr);
            return 0;
        }
        LuaController::showToastDescription(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 6)
    {
        std::string arg0;
        cocos2d::Node* arg1;
        cocos2d::Node* arg2;
        std::string arg3;
        std::string arg4;
        std::string arg5;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showToastDescription");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2);
        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "LuaController:showToastDescription");
        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "LuaController:showToastDescription");
        ok &= luaval_to_std_string(tolua_S, 7,&arg5, "LuaController:showToastDescription");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showToastDescription'", nullptr);
            return 0;
        }
        LuaController::showToastDescription(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showToastDescription",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showToastDescription'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showDialoginfo(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showDialoginfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showDialoginfo'", nullptr);
            return 0;
        }
        LuaController::showDialoginfo(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 7)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showDialoginfo");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showDialoginfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showDialoginfo'", nullptr);
            return 0;
        }
        LuaController::showDialoginfo(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 8)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        std::string arg7;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showDialoginfo");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showDialoginfo");
        ok &= luaval_to_std_string(tolua_S, 9,&arg7, "LuaController:showDialoginfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showDialoginfo'", nullptr);
            return 0;
        }
        LuaController::showDialoginfo(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 9)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        std::string arg7;
        int arg8;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showDialoginfo");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showDialoginfo");
        ok &= luaval_to_std_string(tolua_S, 9,&arg7, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 10,(int *)&arg8, "LuaController:showDialoginfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showDialoginfo'", nullptr);
            return 0;
        }
        LuaController::showDialoginfo(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 10)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        std::string arg7;
        int arg8;
        int arg9;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showDialoginfo");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showDialoginfo");
        ok &= luaval_to_std_string(tolua_S, 9,&arg7, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 10,(int *)&arg8, "LuaController:showDialoginfo");
        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "LuaController:showDialoginfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showDialoginfo'", nullptr);
            return 0;
        }
        LuaController::showDialoginfo(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showDialoginfo",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showDialoginfo'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getGlobalData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getGlobalData'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getGlobalData();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getGlobalData",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getGlobalData'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createGoodsIcon(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:createGoodsIcon");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:createGoodsIcon");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createGoodsIcon'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = LuaController::createGoodsIcon(arg0, arg1);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createGoodsIcon",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createGoodsIcon'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_doResourceByCommonIndex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        bool arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:doResourceByCommonIndex");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "LuaController:doResourceByCommonIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_doResourceByCommonIndex'", nullptr);
            return 0;
        }
        LuaController::doResourceByCommonIndex(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:doResourceByCommonIndex",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_doResourceByCommonIndex'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showSpecialSoldierView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showSpecialSoldierView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showSpecialSoldierView'", nullptr);
            return 0;
        }
        LuaController::showSpecialSoldierView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showSpecialSoldierView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showSpecialSoldierView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_fireForRescue(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:fireForRescue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_fireForRescue'", nullptr);
            return 0;
        }
        LuaController::fireForRescue(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:fireForRescue",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_fireForRescue'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createButtonGoldExchange(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        cocos2d::Node* arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:createButtonGoldExchange");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createButtonGoldExchange'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::createButtonGoldExchange(arg0, arg1);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createButtonGoldExchange",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createButtonGoldExchange'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_toSelectUser(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        bool arg1;
        int arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:toSelectUser");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "LuaController:toSelectUser");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:toSelectUser");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_toSelectUser'", nullptr);
            return 0;
        }
        LuaController::toSelectUser(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:toSelectUser",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_toSelectUser'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showWaitInterface(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showWaitInterface'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::showWaitInterface(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showWaitInterface",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showWaitInterface'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_setScale9SpriteSize(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::ui::Scale9Sprite* arg0;
        cocos2d::Size arg1;
        ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 2, "ccui.Scale9Sprite",&arg0);
        ok &= luaval_to_size(tolua_S, 3, &arg1, "LuaController:setScale9SpriteSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setScale9SpriteSize'", nullptr);
            return 0;
        }
        LuaController::setScale9SpriteSize(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:setScale9SpriteSize",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setScale9SpriteSize'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showDetailPopUpView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showDetailPopUpView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showDetailPopUpView'", nullptr);
            return 0;
        }
        LuaController::showDetailPopUpView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showDetailPopUpView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showDetailPopUpView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_SetUseResToolViewNeedNum(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:SetUseResToolViewNeedNum");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:SetUseResToolViewNeedNum");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_SetUseResToolViewNeedNum'", nullptr);
            return 0;
        }
        LuaController::SetUseResToolViewNeedNum(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:SetUseResToolViewNeedNum",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_SetUseResToolViewNeedNum'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getSECLang(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:getSECLang");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getSECLang'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getSECLang(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getSECLang",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getSECLang'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getSkillInfoBySoldierType(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:getSkillInfoBySoldierType");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:getSkillInfoBySoldierType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getSkillInfoBySoldierType'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getSkillInfoBySoldierType(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getSkillInfoBySoldierType",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getSkillInfoBySoldierType'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addButtonLight(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addButtonLight'", nullptr);
            return 0;
        }
        LuaController::addButtonLight(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addButtonLight",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addButtonLight'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_RescueCommand(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:RescueCommand");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_RescueCommand'", nullptr);
            return 0;
        }
        LuaController::RescueCommand(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:RescueCommand",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_RescueCommand'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_checkSkeletonFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "LuaController:checkSkeletonFile"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_checkSkeletonFile'", nullptr);
            return 0;
        }
        bool ret = LuaController::checkSkeletonFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:checkSkeletonFile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_checkSkeletonFile'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getSoldierSpine(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getSoldierSpine");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getSoldierSpine'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::getSoldierSpine(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getSoldierSpine",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getSoldierSpine'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getGoldItemChooseIndex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getGoldItemChooseIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getGoldItemChooseIndex'", nullptr);
            return 0;
        }
        int ret = LuaController::getGoldItemChooseIndex(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getGoldItemChooseIndex",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getGoldItemChooseIndex'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_callPayment(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:callPayment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_callPayment'", nullptr);
            return 0;
        }
        LuaController::callPayment(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:callPayment");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:callPayment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_callPayment'", nullptr);
            return 0;
        }
        LuaController::callPayment(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:callPayment");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:callPayment");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:callPayment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_callPayment'", nullptr);
            return 0;
        }
        LuaController::callPayment(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:callPayment",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_callPayment'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_autoDoResourceByPath(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        cocos2d::Node* arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:autoDoResourceByPath");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_autoDoResourceByPath'", nullptr);
            return 0;
        }
        LuaController::autoDoResourceByPath(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:autoDoResourceByPath",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_autoDoResourceByPath'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_retReward(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::__Array* arg0;
        ok &= luaval_to_object<cocos2d::__Array>(tolua_S, 2, "cc.__Array",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_retReward'", nullptr);
            return 0;
        }
        std::string ret = LuaController::retReward(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:retReward",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_retReward'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addGoldExchangeViewByType(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:addGoldExchangeViewByType");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:addGoldExchangeViewByType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addGoldExchangeViewByType'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::addGoldExchangeViewByType(arg0, arg1);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addGoldExchangeViewByType",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addGoldExchangeViewByType'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getResData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getResData'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getResData();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getResData",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getResData'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getXMLData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getXMLData");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:getXMLData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getXMLData'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getXMLData(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getXMLData",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getXMLData'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_setButtonTitle(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Node* arg0;
        std::string arg1;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:setButtonTitle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_setButtonTitle'", nullptr);
            return 0;
        }
        LuaController::setButtonTitle(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:setButtonTitle",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_setButtonTitle'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getLang1(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getLang1");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:getLang1");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getLang1'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getLang1(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getLang1",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getLang1'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getObjectType(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Ref* arg0;
        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getObjectType'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getObjectType(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getObjectType",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getObjectType'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createSoldierCell(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:createSoldierCell");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createSoldierCell'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::createSoldierCell(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createSoldierCell",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createSoldierCell'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showButtonAndGold(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        std::string arg3;
        std::string arg4;
        std::string arg5;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showButtonAndGold");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:showButtonAndGold");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showButtonAndGold");
        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "LuaController:showButtonAndGold");
        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "LuaController:showButtonAndGold");
        ok &= luaval_to_std_string(tolua_S, 7,&arg5, "LuaController:showButtonAndGold");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showButtonAndGold'", nullptr);
            return 0;
        }
        LuaController::showButtonAndGold(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 7)
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        std::string arg3;
        std::string arg4;
        std::string arg5;
        bool arg6;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:showButtonAndGold");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:showButtonAndGold");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showButtonAndGold");
        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "LuaController:showButtonAndGold");
        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "LuaController:showButtonAndGold");
        ok &= luaval_to_std_string(tolua_S, 7,&arg5, "LuaController:showButtonAndGold");
        ok &= luaval_to_boolean(tolua_S, 8,&arg6, "LuaController:showButtonAndGold");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showButtonAndGold'", nullptr);
            return 0;
        }
        LuaController::showButtonAndGold(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showButtonAndGold",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showButtonAndGold'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showAccView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showAccView'", nullptr);
            return 0;
        }
        LuaController::showAccView();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showAccView",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showAccView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getArmyInfoByArmyID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getArmyInfoByArmyID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getArmyInfoByArmyID'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getArmyInfoByArmyID(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getArmyInfoByArmyID",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getArmyInfoByArmyID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getHireArmyShopData(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getHireArmyShopData'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getHireArmyShopData();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getHireArmyShopData",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getHireArmyShopData'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addSoldierSkillInfoPopUpView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        std::string arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:addSoldierSkillInfoPopUpView");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:addSoldierSkillInfoPopUpView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addSoldierSkillInfoPopUpView'", nullptr);
            return 0;
        }
        LuaController::addSoldierSkillInfoPopUpView(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addSoldierSkillInfoPopUpView",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addSoldierSkillInfoPopUpView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getPlatform(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getPlatform'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getPlatform();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getPlatform",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getPlatform'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_autoDoResourceByCommonIndex(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        cocos2d::Node* arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:autoDoResourceByCommonIndex");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_autoDoResourceByCommonIndex'", nullptr);
            return 0;
        }
        LuaController::autoDoResourceByCommonIndex(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:autoDoResourceByCommonIndex",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_autoDoResourceByCommonIndex'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getGoldExchangeDataByType(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:getGoldExchangeDataByType");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:getGoldExchangeDataByType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getGoldExchangeDataByType'", nullptr);
            return 0;
        }
        int ret = LuaController::getGoldExchangeDataByType(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getGoldExchangeDataByType",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getGoldExchangeDataByType'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_createPopupBaseView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_createPopupBaseView'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = LuaController::createPopupBaseView();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:createPopupBaseView",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_createPopupBaseView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_flyHint(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:flyHint");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:flyHint");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "LuaController:flyHint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_flyHint'", nullptr);
            return 0;
        }
        LuaController::flyHint(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:flyHint",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_flyHint'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getEffectValueByNum(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        bool arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:getEffectValueByNum");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "LuaController:getEffectValueByNum");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getEffectValueByNum'", nullptr);
            return 0;
        }
        double ret = LuaController::getEffectValueByNum(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getEffectValueByNum",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getEffectValueByNum'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_onBtnFree(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:onBtnFree");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_onBtnFree'", nullptr);
            return 0;
        }
        LuaController::onBtnFree(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:onBtnFree",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_onBtnFree'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_addTipsView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:addTipsView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_addTipsView'", nullptr);
            return 0;
        }
        LuaController::addTipsView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:addTipsView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_addTipsView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_openBagView(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:openBagView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_openBagView'", nullptr);
            return 0;
        }
        LuaController::openBagView(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:openBagView",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_openBagView'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_bIsHireArmyState(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_bIsHireArmyState'", nullptr);
            return 0;
        }
        bool ret = LuaController::bIsHireArmyState();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:bIsHireArmyState",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_bIsHireArmyState'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_showConfirmDialog(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showConfirmDialog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showConfirmDialog'", nullptr);
            return 0;
        }
        LuaController::showConfirmDialog(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 7)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showConfirmDialog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showConfirmDialog'", nullptr);
            return 0;
        }
        LuaController::showConfirmDialog(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 8)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        std::string arg7;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 9,&arg7, "LuaController:showConfirmDialog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showConfirmDialog'", nullptr);
            return 0;
        }
        LuaController::showConfirmDialog(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 9)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        std::string arg7;
        std::string arg8;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 9,&arg7, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 10,&arg8, "LuaController:showConfirmDialog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showConfirmDialog'", nullptr);
            return 0;
        }
        LuaController::showConfirmDialog(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 10)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        std::string arg7;
        std::string arg8;
        int arg9;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 9,&arg7, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 10,&arg8, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "LuaController:showConfirmDialog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showConfirmDialog'", nullptr);
            return 0;
        }
        LuaController::showConfirmDialog(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 11)
    {
        int arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;
        std::string arg6;
        std::string arg7;
        std::string arg8;
        int arg9;
        int arg10;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 8,&arg6, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 9,&arg7, "LuaController:showConfirmDialog");
        ok &= luaval_to_std_string(tolua_S, 10,&arg8, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "LuaController:showConfirmDialog");
        ok &= luaval_to_int32(tolua_S, 12,(int *)&arg10, "LuaController:showConfirmDialog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_showConfirmDialog'", nullptr);
            return 0;
        }
        LuaController::showConfirmDialog(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:showConfirmDialog",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_showConfirmDialog'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_ShowResourceBar(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "LuaController:ShowResourceBar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_ShowResourceBar'", nullptr);
            return 0;
        }
        LuaController::ShowResourceBar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:ShowResourceBar",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_ShowResourceBar'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_getDollarString(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "LuaController:getDollarString");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "LuaController:getDollarString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_getDollarString'", nullptr);
            return 0;
        }
        std::string ret = LuaController::getDollarString(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "LuaController:getDollarString",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_getDollarString'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_if_LuaController_constructor(lua_State* tolua_S)
{
    int argc = 0;
    LuaController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_if_LuaController_constructor'", nullptr);
            return 0;
        }
        cobj = new LuaController();
        tolua_pushusertype(tolua_S,(void*)cobj,"LuaController");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "LuaController:LuaController",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_if_LuaController_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_if_LuaController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LuaController)");
    return 0;
}

int lua_register_cocos2dx_if_LuaController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"LuaController");
    tolua_cclass(tolua_S,"LuaController","LuaController","cc.CCObject",nullptr);

    tolua_beginmodule(tolua_S,"LuaController");
        tolua_function(tolua_S,"new",lua_cocos2dx_if_LuaController_constructor);
        tolua_function(tolua_S,"ChatNoticeInView",lua_cocos2dx_if_LuaController_ChatNoticeInView);
        tolua_function(tolua_S,"backToExchange",lua_cocos2dx_if_LuaController_backToExchange);
        tolua_function(tolua_S,"createExchangeIcon",lua_cocos2dx_if_LuaController_createExchangeIcon);
        tolua_function(tolua_S,"refreshRandView",lua_cocos2dx_if_LuaController_refreshRandView);
        tolua_function(tolua_S,"canTranslate",lua_cocos2dx_if_LuaController_canTranslate);
        tolua_function(tolua_S,"recvGoldExchangeNetMsg",lua_cocos2dx_if_LuaController_recvGoldExchangeNetMsg);
        tolua_function(tolua_S,"backCMD",lua_cocos2dx_if_LuaController_backCMD);
        tolua_function(tolua_S,"showRescueView",lua_cocos2dx_if_LuaController_showRescueView);
        tolua_function(tolua_S,"updateExchangeGiftInfo",lua_cocos2dx_if_LuaController_updateExchangeGiftInfo);
        tolua_function(tolua_S,"showCombatSliderSpeView",lua_cocos2dx_if_LuaController_showCombatSliderSpeView);
        tolua_function(tolua_S,"getAdvCellContainer",lua_cocos2dx_if_LuaController_getAdvCellContainer);
        tolua_function(tolua_S,"getChatNoticeContainer",lua_cocos2dx_if_LuaController_getChatNoticeContainer);
        tolua_function(tolua_S,"changeUI",lua_cocos2dx_if_LuaController_changeUI);
        tolua_function(tolua_S,"closeChatNotice",lua_cocos2dx_if_LuaController_closeChatNotice);
        tolua_function(tolua_S,"initLua",lua_cocos2dx_if_LuaController_initLua);
        tolua_function(tolua_S,"getPayFun",lua_cocos2dx_if_LuaController_getPayFun);
        tolua_function(tolua_S,"checkLuaValid",lua_cocos2dx_if_LuaController_checkLuaValid);
        tolua_function(tolua_S,"ChatNoticeInSceen",lua_cocos2dx_if_LuaController_ChatNoticeInSceen);
        tolua_function(tolua_S,"canSendExchange",lua_cocos2dx_if_LuaController_canSendExchange);
        tolua_function(tolua_S,"getActExcData",lua_cocos2dx_if_LuaController_getActExcData);
        tolua_function(tolua_S,"getLoginTime",lua_cocos2dx_if_LuaController_getLoginTime);
        tolua_function(tolua_S,"checkResValid",lua_cocos2dx_if_LuaController_checkResValid);
        tolua_function(tolua_S,"addSystemUpdate",lua_cocos2dx_if_LuaController_addSystemUpdate);
        tolua_function(tolua_S,"recvLuaNetMessage",lua_cocos2dx_if_LuaController_recvLuaNetMessage);
        tolua_function(tolua_S,"createActivityAdCell",lua_cocos2dx_if_LuaController_createActivityAdCell);
        tolua_function(tolua_S,"getIconContainer",lua_cocos2dx_if_LuaController_getIconContainer);
        tolua_function(tolua_S,"isLuaOpen",lua_cocos2dx_if_LuaController_isLuaOpen);
        tolua_function(tolua_S,"getAdvCell",lua_cocos2dx_if_LuaController_getAdvCell);
        tolua_function(tolua_S,"createActivityListCellSprite",lua_cocos2dx_if_LuaController_createActivityListCellSprite);
        tolua_function(tolua_S,"showAllHireSoldiers",lua_cocos2dx_if_LuaController_showAllHireSoldiers);
        tolua_function(tolua_S,"RandomForGift",lua_cocos2dx_if_LuaController_RandomForGift);
        tolua_function(tolua_S,"createActivityView",lua_cocos2dx_if_LuaController_createActivityView);
        tolua_function(tolua_S,"getPopupTop",lua_cocos2dx_if_LuaController_getPopupTop);
        tolua_function(tolua_S,"setPopupBot",lua_cocos2dx_if_LuaController_setPopupBot);
        tolua_function(tolua_S,"showCombatSliderView",lua_cocos2dx_if_LuaController_showCombatSliderView);
        tolua_function(tolua_S,"addSoldierInfoView",lua_cocos2dx_if_LuaController_addSoldierInfoView);
        tolua_function(tolua_S,"getIsPaying",lua_cocos2dx_if_LuaController_getIsPaying);
        tolua_function(tolua_S,"showSceneNotice",lua_cocos2dx_if_LuaController_showSceneNotice);
        tolua_function(tolua_S,"initExchangeGiftInfo",lua_cocos2dx_if_LuaController_initExchangeGiftInfo);
        tolua_function(tolua_S,"updateRandItem",lua_cocos2dx_if_LuaController_updateRandItem);
        tolua_function(tolua_S,"showGoldRandView",lua_cocos2dx_if_LuaController_showGoldRandView);
        tolua_function(tolua_S,"unzipFinish",lua_cocos2dx_if_LuaController_unzipFinish);
        tolua_function(tolua_S,"setIsPaying",lua_cocos2dx_if_LuaController_setIsPaying);
        tolua_function(tolua_S,"setLoginTime",lua_cocos2dx_if_LuaController_setLoginTime);
        tolua_function(tolua_S,"changeChatNotice",lua_cocos2dx_if_LuaController_changeChatNotice);
        tolua_function(tolua_S,"downloadFinish",lua_cocos2dx_if_LuaController_downloadFinish);
        tolua_function(tolua_S,"updateTroopsChange",lua_cocos2dx_if_LuaController_updateTroopsChange);
        tolua_function(tolua_S,"showExchangeSale",lua_cocos2dx_if_LuaController_showExchangeSale);
        tolua_function(tolua_S,"clearChatNotice",lua_cocos2dx_if_LuaController_clearChatNotice);
        tolua_function(tolua_S,"createExchangeRandIcon",lua_cocos2dx_if_LuaController_createExchangeRandIcon);
        tolua_function(tolua_S,"showHireArmyView",lua_cocos2dx_if_LuaController_showHireArmyView);
        tolua_function(tolua_S,"getPopupBot",lua_cocos2dx_if_LuaController_getPopupBot);
        tolua_function(tolua_S,"createExchangeAdvCell",lua_cocos2dx_if_LuaController_createExchangeAdvCell);
        tolua_function(tolua_S,"createActivityRwdView",lua_cocos2dx_if_LuaController_createActivityRwdView);
        tolua_function(tolua_S,"showActRwdViewByActId",lua_cocos2dx_if_LuaController_showActRwdViewByActId);
        tolua_function(tolua_S,"setPopupTop",lua_cocos2dx_if_LuaController_setPopupTop);
        tolua_function(tolua_S,"sendCMD",lua_cocos2dx_if_LuaController_sendCMD);
        tolua_function(tolua_S,"pushResItemToVec",lua_cocos2dx_if_LuaController_pushResItemToVec);
        tolua_function(tolua_S,"showCombatPopView",lua_cocos2dx_if_LuaController_showCombatPopView);
        tolua_function(tolua_S,"addChatNotice",lua_cocos2dx_if_LuaController_addChatNotice);
        tolua_function(tolua_S,"updateExchangeAdvCell",lua_cocos2dx_if_LuaController_updateExchangeAdvCell);
        tolua_function(tolua_S,"checkActLuaValid",lua_cocos2dx_if_LuaController_checkActLuaValid);
        tolua_function(tolua_S,"getSaleViewContainer",lua_cocos2dx_if_LuaController_getSaleViewContainer);
        tolua_function(tolua_S,"ShowInfoCellSprite", lua_cocos2dx_if_LuaController_ShowInfoCellSprite);
        tolua_function(tolua_S,"showUseResToolView", lua_cocos2dx_if_LuaController_showUseResToolView);
        tolua_function(tolua_S,"getDiamondImm", lua_cocos2dx_if_LuaController_getDiamondImm);
        tolua_function(tolua_S,"isGM", lua_cocos2dx_if_LuaController_isGM);
        tolua_function(tolua_S,"sendMsg", lua_cocos2dx_if_LuaController_sendMsg);
        tolua_function(tolua_S,"showDetailPopup", lua_cocos2dx_if_LuaController_showDetailPopup);
        tolua_function(tolua_S,"addArmyToRescue", lua_cocos2dx_if_LuaController_addArmyToRescue);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_if_LuaController_getInstance);
        tolua_function(tolua_S,"addItemIcon", lua_cocos2dx_if_LuaController_addItemIcon);
        tolua_function(tolua_S,"removePopupView", lua_cocos2dx_if_LuaController_removePopupView);
        tolua_function(tolua_S,"autoDoResourceItemIcon", lua_cocos2dx_if_LuaController_autoDoResourceItemIcon);
        tolua_function(tolua_S,"getGoodsInfo", lua_cocos2dx_if_LuaController_getGoodsInfo);
        tolua_function(tolua_S,"SendCombatData", lua_cocos2dx_if_LuaController_SendCombatData);
        tolua_function(tolua_S,"getFreeVipRefreshArmy", lua_cocos2dx_if_LuaController_getFreeVipRefreshArmy);
        tolua_function(tolua_S,"createClipNode", lua_cocos2dx_if_LuaController_createClipNode);
        tolua_function(tolua_S,"createPopupView", lua_cocos2dx_if_LuaController_createPopupView);
        tolua_function(tolua_S,"getLuaEncryptDownloadUrl", lua_cocos2dx_if_LuaController_getLuaEncryptDownloadUrl);
        tolua_function(tolua_S,"getHireQueueInfo", lua_cocos2dx_if_LuaController_getHireQueueInfo);
        tolua_function(tolua_S,"getTimeStamp", lua_cocos2dx_if_LuaController_getTimeStamp);
        tolua_function(tolua_S,"setGoldItemParams", lua_cocos2dx_if_LuaController_setGoldItemParams);
        tolua_function(tolua_S,"getLuaViewVersion", lua_cocos2dx_if_LuaController_getLuaViewVersion);
        tolua_function(tolua_S,"removeAllPopup", lua_cocos2dx_if_LuaController_removeAllPopup);
        tolua_function(tolua_S,"getPlayerCountryName", lua_cocos2dx_if_LuaController_getPlayerCountryName);
        tolua_function(tolua_S,"showUpgradeUnlockDetailView", lua_cocos2dx_if_LuaController_showUpgradeUnlockDetailView);
        tolua_function(tolua_S,"getUTF8SubString", lua_cocos2dx_if_LuaController_getUTF8SubString);
        tolua_function(tolua_S,"getLanguage", lua_cocos2dx_if_LuaController_getLanguage);
        tolua_function(tolua_S,"getRescueINfoData", lua_cocos2dx_if_LuaController_getRescueINfoData);
        tolua_function(tolua_S,"getStringLength", lua_cocos2dx_if_LuaController_getStringLength);
        tolua_function(tolua_S,"getCMDParams", lua_cocos2dx_if_LuaController_getCMDParams);
        tolua_function(tolua_S,"postNotification", lua_cocos2dx_if_LuaController_postNotification);
        tolua_function(tolua_S,"getWorldTime", lua_cocos2dx_if_LuaController_getWorldTime);
        tolua_function(tolua_S,"addSoldierSkillInfoPopUpView2", lua_cocos2dx_if_LuaController_addSoldierSkillInfoPopUpView2);
        tolua_function(tolua_S,"isPad", lua_cocos2dx_if_LuaController_isPad);
        tolua_function(tolua_S,"createSprite", lua_cocos2dx_if_LuaController_createSprite);
        tolua_function(tolua_S,"showTipsView", lua_cocos2dx_if_LuaController_showTipsView);
        tolua_function(tolua_S,"flyText", lua_cocos2dx_if_LuaController_flyText);
        tolua_function(tolua_S,"getToolInfoById", lua_cocos2dx_if_LuaController_getToolInfoById);
        tolua_function(tolua_S,"getCMDLang", lua_cocos2dx_if_LuaController_getCMDLang);
        tolua_function(tolua_S,"callPaymentToFriend", lua_cocos2dx_if_LuaController_callPaymentToFriend);
        tolua_function(tolua_S,"removeAllPopupView", lua_cocos2dx_if_LuaController_removeAllPopupView);
        tolua_function(tolua_S,"getCombatINfoData", lua_cocos2dx_if_LuaController_getCombatINfoData);
        tolua_function(tolua_S,"getResGlodByType", lua_cocos2dx_if_LuaController_getResGlodByType);
        tolua_function(tolua_S,"addIconByType", lua_cocos2dx_if_LuaController_addIconByType);
        tolua_function(tolua_S,"showHelpShiftFAQ", lua_cocos2dx_if_LuaController_showHelpShiftFAQ);
        tolua_function(tolua_S,"sendInfoToServer", lua_cocos2dx_if_LuaController_sendInfoToServer);
        tolua_function(tolua_S,"CombatClearDate", lua_cocos2dx_if_LuaController_CombatClearDate);
        tolua_function(tolua_S,"addPopupInView", lua_cocos2dx_if_LuaController_addPopupInView);
        tolua_function(tolua_S,"setSpriteGray", lua_cocos2dx_if_LuaController_setSpriteGray);
        tolua_function(tolua_S,"addPopupView", lua_cocos2dx_if_LuaController_addPopupView);
        tolua_function(tolua_S,"playEffects", lua_cocos2dx_if_LuaController_playEffects);
        tolua_function(tolua_S,"setTitleName", lua_cocos2dx_if_LuaController_setTitleName);
        tolua_function(tolua_S,"getScale9SpriteSize", lua_cocos2dx_if_LuaController_getScale9SpriteSize);
        tolua_function(tolua_S,"toCreateSliderView", lua_cocos2dx_if_LuaController_toCreateSliderView);
        tolua_function(tolua_S,"createParticleForLua", lua_cocos2dx_if_LuaController_createParticleForLua);
        tolua_function(tolua_S,"getPlayerCountryFlag", lua_cocos2dx_if_LuaController_getPlayerCountryFlag);
        tolua_function(tolua_S,"autoDoResourceEquipIcon", lua_cocos2dx_if_LuaController_autoDoResourceEquipIcon);
        tolua_function(tolua_S,"getRandPackage", lua_cocos2dx_if_LuaController_getRandPackage);
        tolua_function(tolua_S,"createScale9Sprite", lua_cocos2dx_if_LuaController_createScale9Sprite);
        tolua_function(tolua_S,"addSkeletonAnimation", lua_cocos2dx_if_LuaController_addSkeletonAnimation);
        tolua_function(tolua_S,"getLang", lua_cocos2dx_if_LuaController_getLang);
        tolua_function(tolua_S,"callPayRandRackage", lua_cocos2dx_if_LuaController_callPayRandRackage);
        tolua_function(tolua_S,"getResourceNameByType", lua_cocos2dx_if_LuaController_getResourceNameByType);
        tolua_function(tolua_S,"removeLastPopup", lua_cocos2dx_if_LuaController_removeLastPopup);
        tolua_function(tolua_S,"showAcceleratePropsView", lua_cocos2dx_if_LuaController_showAcceleratePropsView);
        tolua_function(tolua_S,"getBuildingInforByItemID", lua_cocos2dx_if_LuaController_getBuildingInforByItemID);
        tolua_function(tolua_S,"luaToRandomGift", lua_cocos2dx_if_LuaController_luaToRandomGift);
        tolua_function(tolua_S,"setPopupTitleName", lua_cocos2dx_if_LuaController_setPopupTitleName);
        tolua_function(tolua_S,"showToastDescription", lua_cocos2dx_if_LuaController_showToastDescription);
        tolua_function(tolua_S,"showDialoginfo", lua_cocos2dx_if_LuaController_showDialoginfo);
        tolua_function(tolua_S,"getGlobalData", lua_cocos2dx_if_LuaController_getGlobalData);
        tolua_function(tolua_S,"createGoodsIcon", lua_cocos2dx_if_LuaController_createGoodsIcon);
        tolua_function(tolua_S,"doResourceByCommonIndex", lua_cocos2dx_if_LuaController_doResourceByCommonIndex);
        tolua_function(tolua_S,"showSpecialSoldierView", lua_cocos2dx_if_LuaController_showSpecialSoldierView);
        tolua_function(tolua_S,"fireForRescue", lua_cocos2dx_if_LuaController_fireForRescue);
        tolua_function(tolua_S,"createButtonGoldExchange", lua_cocos2dx_if_LuaController_createButtonGoldExchange);
        tolua_function(tolua_S,"toSelectUser", lua_cocos2dx_if_LuaController_toSelectUser);
        tolua_function(tolua_S,"showWaitInterface", lua_cocos2dx_if_LuaController_showWaitInterface);
        tolua_function(tolua_S,"setScale9SpriteSize", lua_cocos2dx_if_LuaController_setScale9SpriteSize);
        tolua_function(tolua_S,"showDetailPopUpView", lua_cocos2dx_if_LuaController_showDetailPopUpView);
        tolua_function(tolua_S,"SetUseResToolViewNeedNum", lua_cocos2dx_if_LuaController_SetUseResToolViewNeedNum);
        tolua_function(tolua_S,"getSECLang", lua_cocos2dx_if_LuaController_getSECLang);
        tolua_function(tolua_S,"getSkillInfoBySoldierType", lua_cocos2dx_if_LuaController_getSkillInfoBySoldierType);
        tolua_function(tolua_S,"addButtonLight", lua_cocos2dx_if_LuaController_addButtonLight);
        tolua_function(tolua_S,"RescueCommand", lua_cocos2dx_if_LuaController_RescueCommand);
        tolua_function(tolua_S,"checkSkeletonFile", lua_cocos2dx_if_LuaController_checkSkeletonFile);
        tolua_function(tolua_S,"getSoldierSpine", lua_cocos2dx_if_LuaController_getSoldierSpine);
        tolua_function(tolua_S,"getGoldItemChooseIndex", lua_cocos2dx_if_LuaController_getGoldItemChooseIndex);
        tolua_function(tolua_S,"callPayment", lua_cocos2dx_if_LuaController_callPayment);
        tolua_function(tolua_S,"autoDoResourceByPath", lua_cocos2dx_if_LuaController_autoDoResourceByPath);
        tolua_function(tolua_S,"retReward", lua_cocos2dx_if_LuaController_retReward);
        tolua_function(tolua_S,"addGoldExchangeViewByType", lua_cocos2dx_if_LuaController_addGoldExchangeViewByType);
        tolua_function(tolua_S,"getResData", lua_cocos2dx_if_LuaController_getResData);
        tolua_function(tolua_S,"getXMLData", lua_cocos2dx_if_LuaController_getXMLData);
        tolua_function(tolua_S,"setButtonTitle", lua_cocos2dx_if_LuaController_setButtonTitle);
        tolua_function(tolua_S,"getLang1", lua_cocos2dx_if_LuaController_getLang1);
        tolua_function(tolua_S,"getObjectType", lua_cocos2dx_if_LuaController_getObjectType);
        tolua_function(tolua_S,"createSoldierCell", lua_cocos2dx_if_LuaController_createSoldierCell);
        tolua_function(tolua_S,"showButtonAndGold", lua_cocos2dx_if_LuaController_showButtonAndGold);
        tolua_function(tolua_S,"showAccView", lua_cocos2dx_if_LuaController_showAccView);
        tolua_function(tolua_S,"getArmyInfoByArmyID", lua_cocos2dx_if_LuaController_getArmyInfoByArmyID);
        tolua_function(tolua_S,"getHireArmyShopData", lua_cocos2dx_if_LuaController_getHireArmyShopData);
        tolua_function(tolua_S,"addSoldierSkillInfoPopUpView", lua_cocos2dx_if_LuaController_addSoldierSkillInfoPopUpView);
        tolua_function(tolua_S,"getPlatform", lua_cocos2dx_if_LuaController_getPlatform);
        tolua_function(tolua_S,"autoDoResourceByCommonIndex", lua_cocos2dx_if_LuaController_autoDoResourceByCommonIndex);
        tolua_function(tolua_S,"getGoldExchangeDataByType", lua_cocos2dx_if_LuaController_getGoldExchangeDataByType);
        tolua_function(tolua_S,"createPopupBaseView", lua_cocos2dx_if_LuaController_createPopupBaseView);
        tolua_function(tolua_S,"flyHint", lua_cocos2dx_if_LuaController_flyHint);
        tolua_function(tolua_S,"getEffectValueByNum", lua_cocos2dx_if_LuaController_getEffectValueByNum);
        tolua_function(tolua_S,"onBtnFree", lua_cocos2dx_if_LuaController_onBtnFree);
        tolua_function(tolua_S,"addTipsView", lua_cocos2dx_if_LuaController_addTipsView);
        tolua_function(tolua_S,"openBagView", lua_cocos2dx_if_LuaController_openBagView);
        tolua_function(tolua_S,"bIsHireArmyState", lua_cocos2dx_if_LuaController_bIsHireArmyState);
        tolua_function(tolua_S,"showConfirmDialog", lua_cocos2dx_if_LuaController_showConfirmDialog);
        tolua_function(tolua_S,"ShowResourceBar", lua_cocos2dx_if_LuaController_ShowResourceBar);
        tolua_function(tolua_S,"getDollarString", lua_cocos2dx_if_LuaController_getDollarString);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(LuaController).name();
    g_luaType[typeName] = "LuaController";
    g_typeCast["LuaController"] = "LuaController";
    return 1;
}
TOLUA_API int register_all_cocos2dx_if(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_cocos2dx_if_CCSafeNotificationCenter(tolua_S);
	lua_register_cocos2dx_if_LuaController(tolua_S);
	lua_register_cocos2dx_if_ActivityEventObj(tolua_S);
	lua_register_cocos2dx_if_CCFlagWaveSprite(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

