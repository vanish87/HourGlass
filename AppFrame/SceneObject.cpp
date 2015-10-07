#include "SceneObject.h"
#include "Context.hpp"
#include "SceneManager.h"

namespace Engine
{
	SceneObject::SceneObject(void)
    :Location(float3(0,0,0)), Visiable(true)
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
    
    
    void SceneObject::SetLocation(const float3& NewLocation)
    {
		if (this->RenderElement != nullptr)
		{
			this->RenderElement->SetLocation(NewLocation);
		}
    }

	void SceneObject::AddToScene()
	{
		Context::Instance().GetSceneManager().AddSceneObject(this);
	}

}
