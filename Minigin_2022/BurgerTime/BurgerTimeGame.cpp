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
#include <LadderComponent.h>

#include "BarrierComponent.h"
#include "EnemyComponent.h"
#include "PlatformComponent.h"

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

	auto enemy1 = std::make_shared<dae::GameObject>();
	enemy1->AddComponent(std::make_shared<dae::RenderComponent>("Enemies/Sausage.png", enemy1));
	enemy1->AddComponent(std::make_shared<dae::EnemyComponent>( enemy1, glm::ivec2(50,60)));

	auto barrier1 = std::make_shared<dae::GameObject>();
	barrier1->AddComponent(std::make_shared<dae::RenderComponent>("Enemies/Sausage.png", barrier1, false));
	barrier1->AddComponent(std::make_shared<dae::BarrierComponent>( barrier1, false));
	barrier1->GetComponent<dae::TransformComponent>()->SetPosition( 725, 60, 0);
	
	scene.Add(barrier1);

	auto barrier2 = std::make_shared<dae::GameObject>();
	barrier2->AddComponent(std::make_shared<dae::RenderComponent>("Enemies/Sausage.png", barrier2, false));
	barrier2->AddComponent(std::make_shared<dae::BarrierComponent>(barrier2, true));
	barrier2->GetComponent<dae::TransformComponent>()->SetPosition(14, 60, 0);

	scene.Add(barrier2);


	scene.Add(enemy1);
	scene.Add(peterPepper);
}

void BurgerTimeGame::CreatePlatform(dae::Scene& scene, float x, float y, std::string texture) const
{
	auto platform = std::make_shared<dae::GameObject>();

	platform->AddComponent(std::make_shared<dae::RenderComponent>(texture, platform));
	platform->AddComponent(std::make_unique<dae::PlatformComponent>(platform));
	platform ->GetComponent<dae::TransformComponent>()->SetPosition(x, y, 0);
	scene.Add(platform);
}

void BurgerTimeGame::CreateLadder(dae::Scene& scene, float x, float y, std::string texture) const
{
	auto ladder = std::make_shared<dae::GameObject>();

	ladder->AddComponent(std::make_shared<dae::RenderComponent>(texture, ladder));
	ladder->AddComponent(std::make_unique<dae::LadderComponent>(ladder));
	ladder->GetComponent<dae::TransformComponent>()->SetPosition(x, y, 0);
	scene.Add(ladder);
}

