//
//  MainLoop_Bridge.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/28.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "MainLoop_Bridge.h"
#include "MainLoopThread.hpp"

static MainLoopThread GameLoop;

void MainLoopBridge_StartGameLoop(void)
{
    GameLoop.Create();
}