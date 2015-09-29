//
//  Thread.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/28.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef Thread_hpp
#define Thread_hpp

#include <string>
#include "PreDeclear.h"
#include "ReturnCode.hpp"
#include <pthread.h>


namespace Tool
{
    class Thread
    {
    public:
        Thread();
        virtual ~Thread();
        
        virtual ReturnCode Main(void* para) = 0;
        
        ReturnCode Create(void* Parameter_ = nullptr,std::string Name = __FILE__);
        
        ReturnCode Join();
        
    private:
        std::string Name;
        void* Parameter;        
        
        pthread_t ThreadNum;
        pthread_attr_t ThreadAttr;

        
        static void* ThreadMain(void* ThreadData);
    };
}

#endif /* Thread_hpp */
