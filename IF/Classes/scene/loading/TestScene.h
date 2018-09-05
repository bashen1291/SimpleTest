//
// Created by imac_liudi on 2018/8/1.
//

#ifndef WARZ_TESTSCENE_H
#define WARZ_TESTSCENE_H

#include "CommonInclude.h"

class TestScene :public Scene{
public:
    static TestScene* create();
    TestScene();
    virtual ~TestScene();

    bool init();

    void onEnter() override ;
    void onExit() override;


};


#endif //WARZ_TESTSCENE_H
