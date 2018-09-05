//
// Created by imac_liudi on 2018/8/13.
//

#include "Rain.h"

Rain::Rain() {

}

#define STRINGIFY(A)  #A
extern const char* Rain_frag;
#include "RainShader.frag"
extern const char* Rain_vert;
#include "RainShader.vert"

Rain *Rain::create() {

    auto ret = new Rain();
    if(ret && ret->init())
        ret->autorelease();
    else
        CC_SAFE_DELETE(ret);
    return ret;
}

bool Rain::init() {
    if(!CCSprite::init())
        return false;

    _glprogram = GLProgram::createWithByteArrays(Rain_vert, Rain_frag);
//
    _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;

    m_RainTex = CCDirector::sharedDirector()->getTextureCache()->addImage("test/yu.png");
    cocos2d::Texture2D::TexParams texParam;
    texParam.wrapS = GL_REPEAT;
    texParam.wrapT = GL_REPEAT;
    texParam.minFilter = GL_LINEAR;
    texParam.magFilter = GL_LINEAR;
    m_RainTex->setTexParameters(texParam);
    initWithTexture(m_RainTex);

    setGLProgram(_glprogram);
    getGLProgramState()->setUniformFloat("_RainIntensity", 1.0f);
    getGLProgramState()->setUniformFloat("_FallSpeed", 0.0f);
    getGLProgramState()->setUniformVec4("_ThunderLighting", Vec4(255.0f/255, 246.0f / 255, 238.0f / 255, 255.0f / 255));
//    getGLProgramState()->setUniformVec4("_ThunderLighting", Vec4(54.0f/255, 37.0f / 255, 37.0f / 255, 128.0f / 255));
    setBlendFunc(_blendFunc);
    setOpacity(0);

    return true;


}

void Rain::update(float t)
{
    if(_playRain)
    {
        //下雨中
        rainTime += t;
        if(rainSpeed < rainSpeedTo)
        {
            rainSpeed = rainTime > rainSpeedTime? rainSpeedTo: (rainTime/rainSpeedTime) * rainSpeedTo;
        }
    }
    else
    {
        //雨停中
        if(rainSpeed <= 0)
        {
            stopRain();
        }

        rainTime+= t;
        rainSpeed = rainTime > rainSpeedTime? 0:((rainSpeedTime - rainTime)/rainSpeedTime) * rainSpeedTo;

    }
    rainOffsetY += rainSpeed * t;
    if(rainOffsetY > 2)
        rainOffsetY -= 2;
    getGLProgramState()->setUniformFloat("_FallSpeed", rainOffsetY);


}

void Rain::startRainIn(float t, float Speed)
{
    rainSpeed = 1;
    rainTime = 0;
    rainSpeedTo = Speed;
    rainSpeedTime = t;
    rainOffsetY = 0;
    _playRain = true;
    runAction(FadeIn::create(0.5));
    scheduleUpdate();
}

void Rain::startRainOut(float t) {
    _playRain = false;
    rainSpeedTime = t;
    rainSpeedTo = rainSpeed;
    rainTime = 0;
    runAction(FadeOut::create(t));
}

void Rain::stopRain()
{
    unscheduleUpdate();
    setOpacity(0);
}



