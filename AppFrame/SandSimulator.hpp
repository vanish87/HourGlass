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
#include "SandParticle.hpp"

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

	Tool::ReturnCode Reset();
	Tool::ReturnCode SetConntactParameter(float Mass, float Alpha, float Beta, float NormalRestitution);
    
    static const uint				NUMBER_OF_PARTICLES = 100;
    static const Engine::float3		GRAVITY_CONSTANT;
    static const Engine::float3		FRICTION_CONSTANT;

	static Engine::float3 GetContactForce(const Engine::float3 x1, const Engine::float3 x2,
										  const float m1, const float m2,
										  const Engine::float3 v1, const Engine::float3 v2,
										  const float r1, const float r2);
    
private:
	Tool::ReturnCode UpdateSpatialHash();
	Tool::ReturnCode CheckDection(SandParticle& PaticleIn, std::list<SandParticle*>& Cadidates);
	Tool::ReturnCode HandleCollisionWith(SandParticle & Target1, SandParticle & Target2);

	static float GetKd(float MassEff = 0, float TimeContact = 1);
	static float GetKr(float MassEff = 0, float TimeContact = 1);
	static float GetKd(Engine::float3 T1, Engine::float3 T2);
	static float GetKr(Engine::float3 T1, Engine::float3 T2);

	static float Alpha;
	static float Beta;
	static float NormalRestitution;

    std::array<SandParticle, SandSimulator::NUMBER_OF_PARTICLES> ParticlePool;

	static const uint				VOXEL_CELL_SIZE;
	std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::list<SandParticle*>>>> SpatialHash;
    
};

#endif /* SandSimulator_hpp */
