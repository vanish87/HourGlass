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
#include <unordered_map>
#include <list>
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
	Tool::ReturnCode UpdateSpatialHash();
	Tool::ReturnCode CheckDection(Physics::Particle& PaticleIn, std::list<Physics::Particle*>& Cadidates);
	Tool::ReturnCode HandleCollisionWith(Physics::Particle & Target1, Physics::Particle & Target2);

	float GetKd(float MassEff = 0, float TimeContact = 1);
	float GetKr(float MassEff = 0, float TimeContact = 1);
	float GetKd(float3 T1, float3 T2);
	float GetKr(float3 T1, float3 T2);

    std::array<Physics::Particle, SandSimulator::NUMBER_OF_PARTICLES> ParticlePool;

	static const uint				VOXEL_CELL_SIZE;
	std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::list<Physics::Particle*>>>> SpatialHash;
    
};

#endif /* SandSimulator_hpp */
