
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
#include "LevelChanger.h"
#include "LevelParser.h"
#include "PlatformComponent.h"
#include "SpriteComponent.h"

#include "TransformComponent.h"


void BurgerTimeGame::CreateMenu(dae::Scene& scene) const
{
	auto backGround = std::make_shared<dae::GameObject>();
	backGround->GetComponent<dae::TransformComponent>()->SetPosition(0, 0, 0);
	backGround->AddComponent(std::make_shared<dae::RenderComponent>("BurgerTime.jpg", backGround));
	scene.Add(backGround);


	auto font = dae::ResourceManager::GetInstance().LoadFont("BurgerTimeFont.otf", 20);
	auto buttonStartSinglePlayer = std::make_shared<dae::GameObject>();
	auto textComp = std::make_shared<dae::TextComponent>("Start SinglePlayer", font, SDL_Color{ 255, 255, 0 }, buttonStartSinglePlayer);
	buttonStartSinglePlayer->AddComponent(textComp);
	buttonStartSinglePlayer->GetComponent<dae::TransformComponent>()->SetPosition(280, 500, 0);
	buttonStartSinglePlayer->AddComponent(std::make_shared<dae::ButtonComponent>(buttonStartSinglePlayer));
	scene.Add(buttonStartSinglePlayer);

	auto buttonStartCoop = std::make_shared<dae::GameObject>();
	textComp = std::make_shared<dae::TextComponent>("2:Start Coop", font, SDL_Color{ 255, 255, 0 }, buttonStartCoop);
	buttonStartCoop->AddComponent(textComp);
	buttonStartCoop->GetComponent<dae::TransformComponent>()->SetPosition(280, 570, 0);
	buttonStartCoop->AddComponent(std::make_shared<dae::ButtonComponent>(buttonStartCoop));
	scene.Add(buttonStartCoop);
}

void BurgerTimeGame::LoadGame() const
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& scene2 = dae::SceneManager::GetInstance().CreateScene("Level1");
	auto& scene3 = dae::SceneManager::GetInstance().CreateScene("Level2");
	auto& scene4 = dae::SceneManager::GetInstance().CreateScene("Level3");

	auto& scene5 = dae::SceneManager::GetInstance().CreateScene("Level1Coop");
	auto& scene6 = dae::SceneManager::GetInstance().CreateScene("Level2Coop");
	auto& scene7 = dae::SceneManager::GetInstance().CreateScene("Level3Coop");
	dae::SceneManager::GetInstance().SetActiveScene(dae::SceneManager::GetInstance().GetScene(0).get());


	auto fpsObject = std::make_shared<dae::GameObject>();
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	fpsObject->AddComponent(std::make_shared<dae::TextComponent>("0 fps", fpsFont, SDL_Color{ 255, 255, 0 }, fpsObject));
	fpsObject->AddComponent(std::make_shared<dae::FPSComponent>(fpsObject));
	scene.Add(fpsObject);

	bool r = dae::LevelParser::ParseOBJ("../Data/Level/Level01.txt", scene2, false);

	auto level = std::make_shared<dae::GameObject>();
	level->AddComponent(std::make_shared<dae::LevelChanger>(1, 2));
	scene2.Add(level);


	r = dae::LevelParser::ParseOBJ("../Data/Level/Level02.txt", scene3, false);
	auto level2 = std::make_shared<dae::GameObject>();
	level2->AddComponent(std::make_shared<dae::LevelChanger>(2, 3));
	scene3.Add(level2);


	r = dae::LevelParser::ParseOBJ("../Data/Level/Level03.txt", scene4, false);
	auto level3 = std::make_shared<dae::GameObject>();
	level3->AddComponent(std::make_shared<dae::LevelChanger>(3, 0));
	scene4.Add(level3);



	r = dae::LevelParser::ParseOBJ("../Data/Level/Level01.txt", scene5, true);

	auto levelcoop = std::make_shared<dae::GameObject>();
	levelcoop->AddComponent(std::make_shared<dae::LevelChanger>(4, 5));
	scene5.Add(levelcoop);


	r = dae::LevelParser::ParseOBJ("../Data/Level/Level02.txt", scene6, true);
	auto level2coop = std::make_shared<dae::GameObject>();
	level2coop->AddComponent(std::make_shared<dae::LevelChanger>(5, 6));
	scene6.Add(level2coop);


	r = dae::LevelParser::ParseOBJ("../Data/Level/Level03.txt", scene7, true);
	auto level3coop = std::make_shared<dae::GameObject>();
	level3coop->AddComponent(std::make_shared<dae::LevelChanger>(6, 0));
	scene7.Add(level3coop);


	CreateMenu(scene);





}








