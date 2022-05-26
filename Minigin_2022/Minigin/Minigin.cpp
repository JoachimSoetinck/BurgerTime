#include "MiniginPCH.h"
#include "Minigin.h"

#include <SDL_mixer.h>
#include <thread>


#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "PeterPepperComponent.h"
#include "Command.h"
#include "LadderComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "Observer.h"
#include "PlatformComponent.h"
#include "RigidBodyComponent.h"
#include "ServiceLocator.h"
#include "Sound.h"


using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		750,
		750,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	ServiceLocator::RegisterSoundSystem(new SoundSystem());
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");


	auto backGround = std::make_shared<GameObject>();

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	CreateLevel(scene);



	auto fpsObject = std::make_shared<GameObject>();
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	fpsObject->AddComponent(std::make_shared<TextComponent>("0 fps", fpsFont, SDL_Color{ 255, 255, 0 }, fpsObject));
	fpsObject->AddComponent(std::make_shared<FPSComponent>(fpsObject));


	auto peterPepper = std::make_shared<GameObject>();
	auto player = std::make_shared<PeterPepperComponent>(peterPepper);
	peterPepper->AddComponent(player);
	peterPepper->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 375, 550, 0 });


	auto healthText = std::make_shared<GameObject>();
	healthText->GetComponent<TransformComponent>()->SetPosition(150, 10, 0);
	auto lives = std::make_shared<LivesComponent>(healthText, SDL_Color{ 255,255,0 }, player);
	healthText->AddComponent(lives);

	scene.Add(healthText);

	player->AddObserver(lives);

	auto scoreText = std::make_shared<GameObject>();
	scoreText->GetComponent<TransformComponent>()->SetPosition(250, 10, 0);
	auto score = std::make_shared<ScoreComponent>(peterPepper, SDL_Color{ 255,255,0 }, peterPepper);
	scoreText->AddComponent(score);
	scoreText->GetComponent<ScoreComponent>()->SetTextLocation(glm::vec3{ 250, 10, 00 });
	scene.Add(scoreText);

	player->AddObserver(score);

	const auto peterPepperImage = std::make_shared<RenderComponent>("PeterPepper/PlayerIdle.png", peterPepper);
	peterPepper->AddComponent(peterPepperImage);

	scene.Add(peterPepper);


	InputManager::GetInstance().AddCommand(ControllerButton::ButtonY, new PlaySound(), peterPepper, 0, ButtonPressType::IsUp);



	scene.Add(fpsObject);
}



void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::RegisterSoundSystem(nullptr);
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;

		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			Time::GetInstance().SetDeltaTime(deltaTime);

			lag += deltaTime;
			lastTime = currentTime;

			doContinue = input.ProcessInput();


			while (lag >= m_FixedTimeStep)
			{
				sceneManager.FixedUpdate(m_FixedTimeStep);
				lag -= m_FixedTimeStep;
			}

			sceneManager.Update();
			renderer.Render();

			//cap fps
			const auto sleepTime = currentTime + std::chrono::milliseconds(MsPerFrame / 1000) - std::chrono::high_resolution_clock::now();
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void dae::Minigin::CreatePlatform(Scene& scene, float x, float y, std::string texture) const
{

	auto platform = std::make_shared<GameObject>();

	platform.get()->AddComponent(std::make_shared<RenderComponent>(texture, platform));
	platform.get()->AddComponent(std::make_unique<PlatformComponent>(platform));
	platform.get()->GetComponent<TransformComponent>()->SetPosition(x, y, 0);
	scene.Add(platform);
}

void dae::Minigin::CreateLadder(Scene& scene, float x, float y, std::string texture) const
{
	auto ladder = std::make_shared<GameObject>();

	ladder.get()->AddComponent(std::make_shared<RenderComponent>(texture, ladder));
	ladder.get()->AddComponent(std::make_unique<LadderComponent>(ladder));
	ladder.get()->GetComponent<TransformComponent>()->SetPosition(x, y, 0);
	scene.Add(ladder);
}

void dae::Minigin::CreateLevel(Scene& scene) const
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



	CreateIngredient(scene, 93, 85, IngredientComponent::Type::TopBun);
	CreateIngredient(scene, 93, 190, IngredientComponent::Type::Lettuce);
	CreateIngredient(scene, 93, 300, IngredientComponent::Type::Patty);
	CreateIngredient(scene, 93, 470, IngredientComponent::Type::Patty);
	CreateIngredient(scene, 93, 575, IngredientComponent::Type::BottomBun);

	CreateIngredient(scene, 255, 85, IngredientComponent::Type::TopBun);
	CreateIngredient(scene, 255, 245, IngredientComponent::Type::Lettuce);
	CreateIngredient(scene, 255, 355, IngredientComponent::Type::Patty);
	CreateIngredient(scene, 255, 470, IngredientComponent::Type::Patty);
	CreateIngredient(scene, 255, 575, IngredientComponent::Type::BottomBun);


	CreateIngredient(scene, 420, 85, IngredientComponent::Type::TopBun);
	CreateIngredient(scene, 420, 190, IngredientComponent::Type::Lettuce);
	CreateIngredient(scene, 420, 355, IngredientComponent::Type::Patty);
	CreateIngredient(scene, 420, 470, IngredientComponent::Type::Patty);
	CreateIngredient(scene, 420, 575, IngredientComponent::Type::BottomBun);

	CreateIngredient(scene, 580, 85, IngredientComponent::Type::TopBun);
	CreateIngredient(scene, 580, 190, IngredientComponent::Type::Lettuce);
	CreateIngredient(scene, 580, 300, IngredientComponent::Type::Patty);
	CreateIngredient(scene, 580, 410, IngredientComponent::Type::Patty);
	CreateIngredient(scene, 580, 575, IngredientComponent::Type::BottomBun);


}

void dae::Minigin::CreateIngredient(Scene& scene, float x, float y, IngredientComponent::Type ingredient) const
{
	auto ingredients = std::make_shared<GameObject>();

	ingredients.get()->AddComponent(std::make_shared<RenderComponent>("LightBluePlatform.png", ingredients));
	ingredients.get()->AddComponent(std::make_unique<IngredientComponent>(ingredients, ingredient));
	ingredients.get()->GetComponent<TransformComponent>()->SetPosition(x, y, 0);
	scene.Add(ingredients);
}


