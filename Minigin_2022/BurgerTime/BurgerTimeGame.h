#pragma once
#include "IngredientComponent.h"
#include "Minigin.h"

class BurgerTimeGame : public dae::Minigin
{
public:
	void LoadGame() const override;

private:
	void CreatePlatform(dae::Scene& scene, float x, float y, std::string texture) const;
	void CreateLadder(dae::Scene& scene, float x, float y, std::string texture) const;
	void CreateLevel(dae::Scene& scene) const;

	void CreateIngredient(dae::Scene& scene, float x, float y, dae::IngredientComponent::Type ingredient)const;
};

