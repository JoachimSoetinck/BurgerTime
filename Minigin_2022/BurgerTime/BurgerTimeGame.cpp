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
#include "ButtonComponent.h"
#include "EnemyComponent.h"
#include "IngredientComponent.h"
#include "LadderComponent.h"
#include "LevelParser.h"
#include "PlatformComponent.h"
#include "SpriteComponent.h"

#include "TransformComponent.h"


void BurgerTimeGame::LoadGame() const
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level1");
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level1");
	dae::SceneManager::GetInstance().SetActiveScene(dae::SceneManager::GetInstance().GetScene(0).get());
	

	auto fpsObject = std::make_shared<dae::GameObject>();
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	fpsObject->AddComponent(std::make_shared<dae::TextComponent>("0 fps", fpsFont, SDL_Color{ 255, 255, 0 }, fpsObject));
	fpsObject->AddComponent(std::make_shared<dae::FPSComponent>(fpsObject));
	scene.Add(fpsObject);


	//bool r = dae::LevelParser::ParseOBJ("../Data/Level/Level01.txt", scene2, true);
	bool r = dae::LevelParser::ParseOBJ("../Data/Level/Level02.txt", scene3, true);

	auto backGround = std::make_shared<dae::GameObject>();
	backGround->GetComponent<dae::TransformComponent>()->SetPosition(0, 0, 0);
	backGround->AddComponent(std::make_shared<dae::RenderComponent>("BurgerTime.jpg", backGround));
	scene.Add(backGround);
	

	auto font = dae::ResourceManager::GetInstance().LoadFont("BurgerTimeFont.otf", 20);
	auto buttonStartSinglePlayer  = std::make_shared<dae::GameObject>();
	auto textComp = std::make_shared<dae::TextComponent>("Start SinglePlayer", font, SDL_Color{ 255, 255, 0 }, buttonStartSinglePlayer);
	buttonStartSinglePlayer->AddComponent(textComp);
	buttonStartSinglePlayer->GetComponent<dae::TransformComponent>()->SetPosition(280, 500, 0);
	buttonStartSinglePlayer->AddComponent(std::make_shared<dae::ButtonComponent>(buttonStartSinglePlayer));
	scene.Add(buttonStartSinglePlayer);

	auto TestSprite = std::make_shared<dae::GameObject>();
	TestSprite->GetComponent<dae::TransformComponent>()->SetPosition(0, 0, 0);
	auto render = std::make_shared<dae::RenderComponent>("PeterPepper/PlayerIdle.png", TestSprite);
	TestSprite->AddComponent(render);
	TestSprite->AddComponent(std::make_shared<dae::SpriteComponent>(TestSprite, render,3, "PeterPepper/WalkLeft.png"));
	scene.Add(TestSprite);


	
}








