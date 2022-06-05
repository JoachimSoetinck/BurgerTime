#pragma once
#include "IngredientComponent.h"
#include "Minigin.h"

class BurgerTimeGame : public dae::Minigin
{
public:
	void CreateMenu(dae::Scene& scene) const;
	void LoadGame() const override;

private:

	
	
};

