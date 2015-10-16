//
//  MainLoop_Bridge.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/28.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "MainLoop_Bridge.h"
#include "MyApp.hpp"

static MyApp GlobalGame;

void MainLoopBridge_StartGameLoop(void)
{
    GlobalGame.Init();
    GlobalGame.Run();
}

void MainLoopBridge_ResetSimulator()
{
    GlobalGame.ResetSimulator();
}