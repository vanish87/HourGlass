//
//  Graphics_Bridge.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef Graphics_Bridge_hpp
#define Graphics_Bridge_hpp

#include "SharedDataType.h"


#ifdef __cplusplus
extern "C" {
#endif
void* Graphics_CreateMesh(enum MeshType Type);
void  Graphics_GetLocation(void* MeshData, float* x, float* y, float* z);
void  Graphics_GetScale(void* MeshData, float* x, float* y, float* z);
void* Graphics_GetRawData(void* MeshData);


bool  Graphics_LockRenderQueue();
bool  Graphics_UnlockRenderQueue();
bool  Graphics_IsRenderQueueEmpty();
void* Graphics_PopAndGetMeshData();
void  Graphics_GetCameraViewMatrix(float Matrix[4][4]);
    
unsigned long Graphics_GetNumberOfMeshes();

#ifdef __cplusplus
}
#endif
#endif /* Graphics_Bridge_hpp */
