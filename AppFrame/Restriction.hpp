//
//  Restriction.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef Restriction_hpp
#define Restriction_hpp

#include "PreDeclear.h"
#include "Particle.hpp"

namespace Physics
{
	class Restriction
	{
	public:
		Restriction();
		virtual ~Restriction();
		virtual Tool::ReturnCode Apply(Physics::Particle& ParticleIn);
	};

}

#endif /* Restriction_hpp */
