//
//  ConeRestriction.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "ConeRestriction.hpp"
#include "ReturnCode.hpp"

using namespace Engine;
using namespace Physics;

ConeRestriction::ConeRestriction()
{
};
ConeRestriction::~ConeRestriction()
{

};

bool ConeRestriction::Check(Particle& ParticleIn)
{
	float3 Position = ParticleIn.GetLocation();
	float y = this->h - ((Position.x() * this->h) / (this->r * Math::Cos(this->Theta)));
	if (y >= Position.y())
	{
		return true;
	}
	return false;
};
Tool::ReturnCode ConeRestriction::Apply(Particle& ParticleIn)
{
	ParticleIn.SetVelocity(ParticleIn.GetVelocity() * -0.001);
	return Tool::Success();
};
