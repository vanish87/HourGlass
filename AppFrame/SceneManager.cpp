#include "SceneManager.h"

namespace Engine
{

	SceneManager::SceneManager(void)
	{
	}


	SceneManager::~SceneManager(void)
	{
	}

	void SceneManager::Flush()
	{
        this->RenderingLock.Lock();
        render_list_.clear();        
        std::vector<SceneObject*>::iterator so;
        for(so = scene_object_list.begin() ; so < scene_object_list.end(); so++)
        {
            bool IsVisiable = (*so)->IsVisiable();
            if( IsVisiable )
            {
                render_list_.push_back((*so)->GetRenderElement());
            }
        }
        this->RenderingLock.Unlock();
	}
    
    
    void SceneManager::LockRenderQueue()
    {
        this->RenderingLock.Lock();
    };
    void SceneManager::UnlockRenderQueue()
    {
        this->RenderingLock.Unlock();
    };

	void SceneManager::Update()
		//do scene cull here
	{
		std::vector<SceneObject*>::iterator so;
		for(so = scene_object_list.begin() ; so < scene_object_list.end(); so++)
		{
			(*so)->Update();//do update aabb and set model_matrix equals to its render_element_'s
		}
	}

    void SceneManager::AddSceneObject( SceneObject* scene_object )
	{
		scene_object_list.push_back(scene_object);
	}

}
