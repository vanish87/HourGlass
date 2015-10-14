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

	virtual bool Check(Physics::Particle& ParticleIn);
	virtual Tool::ReturnCode Apply(Physics::Particle& ParticleIn);

private:
	const float h = 10;
	const float Theta = Math::PI / 6;
	const float r = 3;
};

#endif /* ConeRestriction_hpp */
