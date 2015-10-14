//
//  SandParticle.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef SandParticle_hpp
#define SandParticle_hpp

#include "PreDeclear.h"
#include "Particle.hpp"
#include "ConeRestriction.hpp"

class SandParticle : public Physics::Particle
{
	friend class SandSimulator;
public:
	SandParticle();
    virtual ~SandParticle();
    
    void Update();
    
    
    
private:
	void ApplyRestrictions();

	Engine::float4x4 SandMatrix;

    
    //sand is not a sphere but a combination of four smaller sphere that on the four
    //points of tetrahedron.
    //This intends to provide enough frictions for sand
    static const uint NumberOfSphere = 4;
    struct Tetrahedron
    {
        Engine::float3 Position[SandParticle::NumberOfSphere];
    };

    SandParticle::Tetrahedron TerahedronInstance;

	ConeRestriction RestrictionInstance;
    
};

#endif /* SandParticle_hpp */
