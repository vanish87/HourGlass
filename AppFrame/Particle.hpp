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
        
        virtual void Update(const float DeltaTime = MS_PER_UPDATE);
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

		void ApplyCollisionCorrection(const float DeltaTimeFromLastFrame);
    protected:
		struct SpatialInfomation
		{
			float3 Location;//physics location that differs from render element's
			float3 Velocity;
			float3 Acceleration;
			SpatialInfomation()
				:Location(float3(0, 0, 0)), Velocity(float3(0, 0, 0)), Acceleration(float3(0, 0, 0)), Mass(1), Radius(1)
			{}

			float Mass;
			float Radius;
		};

		SpatialInfomation LastFrameInfo;
		SpatialInfomation CurrentFrameInfo;
        
        
        
    };
}
#endif /* Particle_hpp */
