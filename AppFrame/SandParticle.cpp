//
//  SandParticle.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "SandParticle.hpp"
#include "Vector.h"
#include "ReturnCode.hpp"
#include "Math.h"

using namespace Engine;
using namespace Physics;

SandParticle::SandParticle()
	:Particle()
{
	Math::Identity(this->SandMatrix);
	this->TerahedronInstance.Position[0] = float3( 1, 0, -1 / Math::Sqrt(2));
	this->TerahedronInstance.Position[1] = float3(-1, 0, -1 / Math::Sqrt(2));
	this->TerahedronInstance.Position[2] = float3( 0, 1,  1 / Math::Sqrt(2));
	this->TerahedronInstance.Position[3] = float3( 0,-1,  1 / Math::Sqrt(2));

	this->Radius = Math::Sqrt(Math::Dot(this->TerahedronInstance.Position[0] , this->TerahedronInstance.Position[0])) * 0.1;
};
SandParticle::~SandParticle()
{

};

void SandParticle::Update()
{
	Particle::Update();
	this->ApplyRestrictions();
}

void SandParticle::ApplyRestrictions()
{
	if (this->RestrictionInstance.Check(*this))
	{
		this->RestrictionInstance.Apply(*this);
	}
}
