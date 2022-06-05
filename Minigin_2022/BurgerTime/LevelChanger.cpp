#include "LevelChanger.h"

#include "ServiceLocator.h"

dae::LevelChanger::LevelChanger(int Currentscene, int nextScene, bool playmusic): m_CurrentScene{Currentscene}, m_nextSceneNr{nextScene}, m_canPlayMusic{playmusic}
{
	auto objects = SceneManager::GetInstance().GetScene(m_CurrentScene)->GetObjects();

	for (auto o: objects)
	{
		if(o->GetComponent<IngredientComponent>())
		{
			m_components.push_back(o->GetComponent<IngredientComponent>());
		}
		if (o->GetComponent<PeterPepperComponent>())
		{
			m_pPeterPepper = o->GetComponent<PeterPepperComponent>();
			break;
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
		auto objs = SceneManager::GetInstance().GetScene(m_nextSceneNr)->GetObjects();
		for (auto obj: objs)
		{
			if(obj->GetComponent<PeterPepperComponent>())
			{
				obj->GetComponent<PeterPepperComponent>()->GivePoints(m_pPeterPepper->GetScore());
			}
		}
		SceneManager::GetInstance().SetActiveScene(SceneManager::GetInstance().GetScene(m_nextSceneNr).get());
	}

	

	if (dae::SceneManager::GetInstance().GetActiveSceneNr() >= 1 && m_canPlayMusic)
	{
		ServiceLocator::GetSoundSystem().RegisterSound("../Data/Sound/background.mp3", true);
		m_canPlayMusic = false;
	}
	m_nrOnTrays = 0;
}
