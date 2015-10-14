//
//  App.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/20.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include <stdio.h>
#include "ReturnCode.hpp"
#include "MainLoopThread.hpp"

using namespace Tool;

namespace Engine {
    class App
    {
    public:
        App(){};
        virtual ~App(){};
        
        //Do main context init staffs
        virtual ReturnCode Init(){return Success();};
        //Deinit staffs
        virtual ReturnCode Deinit(){return Success();};
        //User update
        virtual ReturnCode Update(){return Success();};
        
        //main loop entry
        ReturnCode Run()
        {
            MainParameter.AppInstance = this;
            return MainLoop.Create(&MainParameter);
        };
        
        
    private:
        MainLoopThread::Parameter MainParameter;
        MainLoopThread MainLoop;
        
    };
}

#endif /* App_hpp */
