//
//  Context.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "Context.hpp"
#include "SceneManager.h"


Context::Context(void)
{
    
};
Context::~Context(void)
{
    
};
    
Context& Context::Instance()
{
    static Context Instance;
    return Instance;
}

Engine::SceneManager& Context::GetSceneManager()
{
    if (this->scene_manager_ == nullptr)
    {
        this->scene_manager_ = new Engine::SceneManager();
    }
    return *this->scene_manager_;
};