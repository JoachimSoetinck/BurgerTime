#pragma once
#include <string>
#include <fstream>  
#include <iostream>  

#include "PlatformComponent.h"
#include "Scene.h"

namespace dae
{
	class LevelParser
	{
	public:
		static bool ParseOBJ(const std::string& filename, Scene& scene)
		{
			std::ifstream file(filename);
			if (!file)
				return false;



			std::string sCommand;
			// start a while iteration ending when the end of file is reached (ios::eof)
			while (!file.eof())
			{
				//read the first word of the string, use the >> operator (istream::operator>>) 
				file >> sCommand;
				//use conditional statements to process the different commands	
				if (sCommand == "#")
				{

				}
				else if (sCommand == "l")
				{
					//Vertex
					float x, y;
					file >> x >> y;

					CreateLadder(scene, x, y, "Ladder.png");

				}
				else if (sCommand == "lbp")
				{
					float x, y;
					file >> x >> y;

					CreatePlatform(scene, x, y, "LightBluePlatform.png");

				}
				else if (sCommand == "bp")
				{
					float x, y;
					file >> x >> y;

					CreatePlatform(scene, x, y, "BluePlatform.png");

				}
				else if (sCommand == "tb")
				{
					float x, y;
					file >> x >> y;
					CreateIngredient(scene, x, y, IngredientComponent::Type::TopBun);
				}

				else if (sCommand == "lt")
				{
					float x, y;
					file >> x >> y;
					CreateIngredient(scene, x, y, IngredientComponent::Type::Lettuce);
				}

				else if (sCommand == "pat")
				{
					float x, y;
					file >> x >> y;
					CreateIngredient(scene, x, y, IngredientComponent::Type::Patty);
				}

				else if (sCommand == "ch")
				{
					float x, y;
					file >> x >> y;
					CreateIngredient(scene, x, y, IngredientComponent::Type::Cheese);
				}

				else if (sCommand == "bb")
				{
					float x, y;
					file >> x >> y;
					CreateIngredient(scene, x, y, IngredientComponent::Type::BottomBun);
				}

				else if (sCommand == "tom")
				{
					float x, y;
					file >> x >> y;
					CreateIngredient(scene, x, y, IngredientComponent::Type::Tomato);
				}


				
			}

		}

	private:
		static void CreatePlatform(dae::Scene& scene, float x, float y, std::string texture) 
		{
			auto platform = std::make_shared<dae::GameObject>();

			platform->AddComponent(std::make_shared<dae::RenderComponent>(texture, platform));
			platform->AddComponent(std::make_unique<dae::PlatformComponent>(platform));
			platform->GetComponent<dae::TransformComponent>()->SetPosition(x, y, 0);
			scene.Add(platform);
		}

		static void CreateLadder(dae::Scene& scene, float x, float y, std::string texture) 
		{
			auto ladder = std::make_shared<dae::GameObject>();

			ladder->AddComponent(std::make_shared<dae::RenderComponent>(texture, ladder));
			ladder->AddComponent(std::make_unique<dae::LadderComponent>(ladder));
			ladder->GetComponent<dae::TransformComponent>()->SetPosition(x, y, 0);
			scene.Add(ladder);
		}

		static void CreateIngredient(dae::Scene& scene, float x, float y, dae::IngredientComponent::Type ingredient)
		{
			auto ingredients = std::make_shared<dae::GameObject>();

			ingredients->AddComponent(std::make_shared<dae::RenderComponent>("LightBluePlatform.png", ingredients));
			ingredients->AddComponent(std::make_unique<dae::IngredientComponent>(ingredients, ingredient));
			ingredients->GetComponent<dae::TransformComponent>()->SetPosition(x, y, 0);
			scene.Add(ingredients);
		}

	};


}
