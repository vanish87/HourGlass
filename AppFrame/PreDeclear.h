//
//  PreDeclear.h
//  AppFrame
//
//  Created by Yuan Li on 2015/09/20.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef PreDeclear_h
#define PreDeclear_h

//#include <vector_types.h>
#include <stdint.h>

namespace Engine {
    
    class ReturnCode;
    class SceneManager;
    class Mesh;
    
    template <typename T>
    class Vec2;
    typedef Vec2<int32_t> int2;
    typedef Vec2<float> float2;
    
    template <typename T>
    class Vec3;
    typedef Vec3<int32_t> int3;
    typedef Vec3<float> float3;
    
    template <typename T>
    class Vec4;
    typedef Vec4<int32_t> int4;
    typedef Vec4<float> float4;
}


//typedef vector_float3 Vector3;

#endif /* PreDeclear_h */
