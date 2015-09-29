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

namespace Physics
{
    
    Particle::Particle(MeshType Type)
    :SceneObject::SceneObject()
    {
        this->RenderElement = new Mesh(Graphics_CreateMesh(Type));
    };
    Particle::~Particle()
    {
        
    };
    
    void Particle::Update()
    {
        this->Velocity = this->Velocity + this->Acceleration * MS_PER_UPDATE;
        this->Location = this->Location + this->Velocity;
        
        
        this->RenderElement->SetLocation( this->Location);
        
        this->Acceleration = float3(0,0,0);
    };
    void Particle::Render()
    {
        
    };
    
    
    void Particle::ApplyForce(const float3& Force_)
    {
        float3 NewAcc = Force_ / this->Mass;
        this->Acceleration = this->Acceleration + NewAcc;
    }
}