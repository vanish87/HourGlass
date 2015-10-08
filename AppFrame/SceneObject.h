#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#pragma once
#include "PreDeclear.h"
#include "Mesh.hpp"

namespace Engine
{
	class SceneObject
	{
	public:
		SceneObject(void);
		SceneObject(Mesh* render_element)
			:RenderElement(render_element), Visiable(true)
		{

		};
		~SceneObject(void);

		//do update aabb and set model_matrix equals to its render_element_'s
		virtual void Update();
		virtual Mesh* GetRenderElement();

		virtual void AddToScene();

		bool IsVisiable();
		void SetVisiable(bool visiable);
        
	protected:
        Mesh* RenderElement;

		bool Visiable;
	};

}

#endif

