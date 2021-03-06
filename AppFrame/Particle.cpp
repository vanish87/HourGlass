//
//  Particle.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "Particle.hpp"
#include "Graphics_Bridge.hpp"
#include "Mesh.hpp"
#include "ReturnCode.hpp"

using namespace Tool;

namespace Physics
{
    
    Particle::Particle()
        :SceneObject::SceneObject()	
    {
    };
    ReturnCode Particle::Create(MeshType Type)
    {
        this->RenderElement = new Mesh(Type);
        return Success();
    };
    Particle::~Particle()
    {
        delete this->RenderElement;
        this->RenderElement = nullptr;
    };
    
    void Particle::Update(const float Delta = MS_PER_UPDATE)
    {
		if (Delta > 0)
		{
			this->LastFrameInfo = this->CurrentFrameInfo;
			this->CurrentFrameInfo.Location = this->CurrentFrameInfo.Location + //S0
											((this->CurrentFrameInfo.Velocity * Delta) +//V0*t 
											( this->CurrentFrameInfo.Acceleration * 0.5 * Delta * Delta)); //0.5*a*t*t
			this->CurrentFrameInfo.Velocity = this->CurrentFrameInfo.Velocity + this->CurrentFrameInfo.Acceleration * Delta;

			this->RenderElement->SetLocation(this->CurrentFrameInfo.Location);

			this->CurrentFrameInfo.Acceleration = float3(0, 0, 0);
		}
    };
    void Particle::Render()
    {
        
	};

	void Particle::Reset()
	{
		this->CurrentFrameInfo.Location = float3(0, 0, 0);
		this->CurrentFrameInfo.Velocity = float3(0, 0, 0);
		this->CurrentFrameInfo.Acceleration =float3(0, 0, 0);
		this->CurrentFrameInfo.Mass = 1;
		this->CurrentFrameInfo.Radius = 1;
	};
    
    
    void Particle::ApplyForce(const float3& Force_)
    {
        float3 NewAcc = Force_ / this->CurrentFrameInfo.Mass;
        this->CurrentFrameInfo.Acceleration = this->CurrentFrameInfo.Acceleration + NewAcc;
    }


	void Particle::SetLocation(const float3& NewLocation)
	{
		this->CurrentFrameInfo.Location = NewLocation;
	}
	const float3 Particle::GetLocation() const
	{
		return this->CurrentFrameInfo.Location;
	}
	
	void Particle::SetScale(const float3& NewScale)
	{
		this->RenderElement->SetScale(NewScale);
	}
	const float Particle::GetMass() const
	{
		return this->CurrentFrameInfo.Mass;
	}
	void Particle::SetMass(const float & NewMass)
	{
		if (this->CurrentFrameInfo.Mass > 0)
		{
			this->CurrentFrameInfo.Mass = NewMass;
		}
		else
		{
			//do nothing
		}
	}
	const float3 Particle::GetVelocity() const
	{
		return this->CurrentFrameInfo.Velocity;
	}
	void Particle::SetVelocity(const float3& NewVelocity)
	{
		this->CurrentFrameInfo.Velocity = NewVelocity;
	};

	void Particle::ApplyCollisionCorrection(const float NormalizedDeltaTimeFromLastFrame)
	{
		this->CurrentFrameInfo.Velocity = this->LastFrameInfo.Velocity + this->LastFrameInfo.Acceleration * NormalizedDeltaTimeFromLastFrame * MS_PER_UPDATE;
		this->CurrentFrameInfo.Location = this->LastFrameInfo.Location + this->LastFrameInfo.Velocity;

		this->RenderElement->SetLocation(this->CurrentFrameInfo.Location);

		this->CurrentFrameInfo.Acceleration = float3(0, 0, 0);
		this->LastFrameInfo = this->CurrentFrameInfo;
		this->Update((1 - NormalizedDeltaTimeFromLastFrame) * MS_PER_UPDATE);
	}


}