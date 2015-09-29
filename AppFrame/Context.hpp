//
//  Context.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef Context_hpp
#define Context_hpp

#include "PreDeclear.h"

class Context
{
public:
    //TODO : make constructor to be protected: because of singleton pattern
    Context(void);
    ~Context(void);
    
    static Context& Instance();
    
    Engine::SceneManager& GetSceneManager();
    
private:
    Engine::SceneManager* scene_manager_;
};
#endif /* Context_hpp */
