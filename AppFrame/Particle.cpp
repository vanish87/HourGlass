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
        :SceneObject::SceneObject(),
		Location(float3(0,0,0)), Velocity(float3(0,0,0)),Acceleration(float3(0,0,0)),Mass(1)
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
    
    void Particle::Update()
    {
        this->Velocity = this->Velocity + this->Acceleration * MS_PER_UPDATE;
        this->Location = this->Location + this->Velocity;
        
        
        this->RenderElement->SetLocation( this->Location);

		this->Acceleration = float3(0, 0, 0);
    };
    void Particle::Render()
    {
        
    };
    
    
    void Particle::ApplyForce(const float3& Force_)
    {
        float3 NewAcc = Force_ / this->Mass;
        this->Acceleration = this->Acceleration + NewAcc;
    }


	void Particle::SetLocation(const float3& NewLocation)
	{
		this->RenderElement->SetLocation(NewLocation);
	}
	void Particle::SetScale(const float3& NewScale)
	{
		this->RenderElement->SetScale(NewScale);
	}
	const float Particle::GetMass() const
	{
		return this->Mass;
	}
	void Particle::SetMass(const float & NewMass)
	{
		this->Mass = NewMass;
	}
	const float3 Particle::GetVelocity() const
	{
		return this->Velocity;
	}
}