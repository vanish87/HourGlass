//
//  MainLoopThread.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/28.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "MainLoopThread.hpp"
#include <ctime>
#include "Context.hpp"
#include "SceneManager.h"
#include "Particle.hpp"
#include "App.hpp"

using namespace Tool;

float MS_PER_UPDATE = 1/60.0;

Tool::ReturnCode MainLoopThread::Main(void* para)
{
    MainLoopThread::Parameter* RealPara = (MainLoopThread::Parameter*)para;
    std::clock_t start;
    double duration;
    
    start = std::clock();    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;         
    std::clock_t previous = std::clock();
    double lag = 0.0;

    while (true)
    {
        std::clock_t current = std::clock();
        double elapsed = (current - previous)/ (double)CLOCKS_PER_SEC;
        previous = current;
        lag += elapsed;
        while (lag >= MS_PER_UPDATE)
        {
            //Context::Instance().GetSceneManager().Update();
            RealPara->AppInstance->Update();
            lag -= MS_PER_UPDATE;
        }
        Context::Instance().GetSceneManager().Flush();
    }
    return Success();
};