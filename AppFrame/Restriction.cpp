//
//  Restriction.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "Restriction.hpp"
#include "ReturnCode.hpp"

using namespace Engine;
using namespace Physics;

namespace Physics
{
	Restriction::Restriction()
	{
	};
	Restriction::~Restriction()
	{

	};

	bool Restriction::Check(Particle& ParticleIn)
	{
		return false;
	};
	Tool::ReturnCode Restriction::Apply(Particle& ParticleIn)
	{
		return Tool::Success();
	};
}
