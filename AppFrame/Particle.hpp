//
//  Particle.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "PreDeclear.h"
#include "Vector.h"
#include "SceneObject.h"
#include "Graphics_Bridge.hpp"

using namespace Engine;


extern float MS_PER_UPDATE;

namespace Physics {
    
    class Particle : public Engine::SceneObject
    {
    public:
        Particle();
        Tool::ReturnCode Create(MeshType Type = SPHERE);
        virtual ~Particle();
        
        virtual void Update();
        virtual void Render();
		virtual void Reset();
        
        void ApplyForce(const float3& Force_);

		void SetLocation(const float3& NewLocation);
		const float3 GetLocation() const;
		void SetScale(const float3& NewScale);

		const float GetMass() const;
		void  SetMass(const float& NewMass);


		const float3 GetVelocity() const;
		void SetVelocity(const float3& NewVelocity);
        
    protected:
		float3 Location;//physics location that differs from render element's
        float3 Velocity;
        float3 Acceleration;
        
        float Mass;
		float Radius;
        
        
    };
}
#endif /* Particle_hpp */
