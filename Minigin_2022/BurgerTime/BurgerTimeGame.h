#pragma once
#include "IngredientComponent.h"
#include "Minigin.h"

class BurgerTimeGame : public dae::Minigin
{
public:
	void LoadGame() const override;

private:

	void CreateLevel(dae::Scene& scene, bool isCoop) const;
	
};

