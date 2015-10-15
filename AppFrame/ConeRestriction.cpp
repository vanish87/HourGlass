//
//  ConeRestriction.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "ConeRestriction.hpp"
#include "ReturnCode.hpp"
#include "SandSimulator.hpp"

using namespace Engine;
using namespace Physics;

ConeRestriction::ConeRestriction()
{
};
ConeRestriction::~ConeRestriction()
{

};

//http://mathworld.wolfram.com/Cone.html
Tool::ReturnCode ConeRestriction::Apply(Particle& ParticleIn)
{
	float3 Position = ParticleIn.GetLocation();
	Position = Position - Position0;
	float k = Math::Sqrt(Position.x()*Position.x() + Position.z()*Position.z());
	float3 vel = ParticleIn.GetVelocity();
	if (k >= Position.y()) 
	{
		float3 x1 = ParticleIn.GetLocation();
		float3 x2 = float3(x1.x(), k, x1.z());
		float  m1 = ParticleIn.GetMass();
		float  m2 = this->Mass;
		float3 v1 = ParticleIn.GetVelocity();
		float3 v2 = float3(0,0,0);
		float3 Fn = SandSimulator::GetContactForce(x1,x2,m1,m2,v1,v2,10,10);
		//points to T2
		//ParticleIn.ApplyForce(Fn*-1);
        
        
        vel.y() = vel.y() * -1;
	}
    
    if(Position.y() < -5)
    {
        //vel.y() = vel.y() * -1;
    }
        
	if (Position.x() > 20 || Position.x() < -20)
	{
		vel.x() = vel.x()* -0.1;
	}
	ParticleIn.SetVelocity(vel);
	return Tool::Success();
};
