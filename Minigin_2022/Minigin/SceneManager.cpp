#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update()
{
	if (m_pActiveScene)
		m_pActiveScene->Update();
}

void dae::SceneManager::FixedUpdate(float )
{
}

void dae::SceneManager::Render()
{
	if (m_pActiveScene)
		m_pActiveScene->Render();
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(int nr)
{
	return m_Scenes[nr];
}

void dae::SceneManager::SetActiveScene(Scene* scene)
{
	m_pActiveScene = scene;
	m_ActiveSceneNr = scene->GetId();
}


dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
