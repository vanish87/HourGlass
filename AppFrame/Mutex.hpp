//
//  Mutex.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef Mutex_hpp
#define Mutex_hpp

#include <pthread.h>

namespace Tool {
    class Mutex
    {
    public:
        Mutex();
        virtual ~Mutex();
        
        void Lock();
        void Unlock();
        
    private:
        pthread_mutex_t LockHandle;
    };
}

#endif /* Mutex_hpp */
