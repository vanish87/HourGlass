//
//  MainLoopThread.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/28.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef MainLoopThread_hpp
#define MainLoopThread_hpp

#include "Thread.hpp"

class MainLoopThread:public Tool::Thread
{
public:
    struct Parameter
    {
        Engine::App* AppInstance;
    };
    Tool::ReturnCode Main(void* para);
};
#endif /* MainLoopThread_hpp */
