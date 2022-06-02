#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		
		void Update();
		void Render() const;

		std::vector <std::shared_ptr<GameObject>> GetObjects() { return  m_Objects; }
		void DeleteObjects();
		int GetId() { return m_IdCounter; };

		~Scene();
		Scene(const Scene& other) = default;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;

		
	};

}
