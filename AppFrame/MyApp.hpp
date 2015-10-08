//
//  MyApp.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef MyApp_hpp
#define MyApp_hpp

#include "App.hpp"
#include "Particle.hpp"

class MyApp: public Engine::App
{
public:
    MyApp():App();
    virtual ~MyApp();
    
    //Do main context init staffs
    virtual Tool::ReturnCode Init();
    //Deinit staffs
    virtual Tool::ReturnCode Deinit();
    //User update
    virtual Tool::ReturnCode Update();
    
private:
	static const int NUMBER_OF_PARTICLES = 5000;
    std::array<Physics::Particle, NUMBER_OF_PARTICLES> ParticlePool;
    
};

#endif /* MyApp_hpp */
