#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#pragma once
#include "PreDeclear.h"
#include "Vector.h"
#include "Mesh.hpp"

namespace Engine
{
	class SceneObject
	{
	public:
		SceneObject(void);
		SceneObject(Mesh* render_element)
			:RenderElement(render_element),Location(float3(0,0,0)), Visiable(true)
		{
            
		};
		~SceneObject(void);

		//do update aabb and set model_matrix equals to its render_element_'s
		virtual void Update();
		virtual Mesh* GetRenderElement();

		virtual void AddToScene();

		bool IsVisiable();
		void SetVisiable(bool visiable);
        
        void SetLocation(float3 NewLocation);

	protected:

        Mesh* RenderElement;
        float3 Location;

		bool Visiable;
	};

}

#endif

