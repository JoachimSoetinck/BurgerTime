#pragma once
#include "IngredientComponent.h"
#include "Minigin.h"

#pragma warning( push )
#pragma warning( disable : 4201)
// Your function
#pragma warning( pop ) 

class BurgerTimeGame : public dae::Minigin
{
public:
	void CreateMenu(dae::Scene& scene) const;
	void LoadGame() const override;

private:

	
	
};

