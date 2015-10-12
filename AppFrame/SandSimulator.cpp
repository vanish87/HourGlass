//
//  SandSimulator.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "SandSimulator.hpp"
#include "Vector.h"
#include "ReturnCode.hpp"

using namespace Engine;


const float3 SandSimulator::GRAVITY_CONSTANT = float3(0, 0.98, 0);
const float3 SandSimulator::FRICTION_CONSTANT = float3(0, 0.01, 0);

SandSimulator::SandSimulator()
{

};
SandSimulator::~SandSimulator()
{

};
//Do main context init staffs
Tool::ReturnCode SandSimulator::Init()
{
    for (std::array<Physics::Particle, SandSimulator::NUMBER_OF_PARTICLES>::iterator it = this->ParticlePool.begin();
			it != this->ParticlePool.end();
			++it)
	{
		it->Create(CUBE);
		it->AddToScene();
		it->SetLocation(float3(0, 1, 0));
        it->SetScale(float3(0.1,0.1,0.1));
	}

	return Tool::Success();
};
//Deinit staffs
Tool::ReturnCode SandSimulator::Deinit()
{
	return Tool::Success();
};
//User update
Tool::ReturnCode SandSimulator::Update()
{
	for (std::array<Physics::Particle, SandSimulator::NUMBER_OF_PARTICLES>::iterator it = this->ParticlePool.begin();
	it != this->ParticlePool.end();
		++it)
	{
		//apply gravity first
		it->ApplyForce(SandSimulator::GRAVITY_CONSTANT*it->GetMass());

		float3 Friction = it->GetVelocity();
		Friction = Friction * -1;
		Math::Normalize(Friction);
		Friction = Friction * SandSimulator::FRICTION_CONSTANT;
	}
	return Tool::Success();
};