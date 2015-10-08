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
#include "Matrix.h"

#include "Graphics_Bridge.hpp"

namespace Engine
{
    class Mesh
    {
        friend class SceneObject;
    public:
        Mesh(MeshType Type = CUBE, float3 Location = float3(0,0,0));
        virtual ~Mesh();

		void SetLocation(const float3& NewLocation);
		void SetScale(const float3& NewScale);
		float3 GetLocation() const ;
		float3 GetScale() const ;
        void* GetRawData();
        
	private:
		float4x4 MeshMatrix;
        void* Data;
    };
}

#endif /* Mesh_hpp */
