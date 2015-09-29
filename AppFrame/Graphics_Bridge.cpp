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