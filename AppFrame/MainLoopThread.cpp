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

using namespace Tool;

float MS_PER_UPDATE = 1/60.0;

Tool::ReturnCode MainLoopThread::Main(void* para)
{
    
    Para* Data = static_cast<Para*>(para);
    //while (true)
    {
        printf("Running in 2 seconds\n");
        sleep(2);
    }
    std::clock_t start;
    double duration;
    
    start = std::clock();
    
    /* Your algorithm here */
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
    
    Physics::Particle NewP(CUBE);
    NewP.AddToScene();
    NewP.SetLocation(float3(0,1,5));
    
    Physics::Particle NewP1(SPHERE);
    //NewP1.AddToScene();
    NewP1.SetLocation(float3(2,-1,5));
    
    Physics::Particle NewPlane(PLANE);
    NewPlane.AddToScene();
    NewPlane.SetLocation(float3(0,-1,0));
    
    std::clock_t previous = std::clock();
    double lag = 0.0;
    while (true)
    {
        std::clock_t current = std::clock();
        double elapsed = (current - previous)/ (double)CLOCKS_PER_SEC;
        previous = current;
        lag += elapsed;
        //processInput();
        
        //printf("elapsed:%f",elapsed);
        
        //printf("lag:%f\n",lag);
        int Count = 0;
        while (lag >= MS_PER_UPDATE)
        {
            //update();
            usleep(2000);
            //Count++;
            //printf("s:%f",std::clock()/(double)CLOCKS_PER_SEC);
            Context::Instance().GetSceneManager().Update();
            lag -= MS_PER_UPDATE;
        }
        
        //if (Count > 0)
        //{
        //    printf("Count:%d\n",Count);
        //}
        usleep(16000);
        Context::Instance().GetSceneManager().Flush();
        //render();
    }
    
    //std::cout << "Hello, World!\n" << Data->in;
    Data->ret = 2;
    return Success();
};