//
//  SandSimulator.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef SandSimulator_hpp
#define SandSimulator_hpp

#include "PreDeclear.h"
#include "Particle.hpp"

class SandSimulator
{
public:
	SandSimulator();
    virtual ~SandSimulator();
    
    //Do main context init staffs
    Tool::ReturnCode Init();
    //Deinit staffs
    Tool::ReturnCode Deinit();
    //User update
    Tool::ReturnCode Update();
    
    static const uint				NUMBER_OF_PARTICLES = 5;
    static const Engine::float3		GRAVITY_CONSTANT;
    static const Engine::float3		FRICTION_CONSTANT;
    
private:
    std::array<Physics::Particle, SandSimulator::NUMBER_OF_PARTICLES> ParticlePool;
    
};

#endif /* SandSimulator_hpp */