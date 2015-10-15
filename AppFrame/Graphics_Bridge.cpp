//
//  Graphics_Bridge.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//


#include <vector>

#include "Graphics_Bridge.hpp"
#include "Context.hpp"
#include "SceneManager.h"
#include "PreDeclear.h"
#include "Mesh.hpp"

bool  Graphics_LockRenderQueue()
{
    Context::Instance().GetSceneManager().LockRenderQueue();
    return true;
}
bool  Graphics_UnlockRenderQueue()
{
    Context::Instance().GetSceneManager().UnlockRenderQueue();
    return true;
}
bool  Graphics_IsRenderQueueEmpty()
{
    return Context::Instance().GetSceneManager().GetRenderList().empty();
}

void* Graphics_GetRawData(void* MeshData)
{
    if (MeshData != nullptr)
    {
        Engine::Mesh* MeshPtr = static_cast<Engine::Mesh*>(MeshData);
        return MeshPtr->GetRawData();
    }
    return nullptr;
}

void Graphics_GetLocation(void* MeshData, float* x, float* y, float* z)
{
    if (MeshData != nullptr)
    {
        Engine::Mesh* MeshPtr = static_cast<Engine::Mesh*>(MeshData);
        Engine::float3 Loc = MeshPtr->GetLocation();
        
        *x = Loc.x();
        *y = Loc.y();
        *z = Loc.z();
    }
}

void Graphics_GetScale(void* MeshData, float* x, float* y, float* z)
{
	if (MeshData != nullptr)
	{
		Engine::Mesh* MeshPtr = static_cast<Engine::Mesh*>(MeshData);
		Engine::float3 Loc = MeshPtr->GetScale();

		*x = Loc.x();
		*y = Loc.y();
		*z = Loc.z();
	}
}

unsigned long Graphics_GetNumberOfMeshes()
{
    std::vector<Engine::Mesh*>& RenderData = Context::Instance().GetSceneManager().GetRenderList();
    return RenderData.size();
};

void* Graphics_PopAndGetMeshData()
{
    std::vector<Engine::Mesh*>& RenderData = Context::Instance().GetSceneManager().GetRenderList();
    if (!RenderData.empty())
    {
        void* DataToReturn = RenderData.back();
        RenderData.pop_back();
        return DataToReturn;
    }
    return nullptr;
}


void  Graphics_GetCameraViewMatrix(float** Matrix)
{
	if (Matrix == nullptr ) return;
	
	Engine::Camera CurrentCamera = Context::Instance().GetSceneManager().GetCurrentCamera();

	Engine::float4x4 ViewMatrix = CurrentCamera.GetViewMatirx();

	Matrix[0][0] = ViewMatrix[0][0];	Matrix[0][1] = ViewMatrix[0][1];	Matrix[0][2] = ViewMatrix[0][2];	Matrix[0][3] = ViewMatrix[0][3];
	Matrix[1][0] = ViewMatrix[1][0];	Matrix[1][1] = ViewMatrix[1][1];	Matrix[1][2] = ViewMatrix[1][2];	Matrix[1][3] = ViewMatrix[1][3];
	Matrix[2][0] = ViewMatrix[2][0];	Matrix[2][1] = ViewMatrix[2][1];	Matrix[2][2] = ViewMatrix[2][2];	Matrix[2][3] = ViewMatrix[2][3];
	Matrix[3][0] = ViewMatrix[3][0];	Matrix[3][1] = ViewMatrix[3][1];	Matrix[3][2] = ViewMatrix[3][2];	Matrix[3][3] = ViewMatrix[3][3];
}