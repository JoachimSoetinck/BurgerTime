#include "BurgerTimeGame.h"

#include <SDL_pixels.h>

#include "FPSComponent.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "PeterPepperComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "BarrierComponent.h"
#include "EnemyComponent.h"
#include "IngredientComponent.h"
#include "LadderComponent.h"
#include "LevelParser.h"
#include "PlatformComponent.h"
#include "SaltComponent.h"
#include "TransformComponent.h"
#include "TrayComponent.h"

void BurgerTimeGame::LoadGame() const
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");


	auto backGround = std::make_shared<dae::GameObject>();

	CreateLevel(scene);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto fpsObject = std::make_shared<dae::GameObject>();
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	fpsObject->AddComponent(std::make_shared<dae::TextComponent>("0 fps", fpsFont, SDL_Color{ 255, 255, 0 }, fpsObject));
	fpsObject->AddComponent(std::make_shared<dae::FPSComponent>(fpsObject));
	scene.Add(fpsObject);

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


	auto enemy1 = std::make_shared<dae::GameObject>();
	enemy1->AddComponent(std::make_shared<dae::RenderComponent>("Enemies/Sausage.png", enemy1));
	enemy1->AddComponent(std::make_shared<dae::EnemyComponent>( enemy1, glm::ivec2(50,60), peterPepper));



	CreateBarrier(scene, 14, 60, true);
	CreateBarrier(scene, 14, 180, true);
	CreateBarrier(scene, 14, 280, true);
	CreateBarrier(scene, 14, 450, true);
	CreateBarrier(scene, 14, 560, true);

	CreateBarrier(scene, 14, 180, true);
	CreateBarrier(scene, 250, 180, false);
	CreateBarrier(scene, 340, 180, true);
	CreateBarrier(scene, 180, 230, true);
	CreateBarrier(scene, 410, 230, false);
	CreateBarrier(scene, 250, 280, false);
	CreateBarrier(scene, 500, 280, true);
	CreateBarrier(scene, 180, 340, true);
	CreateBarrier(scene, 570, 340, false);
	CreateBarrier(scene, 500, 390, true);
	CreateBarrier(scene, 570, 450, false);
	CreateBarrier(scene, 725, 60, false);
	CreateBarrier(scene, 725, 180, false);
	CreateBarrier(scene, 725, 280, false);
	CreateBarrier(scene, 725, 400, false);
	CreateBarrier(scene, 725, 560, false);
	


	scene.Add(enemy1);
	scene.Add(peterPepper);
}



void BurgerTimeGame::CreateLevel(dae::Scene& scene) const
{
	bool r = dae::LevelParser::ParseOBJ("../Data/Level/Level01.txt", scene);

}

void BurgerTimeGame::CreateBarrier(dae::Scene& scene, float x, float y, bool leftSide) const
{
	auto barrier2 = std::make_shared<dae::GameObject>();
	barrier2->AddComponent(std::make_shared<dae::RenderComponent>("Enemies/Sausage.png", barrier2, false));
	barrier2->AddComponent(std::make_shared<dae::BarrierComponent>(barrier2, true));
	barrier2->GetComponent<dae::TransformComponent>()->SetPosition(x, y, leftSide);

	scene.Add(barrier2);

}





