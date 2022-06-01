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
	bool r = dae::LevelParser::ParseOBJ("../Data/Level/Level01.txt", scene);




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




