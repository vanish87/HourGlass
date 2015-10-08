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
    {
		Math::Identity(this->MeshMatrix);
        this->Data = Graphics_CreateMesh(Type);
    };
    
    Mesh::~Mesh()
    {
        //free data in objectivec
        this->Data = nullptr;
    };
    
    
    void Mesh::SetLocation(const float3& NewLocation)
    {
		this->MeshMatrix.Row(3) = float4(NewLocation.x(), NewLocation.y(), NewLocation.z(), 1);
    };

	void Mesh::SetScale(const float3& NewScale)
	{
		this->MeshMatrix[0][0] = NewScale.x();
		this->MeshMatrix[1][1] = NewScale.y();
		this->MeshMatrix[2][2] = NewScale.z();
	};

	float3 Mesh::GetScale() const
	{
		return float3(this->MeshMatrix[0][0], this->MeshMatrix[1][1],this->MeshMatrix[2][2]);
	}
    
    float3 Mesh::GetLocation() const
    {
        return float3(this->MeshMatrix.Row(3).x(), this->MeshMatrix.Row(3).y(), this->MeshMatrix.Row(3).z());
    };
    void* Mesh::GetRawData()
    {
        return this->Data;
    };
    
    
}