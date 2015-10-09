#include "SceneObject.h"
#include "Context.hpp"
#include "SceneManager.h"

namespace Engine
{
	SceneObject::SceneObject(void)
    : Visiable(true)
	{
	}


	SceneObject::~SceneObject(void)
	{
	}

	void SceneObject::Update()
	{
	}

	Mesh* SceneObject::GetRenderElement()
	{
		return this->RenderElement;
	}

	bool SceneObject::IsVisiable()
	{
		return this->Visiable;
	}

	void SceneObject::SetVisiable( bool Visiable_ )
	{
		this->Visiable = Visiable_;
	}
    

	void SceneObject::AddToScene()
	{
		Context::Instance().GetSceneManager().AddSceneObject(this);
	}

}
