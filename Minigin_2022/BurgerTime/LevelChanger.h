#pragma once
#include <set>

#include "IngredientComponent.h"
#include "Scene.h"

namespace dae
{
	class LevelChanger : public BaseComponent
	{
	public:
		LevelChanger(int Currentscene, int nextScene);
		~LevelChanger() = default;
		LevelChanger(const LevelChanger& other) = delete;
		LevelChanger(LevelChanger&& other) noexcept = delete;
		LevelChanger& operator=(const LevelChanger& other) = delete;
		LevelChanger& operator=(LevelChanger&& other) noexcept = delete;

		void Render() const override;
		void Update() override;

	private:
		int m_CurrentScene;
		int m_nextSceneNr;

		std::vector<std::shared_ptr<IngredientComponent>> m_components;

		int m_nrOnTrays;
	};

}

