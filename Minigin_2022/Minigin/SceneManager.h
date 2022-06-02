#pragma once
#include "Singleton.h"
#include <vector>
#include <iostream>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		
		void Update();
		void FixedUpdate(float fixedTimeStep);
		void Render();
		std::shared_ptr<Scene> GetScene(int nr);
		void SetActiveScene(Scene* scene);
		int GetActiveSceneNr() const;
		
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		Scene* m_pActiveScene = nullptr;
		int m_ActiveSceneNr{};
		bool m_SceneChanged = false;
	};
}
