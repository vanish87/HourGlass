//
//  ConeRestriction.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef ConeRestriction_hpp
#define ConeRestriction_hpp

#include "PreDeclear.h"
#include "Restriction.hpp"

class ConeRestriction : public Physics::Restriction
{
public:
	ConeRestriction();
    virtual ~ConeRestriction();

	virtual Tool::ReturnCode Apply(Physics::Particle& ParticleIn);

private:

	/*
	Cone parameter function
	x = (k / h)*r*cos(Theta) + x0;
	y = k					 + y0;
	z = (k / h)*r*sin(Theta) + z0;
	where
		k = [0, h];
		Theta = [0, 2PI];
	*/
	const float h = 50;
	const float r = 30;
	const float Mass = 5000;
	const Engine::float3 Position0 = Engine::float3(0, 0, 100);
};

#endif /* ConeRestriction_hpp */
