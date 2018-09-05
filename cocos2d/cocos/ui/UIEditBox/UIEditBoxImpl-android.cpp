/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UIEditBoxImpl-android.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "UIEditBox.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxBitmap.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "2d/CCLabel.h"
#include "base/ccUTF8.h"

NS_CC_BEGIN

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplAndroid(pEditBox);
}

EditBoxImplAndroid::EditBoxImplAndroid(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _label(nullptr)
, _labelPlaceHolder(nullptr)
, _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
, _editBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
, _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
, _colText(Color3B::WHITE)
, _colPlaceHolder(Color3B::GRAY)
, _maxLength(-1)
{
    
}

EditBoxImplAndroid::~EditBoxImplAndroid()
{
	
}

void EditBoxImplAndroid::doAnimationWhenKeyboardMove(float duration, float distance)
{ // don't need to be implemented on android platform.
	
}

static const int CC_EDIT_BOX_PADDING = 5;

bool EditBoxImplAndroid::initWithSize(const Size& size)
{
    int fontSize = getFontSizeAccordingHeightJni(size.height-12);
    _label = Label::create();
    _label->setSystemFontSize(size.height-12);
	// align the text vertically center
    _label->setAnchorPoint(Vec2(0, 0.5f));
    _label->setPosition(Vec2(CC_EDIT_BOX_PADDING, size.height / 2.0f));
    _label->setTextColor(_colText);
    _editBox->addChild(_label);
	
    _labelPlaceHolder = Label::create();
    _labelPlaceHolder->setSystemFontSize(size.height-12);
	// align the text vertically center
    _labelPlaceHolder->setAnchorPoint(Vec2(0, 0.5f));
    _labelPlaceHolder->setPosition(CC_EDIT_BOX_PADDING, size.height / 2.0f);
    _labelPlaceHolder->setVisible(false);
    _labelPlaceHolder->setTextColor(_colPlaceHolder);
    _editBox->addChild(_labelPlaceHolder);
    
    _editSize = size;
    return true;
}

void EditBoxImplAndroid::setFont(const char* pFontName, int fontSize)
{
	if(_label != NULL) {
		_label->setSystemFontName(pFontName);
		_label->setSystemFontSize(fontSize);
	}
	
	if(_labelPlaceHolder != NULL) {
		_labelPlaceHolder->setSystemFontName(pFontName);
		_labelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void EditBoxImplAndroid::setFontColor(const Color4B& color)
{
    _colText = color;
    _label->setTextColor(color);
}

void EditBoxImplAndroid::setPlaceholderFont(const char* pFontName, int fontSize)
{
	if(_labelPlaceHolder != NULL) {
		_labelPlaceHolder->setSystemFontName(pFontName);
		_labelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void EditBoxImplAndroid::setPlaceholderFontColor(const Color4B& color)
{
    _colPlaceHolder = color;
    _labelPlaceHolder->setTextColor(color);
}

void EditBoxImplAndroid::setInputMode(EditBox::InputMode inputMode)
{
    _editBoxInputMode = inputMode;
}

void EditBoxImplAndroid::setMaxLength(int maxLength)
{
    _maxLength = maxLength;
}

int EditBoxImplAndroid::getMaxLength()
{
    return _maxLength;
}

void EditBoxImplAndroid::setInputFlag(EditBox::InputFlag inputFlag)
{
    _editBoxInputFlag = inputFlag;
}

void EditBoxImplAndroid::setReturnType(EditBox::KeyboardReturnType returnType)
{
    _keyboardReturnType = returnType;
}

bool EditBoxImplAndroid::isEditing()
{
    return false;
}

void EditBoxImplAndroid::setText(const char* pText)
{
    if (pText != NULL)
    {
        _text = pText;
		
        if (_text.length() > 0)
        {
            _labelPlaceHolder->setVisible(false);
			
            std::string strToShow;
			
            if (EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
            {
                long length = cc_utf8_strlen(_text.c_str(), -1);
                for (long i = 0; i < length; i++)
                {
                    strToShow.append("*");
                }
            }
            else
            {
                strToShow = _text;
            }

			_label->setString(strToShow.c_str());

			// Clip the text width to fit to the text box

            float fMaxWidth = _editSize.width - CC_EDIT_BOX_PADDING * 2;
            auto labelSize = _label->getContentSize();
            if(labelSize.width > fMaxWidth) {
                _label->setDimensions(fMaxWidth,labelSize.height);
            }
        }
        else
        {
            _labelPlaceHolder->setVisible(true);
            _label->setString("");
        }
		
    }
}

const char*  EditBoxImplAndroid::getText(void)
{
    return _text.c_str();
}

void EditBoxImplAndroid::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        _placeHolder = pText;
        if (_placeHolder.length() > 0 && _text.length() == 0)
        {
            _labelPlaceHolder->setVisible(true);
        }

        _labelPlaceHolder->setDimensions(_editSize.width-3, _editSize.height);
        _labelPlaceHolder->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
        _labelPlaceHolder->setLineBreakMode(cocos2d::CCLineBreakMode::CCLineBreakByTruncatingTail);
        _labelPlaceHolder->setString(_placeHolder.c_str());
    }
}

void EditBoxImplAndroid::setPosition(const Vec2& pos)
{ // don't need to be implemented on android platform.
	
}

void EditBoxImplAndroid::setVisible(bool visible)
{ // don't need to be implemented on android platform.

}

void EditBoxImplAndroid::setContentSize(const Size& size)
{ // don't need to be implemented on android platform.
	
}

void EditBoxImplAndroid::setAnchorPoint(const Vec2& anchorPoint)
{ // don't need to be implemented on android platform.
	
}

void EditBoxImplAndroid::visit(void)
{ // don't need to be implemented on android platform.
    
}

void EditBoxImplAndroid::onEnter(void)
{ // don't need to be implemented on android platform.
    
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    EditBoxImplAndroid* thiz = (EditBoxImplAndroid*)ctx;
    thiz->setText(pText);
	
    if (thiz->getDelegate() != NULL)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getEditBox());
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = thiz->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {        
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "ended", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
        memset(data.eventName, 0, sizeof(data.eventName));
        strncpy(data.eventName, "return", sizeof(data.eventName));
        event.data = (void*)&data;
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
}
    
    bool correctUtfBytesandroid(const char* bytes, int & index) {
        index = 0;
        while (*bytes != '\0') {
            unsigned char utf8 = *(bytes++);
            ++index;
            // Switch on the high four bits.
            switch (utf8 >> 4) {
                case 0x00:
                case 0x01:
                case 0x02:
                case 0x03:
                case 0x04:
                case 0x05:
                case 0x06:
                case 0x07:
                    // Bit pattern 0xxx. No need for any extra bytes.
                    break;
                case 0x08:
                case 0x09:
                case 0x0a:
                case 0x0b:
                case 0x0f:
                    /*
                     * Bit pattern 10xx or 1111, which are illegal start bytes.
                     * Note: 1111 is valid for normal UTF-8, but not the
                     * modified UTF-8 used here.
                     */
                    // *(bytes-1) = '?';
                    return false;
                    break;
                case 0x0e:
                    // Bit pattern 1110, so there are two additional bytes.
                    utf8 = *(bytes++);
                    if ((utf8 & 0xc0) != 0x80) {
                        // *(bytes-1) = 0;
                        //--bytes;
                        //*(bytes-2) = 0;
                        return false;
                        break;
                    }
                    
                    // Fall through to take care of the final byte.
                case 0x0c:
                case 0x0d:
                    // Bit pattern 110x, so there is one additional byte.
                    utf8 = *(bytes++);
                    if ((utf8 & 0xc0) != 0x80) {
                        
                        //--bytes;
                        //if(three)--bytes;
                        // *(bytes-2) = 0;
                        // *(bytes-1)=0;
                        return false;
                    }
                    break;
            }
        }
        return true;
    }
    

void EditBoxImplAndroid::openKeyboard()
{
    if (_delegate != NULL)
    {
        _delegate->editBoxEditingDidBegin(_editBox);
    }
    
#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = this->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {        
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        ScriptEvent event(cocos2d::kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
	
    int errIndex = 0;
    if(  !correctUtfBytesandroid( _placeHolder.c_str(), errIndex  ) )
    {
        CCLOG(" openKeyboard error:%s,%d",_placeHolder.c_str(), errIndex);
        return ;
    }
    if(  !correctUtfBytesandroid( _text.c_str(), errIndex  ) )
    {
        CCLOG(" openKeyboard 2error:%s,%d",_text.c_str(), errIndex);
        return ;
    }
    
    showEditTextDialogJNI(  _placeHolder.c_str(),
						  _text.c_str(),
						  (int)_editBoxInputMode,
						  (int)_editBoxInputFlag,
						  (int)_keyboardReturnType,
						  _maxLength,
						  editBoxCallbackFunc,
						  (void*)this  );
	
}

void EditBoxImplAndroid::closeKeyboard()
{
	closeEditText((void*)this);
}

}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) */

