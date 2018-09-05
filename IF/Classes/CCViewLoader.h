//
//  CCViewLoader.h
//  IF
//
//  Created by XQ on 2015-01-22.
//
//
#ifndef __COK__CCViewLoader__
#define __COK__CCViewLoader__

#include "CommonInclude.h"
#include "CCModelLayer.h"
#include "CCLabelIF.h"
#include "CCLabelIFBMFont.h"
#include "CCEditBoxLoader.h"
#include "CCAniNode.h"

#define RegDialogCtrl(NAME, MEMBERVARIABLE)     registerCtrl(NAME, (CCNode**)&(this->MEMBERVARIABLE))

#define RegDialogEventHandle(NAME, METHOD)      registerEventHandle(NAME, cccontrol_selector(METHOD))

template<typename T = CCIFTouchNode>
class CCViewLoader
: public T
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
//,public CCTargetedTouchDelegate
{
public:
    CCViewLoader() : T(), m_rootNode(nullptr), m_bTouchEnable(false), m_bSwallowsTouches(false), m_nTouchPriority(Touch_Popup)
    {
    }

    virtual ~CCViewLoader(){
        clear();
    }

    virtual bool init() {
        bool ret = T::init();
        if(ret) {
			loadfile();
        }
        return ret;
    }

	void loadfile() {
		m_rootNode = CCBLoadFile(ccbiName(), this, this);
		ccbiLoaded();
	}

    virtual void onEnter() {
        T::onEnter();
        if(m_bTouchEnable) {
            T::setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
            T::setTouchEnabled(true);
//            CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_nTouchPriority, m_bSwallowsTouches);
        }
    }

    virtual void onExit() {
        if(m_bTouchEnable) {
            T::setTouchEnabled(false);
//            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
        T::onExit();
    }

    virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
        return m_bTouchEnable;
    }

protected:
    virtual const char* ccbiName() const = 0;

    // cocosbuilder::CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) {
        return nullptr;
    }

    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) {
        std::map<std::string, SEL_CCControlHandler>::iterator iter = m_regEventHandle.find(pSelectorName);
        if(iter != m_regEventHandle.end()) {
            return iter->second;
        }
        return nullptr;
    }

    // cocosbuilder::CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* memberVariableName, CCNode* node) {
        CCLOG("find a control which named by %s", memberVariableName);
        if(memberVariableName && node) {
            CC_SAFE_RETAIN(node);
            m_allCtrl.insert(std::make_pair(memberVariableName, node));
        }
        std::map<std::string, CCNode**>::iterator iter = m_regCtrl.find(memberVariableName);
        if(iter != m_regCtrl.end()) {
            CCNode** ctrl = iter->second;
            if(*ctrl != node) {
                *ctrl = node;
                return true;
            }
        }
        return false;
    }

    virtual void ccbiLoaded() {}

    CCNode* getChildByName(const char* name) const {
        CCNode* ret = NULL;
        if(name) {
            std::map<std::string, CCNode*>::iterator iter = m_allCtrl.find(name);
            if(iter != m_allCtrl.end()) {
                return iter->second;
            }
        }
        return ret;
    }

protected:
    void registerEventHandle(const char* name, SEL_CCControlHandler fun) {
        if(m_regEventHandle.find(name) == m_regEventHandle.end()) {
            m_regEventHandle.insert(std::make_pair(name, fun));
        }
    }

    bool registerCtrl(const char* name, CCNode** ctrl) {
        if(m_regCtrl.find(name) == m_regCtrl.end()) {
            *ctrl = nullptr;
            m_regCtrl.insert(std::make_pair(name, ctrl));
            return true;
        }
        return false;
    }

private:
    void clear() {
        m_regEventHandle.clear();
        m_regCtrl.clear();
        if(!m_allCtrl.empty()) {
            std::map<std::string, CCNode*>::iterator iter = m_allCtrl.begin();
            while(iter != m_allCtrl.end()) {
                CCNode* node = iter->second;
                CC_SAFE_RELEASE_NULL(node);
                iter++;
            }
            m_allCtrl.clear();
        }
    }

protected:
	bool m_bSwallowsTouches;
    bool m_bTouchEnable;
    int  m_nTouchPriority;
    CCNode* m_rootNode;

private:
    std::map<std::string, CCNode*>  m_allCtrl;
    std::map<std::string, CCNode**> m_regCtrl;
    std::map<std::string, SEL_CCControlHandler> m_regEventHandle;
};

#endif /* defined(__COK__CCViewLoader__) */
