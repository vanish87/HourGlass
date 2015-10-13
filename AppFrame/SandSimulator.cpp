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
extern float MS_PER_UPDATE;

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
	this->UpdateSpatialHash();

	for (std::array<Physics::Particle, SandSimulator::NUMBER_OF_PARTICLES>::iterator it = this->ParticlePool.begin();
	it != this->ParticlePool.end();
		++it)
	{
		/*
		float3 Friction = it->GetVelocity();
		Friction = Friction * -1;
		Math::Normalize(Friction);
		Friction = Friction * SandSimulator::FRICTION_CONSTANT;*/
	}

	return Tool::Success();
}
Tool::ReturnCode SandSimulator::UpdateSpatialHash()
{
	for (std::array<Physics::Particle, SandSimulator::NUMBER_OF_PARTICLES>::iterator it = this->ParticlePool.begin();
		it != this->ParticlePool.end();
		++it)
	{
		//apply gravity first
		it->ApplyForce(SandSimulator::GRAVITY_CONSTANT*it->GetMass());

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
					this->CheckDection(*it, Zit->second);
				}
				else
				{
					this->SpatialHash[HashId.x()][HashId.y()][HashId.z()].push_back(&*it);
				}
			}
			else
			{
				this->SpatialHash[HashId.x()][HashId.y()][HashId.z()].push_back(&*it);
			}
		}
		else
		{
			this->SpatialHash[HashId.x()][HashId.y()][HashId.z()].push_back(&*it);
		}

		it->Update();
	}
	return Tool::Success();
};

Tool::ReturnCode SandSimulator::CheckDection(Physics::Particle& PaticleIn, std::list<Physics::Particle*>& Cadidates)
{
	for (std::list<Physics::Particle*>::iterator it = Cadidates.begin(); it != Cadidates.end(); ++it)
	{
		this->HandleCollisionWith(PaticleIn, **it);
	}
	return Tool::Success();
}
Tool::ReturnCode SandSimulator::HandleCollisionWith(Physics::Particle & Target1, Physics::Particle & Target2)
{
	//if contacted, apply contact force
	float3 x1 = Target1.GetLocation();
	float3 x2 = Target2.GetLocation();

	float m1 = Target1.GetMass();
	float m2 = Target2.GetMass();

	float3 v1 = Target1.GetVelocity();
	float3 v2 = Target2.GetVelocity();

	float Distance = Math::Dot(x1, x2);
	//const radius 1
	if (Distance <= 1)
	{
		float3 CenterVector = x2 - x1;
		float3 Normal = Math::Normalize(CenterVector);
		float Overlap = Math::Max((float)0.0, 2 - Math::Sqrt(Distance));
		float Meff = (m1 * m2) / (m1 + m2);
		//dissipation
		float Kd = this->GetKd(Meff, MS_PER_UPDATE);
		//stiffness
		float Kr = this->GetKr(Meff, MS_PER_UPDATE);

		float Alpha = 0.5;
		float Beta = 1.5;

		float Ov = Math::Dot(v1 - v2, Normal);

		float fn = -Kd * Math::Pow(Overlap, Alpha) * Ov - Kr * Math::Pow(Overlap, Beta);
		//point to T2
		float3 Fn = Normal * fn;

		Target2.ApplyForce(Fn);
		Target1.ApplyForce(Fn * -1);
	}
	//apply friction

	float3 Friction = Target1.GetVelocity();
	Friction = Friction * -1;
	Math::Normalize(Friction);
	Friction = Friction * SandSimulator::FRICTION_CONSTANT; 
	Target1.ApplyForce(Friction);

	Friction = Target2.GetVelocity();
	Friction = Friction * -1;
	Math::Normalize(Friction);
	Friction = Friction * SandSimulator::FRICTION_CONSTANT;
	Target2.ApplyForce(Friction);

	return Tool::Success();
}

float SandSimulator::GetKd(float MassEff, float TimeContact)
{
	if (MassEff > 0 && TimeContact > 0)
	{
		float NORMAL_RESTITUTION = 1;
		return 2 * MassEff * -Math::Ln(NORMAL_RESTITUTION) / TimeContact;
	}
	return 0.0f;
}

float SandSimulator::GetKr(float MassEff, float TimeContact)
{
	if (MassEff > 0 && TimeContact > 0)
	{
		float NORMAL_RESTITUTION = 1;
		float lnE = Math::Ln(NORMAL_RESTITUTION);
		return (MassEff/( TimeContact * TimeContact)) *(lnE * lnE + Math::PI * Math::PI);
	}
	return 0.0f;
}

//Hertz theory Kd, Kr
float SandSimulator::GetKd(float3 T1, float3 T2)
{

	return 0.0f;
}

float SandSimulator::GetKr(float3 T1, float3 T2)
{
	//x is Radius
	float Reff = (T1.x() * T2.x()) / (T1.x() + T2.x());
	//y is Young's moduli
	//z is Poisson ratios
	float Eeff = ((1 - T1.y()*T1.y()) / T1.z()) + ((1 - T2.y()*T2.y()) / T2.z());
	Eeff = 1 / Eeff;
	return 4.0 / 3.0 * Eeff * Math::Sqrt(Reff);
}

