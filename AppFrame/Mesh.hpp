//
//  Mesh.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/29.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include "PreDeclear.h"
#include "Vector.h"

namespace Engine
{
    class Mesh
    {
        friend class SceneObject;
    public:
        Mesh(void* Data, float3 Location = float3(0,0,0));
        virtual ~Mesh();
        
        void SetLocation(const float3& NewLocation);
        float3 GetLocation();
        void* GetRawData();
        
    private:
        float3 Location;
        void* Data;
    };
}

#endif /* Mesh_hpp */
