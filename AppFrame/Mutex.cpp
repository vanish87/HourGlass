//
//  Mutex.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "Mutex.hpp"
#include <stdio.h>

namespace Tool
{
    Mutex::Mutex()
    {
        pthread_mutex_init(&this->LockHandle, nullptr);
    };
    Mutex::~Mutex()
    {
        pthread_mutex_destroy(&this->LockHandle);
    };
    
    void Mutex::Lock()
    {
        if(pthread_mutex_lock(&this->LockHandle) != 0 )
        {
            printf("Lock Error\n");
        }
    };
    void Mutex::Unlock()
    {
        if(pthread_mutex_unlock(&this->LockHandle) != 0 )
        {
            printf("Unlock Error\n");
        }
    };
}
