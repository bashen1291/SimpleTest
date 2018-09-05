
--------------------------------
-- @module LuaController
-- @extend CCObject
-- @parent_module 

--------------------------------
-- 
-- @function [parent=#LuaController] backToExchange 
-- @param self
-- @param #int backTo
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createExchangeIcon 
-- @param self
-- @param #cc.Node node
-- @param #string info
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] refreshRandView 
-- @param self
-- @param #string info
-- @param #bool isForCache
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] canTranslate 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] recvGoldExchangeNetMsg 
-- @param self
-- @param #string data
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] backCMD 
-- @param self
-- @param #string cmdName
-- @param #cc.__Dictionary dict
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showRescueView 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] updateExchangeGiftInfo 
-- @param self
-- @param #string toUID
-- @param #string itemid
-- @param #double sendTime
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getAdvCellContainer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getChatNoticeContainer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] changeUI 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] closeChatNotice 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] initLua 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] ChatNoticeInView 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] checkLuaValid 
-- @param self
-- @param #string popImg
-- @param #string md5
-- @param #string resType
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] ChatNoticeInSceen 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] canSendExchange 
-- @param self
-- @param #string itemid
-- @param #string uid
-- @param #string toName
-- @param #int type
-- @param #bool showTip
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getActExcData 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getLoginTime 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] checkResValid 
-- @param self
-- @param #string popImg
-- @param #string md5
-- @param #string resType
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addSystemUpdate 
-- @param self
-- @param #double countDown
-- @param #bool isLogin
-- @param #string tip
-- @param #int type
-- @param #string icon
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] recvLuaNetMessage 
-- @param self
-- @param #string data
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createActivityAdCell 
-- @param self
-- @param #ActivityEventObj obj
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getIconContainer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] isLuaOpen 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getAdvCell 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createActivityListCellSprite 
-- @param self
-- @param #ActivityEventObj obj
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showAllHireSoldiers 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] RandomForGift 
-- @param self
-- @param #bool isLogin
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createActivityView 
-- @param self
-- @param #ActivityEventObj obj
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getPopupTop 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setPopupBot 
-- @param self
-- @param #int var
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showCombatSliderView 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addSoldierInfoView 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getIsPaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showSceneNotice 
-- @param self
-- @param #bool b
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] initExchangeGiftInfo 
-- @param self
-- @param #cc.__Array arr
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] updateRandItem 
-- @param self
-- @param #GoldExchangeItem randItem
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showGoldRandView 
-- @param self
-- @param #cc.Node node
-- @param #string info
-- @param #bool isForCache
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] unzipFinish 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setIsPaying 
-- @param self
-- @param #bool isPay
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setLoginTime 
-- @param self
-- @param #int var
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] changeChatNotice 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] downloadFinish 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] updateTroopsChange 
-- @param self
-- @param #cc.Ref ref
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showExchangeSale 
-- @param self
-- @param #cc.Node node
-- @param #string info
-- @param #string swallowTouch
-- @param #string isTab
-- @param #string callFun
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] clearChatNotice 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createExchangeRandIcon 
-- @param self
-- @param #cc.Node node
-- @param #string info
-- @param #bool isForCache
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showHireArmyView 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getPopupBot 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createExchangeAdvCell 
-- @param self
-- @param #cc.Node node
-- @param #string info
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createActivityRwdView 
-- @param self
-- @param #ActivityEventObj obj
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showActRwdViewByActId 
-- @param self
-- @param #string actId
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setPopupTop 
-- @param self
-- @param #int var
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] sendCMD 
-- @param self
-- @param #string cmdName
-- @param #cc.__Dictionary dict
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] pushResItemToVec 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showCombatPopView 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addChatNotice 
-- @param self
-- @param #cc.__Dictionary dict
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] updateExchangeAdvCell 
-- @param self
-- @param #cc.Node node
-- @param #string info
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] checkActLuaValid 
-- @param self
-- @param #ActivityEventObj obj
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getSaleViewContainer 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] ShowInfoCellSprite 
-- @param self
-- @param #int LV
-- @param #string armId
-- @param #string num
-- @param #bool lock
-- @param #bool touch
-- @param #int unLockLv
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getDiamondImm 
-- @param self
-- @param #string armyId
-- @param #int num
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] isGM 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] sendMsg 
-- @param self
-- @param #string cmd
-- @param #string param
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] callPaymentToFriend 
-- @param self
-- @param #string itemid
-- @param #string touid
-- @param #string toName
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showDetailPopup 
-- @param self
-- @param #string itemid
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addArmyToRescue 
-- @param self
-- @param #string armyId
-- @param #int type
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getInstance 
-- @param self
-- @return LuaController#LuaController ret (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addItemIcon 
-- @param self
-- @param #cc.Node node
-- @param #string itemid
-- @param #cc.Label lable
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] removePopupView 
-- @param self
-- @param #cc.Node view
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] autoDoResourceItemIcon 
-- @param self
-- @param #cc.Node node
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getGoodsInfo 
-- @param self
-- @param #string itemId
-- @return __Dictionary#__Dictionary ret (return value: cc.__Dictionary)
        
