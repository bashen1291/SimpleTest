//
// Created by imac_liudi on 2018/8/13.
//

#ifndef WARZSIMPLETEST_RAIN_H
#define WARZSIMPLETEST_RAIN_H

#include "CommonInclude.h"

class Rain : public CCSprite {

public:
    static Rain* create();
    Rain();
    ~Rain(){};
    bool init();


    BlendFunc _blendFunc;
    GLProgramState *_glprogramstate = nullptr;
    GLProgram *_glprogram = nullptr;
    Texture2D* m_RainTex;

    float rainOffsetY;
    float rainTime;
    float rainSpeed = 0;
    float rainSpeedTo = 0;
    float rainSpeedTime = 0;


    bool _playRain;

    void update(float t);

    void startRainIn(float t, float Speed);

    void startRainOut(float t);

    void stopRain();


};


#endif //WARZSIMPLETEST_RAIN_H