void BurgerTimeGame::CreateLevel(dae::Scene& scene) const
{
	CreateLadder(scene, 50, 90, "Ladder.png");
	CreateLadder(scene, 50, 145, "Ladder.png");
	CreateLadder(scene, 50, 310, "Ladder.png");
	CreateLadder(scene, 50, 365, "Ladder.png");
	CreateLadder(scene, 50, 420, "Ladder.png");
	CreateLadder(scene, 50, 475, "Ladder.png");
	CreateLadder(scene, 50, 530, "Ladder.png");
	CreateLadder(scene, 130, 200, "Ladder.png");
	CreateLadder(scene, 130, 255, "Ladder.png");
	CreateLadder(scene, 130, 310, "Ladder.png");
	CreateLadder(scene, 130, 365, "Ladder.png");
	CreateLadder(scene, 130, 420, "Ladder.png");
	CreateLadder(scene, 210, 90, "Ladder.png");
	CreateLadder(scene, 210, 145, "Ladder.png");
	CreateLadder(scene, 210, 200, "Ladder.png");
	CreateLadder(scene, 210, 255, "Ladder.png");
	CreateLadder(scene, 210, 310, "Ladder.png");
	CreateLadder(scene, 210, 365, "Ladder.png");
	CreateLadder(scene, 210, 420, "Ladder.png");
	CreateLadder(scene, 210, 475, "Ladder.png");
	CreateLadder(scene, 210, 530, "Ladder.png");
	CreateLadder(scene, 290, 90, "Ladder.png");
	CreateLadder(scene, 290, 145, "Ladder.png");
	CreateLadder(scene, 290, 200, "Ladder.png");
	CreateLadder(scene, 370, 90, "Ladder.png");
	CreateLadder(scene, 370, 145, "Ladder.png");
	CreateLadder(scene, 370, 200, "Ladder.png");
	CreateLadder(scene, 370, 255, "Ladder.png");
	CreateLadder(scene, 370, 310, "Ladder.png");
	CreateLadder(scene, 370, 365, "Ladder.png");
	CreateLadder(scene, 370, 420, "Ladder.png");
	CreateLadder(scene, 370, 475, "Ladder.png");
	CreateLadder(scene, 370, 530, "Ladder.png");
	CreateLadder(scene, 450, 200, "Ladder.png");
	CreateLadder(scene, 450, 255, "Ladder.png");
	CreateLadder(scene, 450, 310, "Ladder.png");
	CreateLadder(scene, 530, 90, "Ladder.png");
	CreateLadder(scene, 530, 145, "Ladder.png");
	CreateLadder(scene, 530, 200, "Ladder.png");
	CreateLadder(scene, 530, 255, "Ladder.png");
	CreateLadder(scene, 530, 310, "Ladder.png");
	CreateLadder(scene, 530, 365, "Ladder.png");
	CreateLadder(scene, 530, 420, "Ladder.png");
	CreateLadder(scene, 530, 475, "Ladder.png");
	CreateLadder(scene, 530, 530, "Ladder.png");
	CreateLadder(scene, 610, 310, "Ladder.png");
	CreateLadder(scene, 610, 365, "Ladder.png");
	CreateLadder(scene, 610, 420, "Ladder.png");
	CreateLadder(scene, 610, 475, "Ladder.png");
	CreateLadder(scene, 610, 530, "Ladder.png");
	CreateLadder(scene, 690, 90, "Ladder.png");
	CreateLadder(scene, 690, 145, "Ladder.png");
	CreateLadder(scene, 690, 200, "Ladder.png");
	CreateLadder(scene, 690, 255, "Ladder.png");
	CreateLadder(scene, 690, 420, "Ladder.png");
	CreateLadder(scene, 690, 475, "Ladder.png");
	CreateLadder(scene, 690, 530, "Ladder.png");

	CreatePlatform(scene, 50, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 90, 90, "BluePlatform.png");
	CreatePlatform(scene, 130, 90, "BluePlatform.png");
	CreatePlatform(scene, 170, 90, "BluePlatform.png");
	CreatePlatform(scene, 210, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 250, 90, "BluePlatform.png");
	CreatePlatform(scene, 290, 90, "BluePlatform.png");
	CreatePlatform(scene, 330, 90, "BluePlatform.png");
	CreatePlatform(scene, 370, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 410, 90, "BluePlatform.png");
	CreatePlatform(scene, 450, 90, "BluePlatform.png");
	CreatePlatform(scene, 490, 90, "BluePlatform.png");
	CreatePlatform(scene, 530, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 570, 90, "BluePlatform.png");
	CreatePlatform(scene, 610, 90, "BluePlatform.png");
	CreatePlatform(scene, 650, 90, "BluePlatform.png");
	CreatePlatform(scene, 690, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 50, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 90, 200, "BluePlatform.png");
	CreatePlatform(scene, 130, 200, "BluePlatform.png");
	CreatePlatform(scene, 170, 200, "BluePlatform.png");
	CreatePlatform(scene, 210, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 370, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 410, 200, "BluePlatform.png");
	CreatePlatform(scene, 450, 200, "BluePlatform.png");
	CreatePlatform(scene, 490, 200, "BluePlatform.png");
	CreatePlatform(scene, 530, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 570, 200, "BluePlatform.png");
	CreatePlatform(scene, 610, 200, "BluePlatform.png");
	CreatePlatform(scene, 650, 200, "BluePlatform.png");
	CreatePlatform(scene, 690, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 210, 255, "LightBluePlatform.png");
	CreatePlatform(scene, 250, 255, "BluePlatform.png");
	CreatePlatform(scene, 290, 255, "BluePlatform.png");
	CreatePlatform(scene, 330, 255, "BluePlatform.png");
	CreatePlatform(scene, 370, 255, "LightBluePlatform.png");
	CreatePlatform(scene, 50, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 90, 310, "BluePlatform.png");
	CreatePlatform(scene, 130, 310, "BluePlatform.png");
	CreatePlatform(scene, 170, 310, "BluePlatform.png");
	CreatePlatform(scene, 210, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 530, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 570, 310, "BluePlatform.png");
	CreatePlatform(scene, 610, 310, "BluePlatform.png");
	CreatePlatform(scene, 650, 310, "BluePlatform.png");
	CreatePlatform(scene, 690, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 210, 365, "LightBluePlatform.png");
	CreatePlatform(scene, 250, 365, "BluePlatform.png");
	CreatePlatform(scene, 290, 365, "BluePlatform.png");
	CreatePlatform(scene, 330, 365, "BluePlatform.png");
	CreatePlatform(scene, 370, 365, "LightBluePlatform.png");
	CreatePlatform(scene, 410, 365, "BluePlatform.png");
	CreatePlatform(scene, 450, 365, "BluePlatform.png");
	CreatePlatform(scene, 490, 365, "BluePlatform.png");
	CreatePlatform(scene, 530, 365, "LightBluePlatform.png");
	CreatePlatform(scene, 530, 420, "LightBluePlatform.png");
	CreatePlatform(scene, 570, 420, "BluePlatform.png");
	CreatePlatform(scene, 610, 420, "BluePlatform.png");
	CreatePlatform(scene, 650, 420, "BluePlatform.png");
	CreatePlatform(scene, 690, 420, "LightBluePlatform.png");
	CreatePlatform(scene, 50, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 90, 475, "BluePlatform.png");
	CreatePlatform(scene, 130, 475, "BluePlatform.png");
	CreatePlatform(scene, 170, 475, "BluePlatform.png");
	CreatePlatform(scene, 210, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 250, 475, "BluePlatform.png");
	CreatePlatform(scene, 290, 475, "BluePlatform.png");
	CreatePlatform(scene, 330, 475, "BluePlatform.png");
	CreatePlatform(scene, 370, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 410, 475, "BluePlatform.png");
	CreatePlatform(scene, 450, 475, "BluePlatform.png");
	CreatePlatform(scene, 490, 475, "BluePlatform.png");
	CreatePlatform(scene, 530, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 50, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 90, 585, "BluePlatform.png");
	CreatePlatform(scene, 130, 585, "BluePlatform.png");
	CreatePlatform(scene, 170, 585, "BluePlatform.png");
	CreatePlatform(scene, 210, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 250, 585, "BluePlatform.png");
	CreatePlatform(scene, 290, 585, "BluePlatform.png");
	CreatePlatform(scene, 330, 585, "BluePlatform.png");
	CreatePlatform(scene, 370, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 410, 585, "BluePlatform.png");
	CreatePlatform(scene, 450, 585, "BluePlatform.png");
	CreatePlatform(scene, 490, 585, "BluePlatform.png");
	CreatePlatform(scene, 530, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 570, 585, "BluePlatform.png");
	CreatePlatform(scene, 610, 585, "BluePlatform.png");
	CreatePlatform(scene, 650, 585, "BluePlatform.png");
	CreatePlatform(scene, 690, 585, "LightBluePlatform.png");



	CreateIngredient(scene, 93, 85, dae::IngredientComponent::Type::TopBun);
	CreateIngredient(scene, 93, 190, dae::IngredientComponent::Type::Lettuce);
	CreateIngredient(scene, 93, 300, dae::IngredientComponent::Type::Patty);
	CreateIngredient(scene, 93, 470, dae::IngredientComponent::Type::Patty);
	CreateIngredient(scene, 93, 575, dae::IngredientComponent::Type::BottomBun);

	CreateIngredient(scene, 255, 85, dae::IngredientComponent::Type::TopBun);
	CreateIngredient(scene, 255, 245, dae::IngredientComponent::Type::Lettuce);
	CreateIngredient(scene, 255, 355, dae::IngredientComponent::Type::Patty);
	CreateIngredient(scene, 255, 470, dae::IngredientComponent::Type::Patty);
	CreateIngredient(scene, 255, 575, dae::IngredientComponent::Type::BottomBun);


	CreateIngredient(scene, 420, 85, dae::IngredientComponent::Type::TopBun);
	CreateIngredient(scene, 420, 190, dae::IngredientComponent::Type::Lettuce);
	CreateIngredient(scene, 420, 355, dae::IngredientComponent::Type::Patty);
	CreateIngredient(scene, 420, 470, dae::IngredientComponent::Type::Patty);
	CreateIngredient(scene, 420, 575, dae::IngredientComponent::Type::BottomBun);

	CreateIngredient(scene, 580, 85, dae::IngredientComponent::Type::TopBun);
	CreateIngredient(scene, 580, 190, dae::IngredientComponent::Type::Lettuce);
	CreateIngredient(scene, 580, 300, dae::IngredientComponent::Type::Patty);
	CreateIngredient(scene, 580, 410, dae::IngredientComponent::Type::Patty);
	CreateIngredient(scene, 580, 575, dae::IngredientComponent::Type::BottomBun);
}

void BurgerTimeGame::CreateIngredient(dae::Scene& scene, float x, float y, dae::IngredientComponent::Type ingredient) const
{
	auto ingredients = std::make_shared<dae::GameObject>();

	ingredients->AddComponent(std::make_shared<dae::RenderComponent>("LightBluePlatform.png", ingredients));
	ingredients->AddComponent(std::make_unique<dae::IngredientComponent>(ingredients, ingredient));
	ingredients->GetComponent<dae::TransformComponent>()->SetPosition(x, y, 0);
	scene.Add(ingredients);
}