--------------------------------
-- 
-- @function [parent=#LuaController] SendCombatData 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createPopupView 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getLuaEncryptDownloadUrl 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getHireQueueInfo 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getTimeStamp 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setGoldItemParams 
-- @param self
-- @param #string itemId
-- @param #string param
-- @param #string data
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getLuaViewVersion 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] removeAllPopup 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getPlayerCountryName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showUpgradeUnlockDetailView 
-- @param self
-- @param #string armyid
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getUTF8SubString 
-- @param self
-- @param #string str
-- @param #int start
-- @param #int end
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getLanguage 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showHelpShiftFAQ 
-- @param self
-- @param #string type
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getStringLength 
-- @param self
-- @param #string str
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getCMDParams 
-- @param self
-- @param #string cmdName
-- @return __Dictionary#__Dictionary ret (return value: cc.__Dictionary)
        
--------------------------------
-- 
-- @function [parent=#LuaController] postNotification 
-- @param self
-- @param #string _postKey
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getWorldTime 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addSoldierSkillInfoPopUpView2 
-- @param self
-- @param #string skillname
-- @param #string des
-- @param #string icon
-- @param #int level
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] isPad 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createSprite 
-- @param self
-- @param #string fileName
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#LuaController] flyText 
-- @param self
-- @param #string msg
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getToolInfoById 
-- @param self
-- @param #string itemId
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getCMDLang 
-- @param self
-- @param #string msg
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getRescueINfoData 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] removeAllPopupView 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getCombatINfoData 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getResGlodByType 
-- @param self
-- @param #int type
-- @param #int num
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addIconByType 
-- @param self
-- @param #cc.Node node
-- @param #string itemid
-- @param #cc.Label lable
-- @param #int type
-- @param #int size
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showTipsView 
-- @param self
-- @param #string 
-- @param #int align
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] sendInfoToServer 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] CombatClearDate 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addPopupInView 
-- @param self
-- @param #cc.Node view
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setSpriteGray 
-- @param self
-- @param #cc.Sprite sprite
-- @param #bool gray
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addPopupView 
-- @param self
-- @param #cc.Node view
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] playEffects 
-- @param self
-- @param #string name
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setTitleName 
-- @param self
-- @param #string _name
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] toCreateSliderView 
-- @param self
-- @param #int type
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createParticleForLua 
-- @param self
-- @param #char name
-- @return ParticleSystemQuad#ParticleSystemQuad ret (return value: cc.ParticleSystemQuad)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getPlayerCountryFlag 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#LuaController] autoDoResourceEquipIcon 
-- @param self
-- @param #cc.Node node
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getRandPackage 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createScale9Sprite 
-- @param self
-- @param #char fileName
-- @return Scale9Sprite#Scale9Sprite ret (return value: ccui.Scale9Sprite)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addSkeletonAnimation 
-- @param self
-- @param #cc.Node node
-- @param #char skeletonDataFile
-- @param #char atlasFile
-- @param #char animation
-- @param #float scale
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getLang 
-- @param self
-- @param #string msg
-- @param #bool debug
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] callPayRandRackage 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getResourceNameByType 
-- @param self
-- @param #int itemid
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] removeLastPopup 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showAcceleratePropsView 
-- @param self
-- @param #int queueType
-- @param #int buildId
-- @param #int queueId
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getBuildingInforByItemID 
-- @param self
-- @param #int bId
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] luaToRandomGift 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setPopupTitleName 
-- @param self
-- @param #string title
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showToastDescription 
-- @param self
-- @param #string itemid
-- @param #cc.Node pNode
-- @param #cc.Node root
-- @param #string name
-- @param #string des
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getGlobalData 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createGoodsIcon 
-- @param self
-- @param #string itemId
-- @param #int size
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#LuaController] doResourceByCommonIndex 
-- @param self
-- @param #int commonIndex
-- @param #bool isLoad
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] fireForRescue 
-- @param self
-- @param #string armyId
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createButtonGoldExchange 
-- @param self
-- @param #string itemId
-- @param #cc.Node parent
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] toSelectUser 
-- @param self
-- @param #string itemid
-- @param #bool removeAllPop
-- @param #int backTo
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showWaitInterface 
-- @param self
-- @param #cc.Node node
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showDetailPopUpView 
-- @param self
-- @param #string showType
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] SetUseResToolViewNeedNum 
-- @param self
-- @param #int _type
-- @param #int count
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getSECLang 
-- @param self
-- @param #int time
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getSkillInfoBySoldierType 
-- @param self
-- @param #int sType
-- @param #string pointType
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addButtonLight 
-- @param self
-- @param #cc.Node node
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] RescueCommand 
-- @param self
-- @param #int type
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] checkSkeletonFile 
-- @param self
-- @param #char fileName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getSoldierSpine 
-- @param self
-- @param #string itemId
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getGoldItemChooseIndex 
-- @param self
-- @param #string itemId
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] callPayment 
-- @param self
-- @param #string itemid
-- @param #string chooseItem
-- @param #string callFun
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] autoDoResourceByPath 
-- @param self
-- @param #string path
-- @param #cc.Node node
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] retReward 
-- @param self
-- @param #cc.__Array 
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addGoldExchangeViewByType 
-- @param self
-- @param #int showTypeMain
-- @param #int showTypeSub
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getResData 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getXMLData 
-- @param self
-- @param #string key
-- @param #string var
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] setButtonTitle 
-- @param self
-- @param #cc.Node node
-- @param #string msg
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getLang1 
-- @param self
-- @param #string msg
-- @param #string param
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getObjectType 
-- @param self
-- @param #cc.Ref obj
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createSoldierCell 
-- @param self
-- @param #string armyId
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showButtonAndGold 
-- @param self
-- @param #string content
-- @param #string buttonName
-- @param #int gold
-- @param #string desDialog
-- @param #string _type
-- @param #string params
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showAccView 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getArmyInfoByArmyID 
-- @param self
-- @param #string armyId
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getHireArmyShopData 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addSoldierSkillInfoPopUpView 
-- @param self
-- @param #int soliderType
-- @param #string pointType
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getPlatform 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] autoDoResourceByCommonIndex 
-- @param self
-- @param #int commonIndex
-- @param #cc.Node node
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getGoldExchangeDataByType 
-- @param self
-- @param #int showTypeMain
-- @param #int showTypeSub
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#LuaController] createPopupBaseView 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- 
-- @function [parent=#LuaController] flyHint 
-- @param self
-- @param #string icon
-- @param #string titleText
-- @param #string context
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] onBtnFree 
-- @param self
-- @param #string itemId
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] addTipsView 
-- @param self
-- @param #string msg
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] openBagView 
-- @param self
-- @param #int type
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] bIsHireArmyState 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LuaController] showConfirmDialog 
-- @param self
-- @param #int food
-- @param #int wood
-- @param #int iron
-- @param #int stone
-- @param #int money
-- @param #int gold
-- @param #string luaCommand
-- @param #string tips
-- @param #string btnName
-- @param #int chip
-- @param #int drawing
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] ShowResourceBar 
-- @param self
-- @param #bool visible
-- @return LuaController#LuaController self (return value: LuaController)
        
--------------------------------
-- 
-- @function [parent=#LuaController] getDollarString 
-- @param self
-- @param #string dollar
-- @param #string productId
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LuaController] LuaController 
-- @param self
-- @return LuaController#LuaController self (return value: LuaController)
        
return nil
