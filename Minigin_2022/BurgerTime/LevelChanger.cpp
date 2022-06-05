#include "LevelChanger.h"

dae::LevelChanger::LevelChanger(int Currentscene, int nextScene): m_CurrentScene{Currentscene}, m_nextSceneNr{nextScene}
{
	auto objects = SceneManager::GetInstance().GetScene(m_CurrentScene)->GetObjects();

	for (auto o: objects)
	{
		if(o->GetComponent<IngredientComponent>())
		{
			m_components.push_back(o->GetComponent<IngredientComponent>());
		}
	}

	std::cout << "Ingredients:" << m_components.size();
}

void dae::LevelChanger::Render() const
{
}

void dae::LevelChanger::Update()
{
	for (auto& ingredient : m_components)
	{
		if (ingredient->IsOnTray() == true)
			++m_nrOnTrays;
	}

	if(m_nrOnTrays == static_cast<int>(m_components.size()))
	{
		SceneManager::GetInstance().SetActiveScene(SceneManager::GetInstance().GetScene(m_nextSceneNr).get());
	}

	m_nrOnTrays = 0;
}
