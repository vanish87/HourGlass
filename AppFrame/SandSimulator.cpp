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
const uint	 SandSimulator::VOXEL_CELL_SIZE = 10;

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
		it->SetLocation(float3(0, 1, 5));
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
}
Tool::ReturnCode SandSimulator::UpdateSpatialHash()
{
	for (std::array<Physics::Particle, SandSimulator::NUMBER_OF_PARTICLES>::iterator it = this->ParticlePool.begin();
	it != this->ParticlePool.end();
		++it)
	{
		const float3 Position = it->GetLocation();
		const int3 HashId = Position / SandSimulator::VOXEL_CELL_SIZE;
		std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::list<Physics::Particle*>>>>::iterator Xit = this->SpatialHash.find(HashId.x());
		if (Xit != this->SpatialHash.end())
		{
			std::unordered_map<int, std::unordered_map<int, std::list<Physics::Particle*>>>::iterator Yit = Xit->second.find(HashId.y());
			if (Yit != Xit->second.end())
			{
				std::unordered_map<int, std::list<Physics::Particle*>>::iterator Zit = Yit->second.find(HashId.z());
				if (Zit != Yit->second.end())
				{
					return this->CheckDection(*it, Zit->second);
				}
				else
				{
					this->SpatialHash[HashId.x()][HashId.y()][HashId.z()].push_back(&*it);
					return Tool::Success();
				}
			}
			else
			{
				this->SpatialHash[HashId.x()][HashId.y()][HashId.z()].push_back(&*it);
				return Tool::Success();
			}
		}
		else
		{
			this->SpatialHash[HashId.x()][HashId.y()][HashId.z()].push_back(&*it);
			return Tool::Success();
		}
	}
	return Tool::Success();
};

Tool::ReturnCode SandSimulator::CheckDection(Physics::Particle& PaticleIn, std::list<Physics::Particle*>& Cadidates)
{
	for (std::list<Physics::Particle*>::iterator it = Cadidates.begin(); it != Cadidates.end(); ++it)
	{
		PaticleIn.HandleCollisionWith(**it);
	}
}

