#pragma once
#include <string>
#include <fstream>  
#include <iostream>  

#include "PlatformComponent.h"
#include "BarrierComponent.h"
#include "EnemyComponent.h"
#include "SaltComponent.h"
#include "Scene.h"
#include "TrayComponent.h"

namespace dae
{
	class LevelParser
	{
	public:
		static bool ParseOBJ(const std::string& filename, Scene& scene, bool isCoop)
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

				else if (sCommand == "bar")
				{
					float x, y;
					int z;
					file >> x >> y >> z;
					CreateBarrier(scene, x, y, z);
				}
				else if (sCommand == "tr")
				{
					float x, y;
					bool z;
					file >> x >> y;
					CreateTray(scene, x, y);
				}
				else if (sCommand == "hot")
				{
					float x, y;
					bool z;
					file >> x >> y;
					if (isCoop)
						CreateEnemy(scene, x, y);
				}

				else if (sCommand == "pet")
				{
					float x, y;
					bool z;
					file >> x >> y;
					CreatePeter(scene, x, y);
				}

				else if (sCommand == "sal")
				{
					float x, y;
					bool z;
					file >> x >> y;
					if (isCoop)
						CreateSalt(scene, x, y);
				}
				sCommand = "";


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

		static void CreateBarrier(dae::Scene& scene, float x, float y, bool leftSide)
		{

			auto barrier2 = std::make_shared<dae::GameObject>();
			barrier2->AddComponent(std::make_shared<dae::RenderComponent>("Enemies/Sausage.png", barrier2, false));
			barrier2->AddComponent(std::make_shared<dae::BarrierComponent>(barrier2, leftSide));
			barrier2->GetComponent<dae::TransformComponent>()->SetPosition(x, y, leftSide);

			scene.Add(barrier2);

		}
		static void CreateTray(dae::Scene& scene, float x, float y)
		{

			auto tray = std::make_shared<dae::GameObject>();
			tray->AddComponent(std::make_shared<dae::RenderComponent>("Tray.png", tray));
			tray->GetComponent<dae::TransformComponent>()->SetPosition(x, y, 0);
			tray->AddComponent(std::make_shared<dae::TrayComponent>(tray));
			scene.Add(tray);

		}
		static void CreateEnemy(dae::Scene& scene, float x, float y)
		{

			auto enemy1 = std::make_shared<dae::GameObject>();
			enemy1->AddComponent(std::make_shared<dae::RenderComponent>("Enemies/Sausage.png", enemy1));
			enemy1->AddComponent(std::make_shared<dae::EnemyComponent>(enemy1, glm::ivec2(x, y)));
			scene.Add(enemy1);

		}

		

		static void CreatePeter(dae::Scene& scene, float x, float y)
		{

			auto peterPepper = std::make_shared<dae::GameObject>();
			auto player = std::make_shared<dae::PeterPepperComponent>(peterPepper);
			peterPepper->AddComponent(player);
			peterPepper->GetComponent<dae::TransformComponent>()->SetPosition(glm::vec3{ 375, 550, 0 });

			//score bord
			auto healthText = std::make_shared<dae::GameObject>();
			healthText->GetComponent<dae::TransformComponent>()->SetPosition(150, 10, 0);
			auto lives = std::make_shared<dae::LivesComponent>(healthText, SDL_Color{ 255,255,0 }, player);
			healthText->AddComponent(lives);

			scene.Add(healthText);

			player->AddObserver(lives);


			auto scoreText = std::make_shared<dae::GameObject>();
			scoreText->GetComponent<dae::TransformComponent>()->SetPosition(250, 10, 0);
			auto score = std::make_shared<dae::ScoreComponent>(peterPepper, SDL_Color{ 255,255,0 }, peterPepper);
			scoreText->AddComponent(score);
			scoreText->GetComponent<dae::ScoreComponent>()->SetTextLocation(glm::vec3{ 250, 10, 00 });
			scene.Add(scoreText);

			player->AddObserver(score);

			const auto peterPepperImage = std::make_shared<dae::RenderComponent>("PeterPepper/PlayerIdle.png", peterPepper);
			peterPepper->AddComponent(peterPepperImage);


			//attack part salt
			auto salt = std::make_shared<dae::GameObject>();
			salt->GetComponent<dae::TransformComponent>()->SetPosition(-50, 10, -0);
			salt->AddComponent(std::make_shared<dae::RenderComponent>("PeterPepper/Salt.png", salt));
			auto saltComp = std::make_shared<dae::SaltComponent>(salt, peterPepper->GetComponent<dae::PeterPepperComponent>());

			salt->AddComponent(saltComp);
			scene.Add(salt);

			peterPepper->AddChild(salt);
			scene.Add(peterPepper);

			
		}

		static void CreateSalt(dae::Scene& scene, int x, int y)
		{

			auto mssSalt = std::make_shared<dae::GameObject>();
			auto player = std::make_shared<dae::PeterPepperComponent>(mssSalt, 1);
			mssSalt->AddComponent(player);
			mssSalt->GetComponent<dae::TransformComponent>()->SetPosition(glm::vec3{ x, y, 0 });

			//score bord
			auto healthText = std::make_shared<dae::GameObject>();
			healthText->GetComponent<dae::TransformComponent>()->SetPosition(400, 10, 0);
			auto lives = std::make_shared<dae::LivesComponent>(healthText, SDL_Color{ 0,255,255 }, player);
			healthText->AddComponent(lives);

			scene.Add(healthText);

			player->AddObserver(lives);


			auto scoreText = std::make_shared<dae::GameObject>();
			scoreText->GetComponent<dae::TransformComponent>()->SetPosition(250, 10, 0);
			auto score = std::make_shared<dae::ScoreComponent>(mssSalt, SDL_Color{ 0,255,255 }, mssSalt);
			scoreText->AddComponent(score);
			scoreText->GetComponent<dae::ScoreComponent>()->SetTextLocation(glm::vec3{ 600, 10, 00 });
			scene.Add(scoreText);

			player->AddObserver(score);

			const auto peterPepperImage = std::make_shared<dae::RenderComponent>("PeterPepper/PlayerIdle.png", mssSalt);
			mssSalt->AddComponent(peterPepperImage);


			//attack part salt
			auto salt = std::make_shared<dae::GameObject>();
			salt->GetComponent<dae::TransformComponent>()->SetPosition(-50, 10, -0);
			salt->AddComponent(std::make_shared<dae::RenderComponent>("PeterPepper/Salt.png", salt));
			auto saltComp = std::make_shared<dae::SaltComponent>(salt, mssSalt->GetComponent<dae::PeterPepperComponent>());

			salt->AddComponent(saltComp);
			scene.Add(salt);

			mssSalt->AddChild(salt);
			scene.Add(mssSalt);

		}

		
	};

	
}
