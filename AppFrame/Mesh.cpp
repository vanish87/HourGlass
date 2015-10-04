//
//  Mesh.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "Mesh.hpp"

namespace Engine
{
    Mesh::Mesh(MeshType Type, float3 Location_)
    :Location(Location_)
    {
        this->Data = Graphics_CreateMesh(Type);
    };
    
    Mesh::~Mesh()
    {
        //free data in objectivec
        this->Data = nullptr;
    };
    
    
    void Mesh::SetLocation(const float3& NewLocation)
    {
        this->Location = NewLocation;
    };
    
    
    float3 Mesh::GetLocation()
    {
        return this->Location;
    };
    void* Mesh::GetRawData()
    {
        return this->Data;
    };
    
    
}