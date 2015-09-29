#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#pragma once
#include <vector>
#include <iterator>

#include "SceneObject.h"
#include "Mutex.hpp"

namespace Engine
{
	class SceneManager
	{
	public:
		SceneManager(void);
		~SceneManager(void);

		void AddSceneObject(SceneObject* scene_object);
		//void AddLight(Light* light);

		void Flush();
		void Update();
        
        void LockRenderQueue();
        void UnlockRenderQueue();
        
		//std::vector<Light*> GetLights();
		std::vector<Mesh*>& GetRenderList(){return render_list_;};
	protected:
		std::vector<Mesh*> render_list_;
		std::vector<SceneObject*> scene_object_list;
        
        Tool::Mutex RenderingLock;

		//std::vector<Light*> lights_;
	};

}
#endif

