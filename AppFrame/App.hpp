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

using namespace Tool;

namespace Engine {
    class App
    {
    public:
        App();
        virtual ~App();
        
        //Do main context init staffs
        virtual ReturnCode Init();
        //Deinit staffs
        virtual ReturnCode Deinit();
        //User update
        virtual ReturnCode Update();
        
        //main loop entry
        ReturnCode Run();
        
    };
}

#endif /* App_hpp */
