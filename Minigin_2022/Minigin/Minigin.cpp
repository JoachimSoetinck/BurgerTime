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
	peterPepper->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 375, 535, 0 });


	auto healthText = std::make_shared<GameObject>();
	healthText->GetComponent<TransformComponent>()->SetPosition(150, 10, 0);
	auto lives = std::make_shared<LivesComponent>(healthText, SDL_Color{ 255,255,0 }, player);
	healthText->AddComponent(lives);

	scene.Add(healthText);

	player->AddObserver(lives);

	auto score = std::make_shared<ScoreComponent>(peterPepper, SDL_Color{ 255,255,0 });
	peterPepper->AddComponent(score);
	peterPepper->GetComponent<ScoreComponent>()->SetTextLocation(glm::vec3{ 20, 380, 0 });

	const auto peterPepperImage = std::make_shared<RenderComponent>("PeterPepper/PlayerIdle.png", peterPepper);
	peterPepper->AddComponent(peterPepperImage);

	scene.Add(peterPepper);

	InputManager::GetInstance().AddCommand(ControllerButton::ButtonA, new LoseLive(), peterPepper, 0);
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonB, new GivePointsCommand(), peterPepper, 0);

	InputManager::GetInstance().AddCommand(ControllerButton::ButtonRight, new MoveRight(), peterPepper, 0, ButtonPressType::IsDown);
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonRight, new StopMoving(), peterPepper, 0, ButtonPressType::IsUp);

	InputManager::GetInstance().AddCommand(ControllerButton::ButtonLeft, new MoveLeft(), peterPepper, 0, ButtonPressType::IsDown);
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonLeft, new StopMoving(), peterPepper, 0, ButtonPressType::IsUp);

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
	
	platform.get()->AddComponent(std::make_shared<RenderComponent>( texture, platform));
	platform.get()->AddComponent(std::make_unique<PlatformComponent>(platform));
	platform.get()->GetComponent<TransformComponent>()->SetPosition(x, y,0);
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

	CreateLadder(scene, 55, 90, "Ladder.png");
	CreateLadder(scene, 55, 145, "Ladder.png");
	CreateLadder(scene, 55, 310, "Ladder.png");
	CreateLadder(scene, 55, 365, "Ladder.png");
	CreateLadder(scene, 55, 420, "Ladder.png");
	CreateLadder(scene, 55, 475, "Ladder.png");
	CreateLadder(scene, 55, 530, "Ladder.png");
	CreateLadder(scene, 135, 200, "Ladder.png");
	CreateLadder(scene, 135, 255, "Ladder.png");
	CreateLadder(scene, 135, 310, "Ladder.png");
	CreateLadder(scene, 135, 365, "Ladder.png");
	CreateLadder(scene, 135, 420, "Ladder.png");
	CreateLadder(scene, 215, 90, "Ladder.png");
	CreateLadder(scene, 215, 145, "Ladder.png");
	CreateLadder(scene, 215, 200, "Ladder.png");
	CreateLadder(scene, 215, 255, "Ladder.png");
	CreateLadder(scene, 215, 310, "Ladder.png");
	CreateLadder(scene, 215, 365, "Ladder.png");
	CreateLadder(scene, 215, 420, "Ladder.png");
	CreateLadder(scene, 215, 475, "Ladder.png");
	CreateLadder(scene, 215, 530, "Ladder.png");
	CreateLadder(scene, 295, 90, "Ladder.png");
	CreateLadder(scene, 295, 145, "Ladder.png");
	CreateLadder(scene, 295, 200, "Ladder.png");
	CreateLadder(scene, 375, 90, "Ladder.png");
	CreateLadder(scene, 375, 145, "Ladder.png");
	CreateLadder(scene, 375, 200, "Ladder.png");
	CreateLadder(scene, 375, 255, "Ladder.png");
	CreateLadder(scene, 375, 310, "Ladder.png");
	CreateLadder(scene, 375, 365, "Ladder.png");
	CreateLadder(scene, 375, 420, "Ladder.png");
	CreateLadder(scene, 375, 475, "Ladder.png");
	CreateLadder(scene, 375, 530, "Ladder.png");
	CreateLadder(scene, 455, 200, "Ladder.png");
	CreateLadder(scene, 455, 255, "Ladder.png");
	CreateLadder(scene, 455, 310, "Ladder.png");
	CreateLadder(scene, 535, 90, "Ladder.png");
	CreateLadder(scene, 535, 145, "Ladder.png");
	CreateLadder(scene, 535, 200, "Ladder.png");
	CreateLadder(scene, 535, 255, "Ladder.png");
	CreateLadder(scene, 535, 310, "Ladder.png");
	CreateLadder(scene, 535, 365, "Ladder.png");
	CreateLadder(scene, 535, 420, "Ladder.png");
	CreateLadder(scene, 535, 475, "Ladder.png");
	CreateLadder(scene, 535, 530, "Ladder.png");
	CreateLadder(scene, 615, 310, "Ladder.png");
	CreateLadder(scene, 615, 365, "Ladder.png");
	CreateLadder(scene, 615, 420, "Ladder.png");
	CreateLadder(scene, 615, 475, "Ladder.png");
	CreateLadder(scene, 615, 530, "Ladder.png");
	CreateLadder(scene, 695, 90, "Ladder.png");
	CreateLadder(scene, 695, 145, "Ladder.png");
	CreateLadder(scene, 695, 200, "Ladder.png");
	CreateLadder(scene, 695, 255, "Ladder.png");
	CreateLadder(scene, 695, 420, "Ladder.png");
	CreateLadder(scene, 695, 475, "Ladder.png");
	CreateLadder(scene, 695, 530, "Ladder.png");

	CreatePlatform(scene, 55, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 90, "BluePlatform.png");
	CreatePlatform(scene, 135, 90, "BluePlatform.png");
	CreatePlatform(scene, 175, 90, "BluePlatform.png");
	CreatePlatform(scene, 215, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 90, "BluePlatform.png");
	CreatePlatform(scene, 295, 90, "BluePlatform.png");
	CreatePlatform(scene, 335, 90, "BluePlatform.png");
	CreatePlatform(scene, 375, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 90, "BluePlatform.png");
	CreatePlatform(scene, 455, 90, "BluePlatform.png");
	CreatePlatform(scene, 495, 90, "BluePlatform.png");
	CreatePlatform(scene, 535, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 90, "BluePlatform.png");
	CreatePlatform(scene, 615, 90, "BluePlatform.png");
	CreatePlatform(scene, 655, 90, "BluePlatform.png");
	CreatePlatform(scene, 695, 90, "LightBluePlatform.png");
	CreatePlatform(scene, 55, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 200, "BluePlatform.png");
	CreatePlatform(scene, 135, 200, "BluePlatform.png");
	CreatePlatform(scene, 175, 200, "BluePlatform.png");
	CreatePlatform(scene, 215, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 375, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 200, "BluePlatform.png");
	CreatePlatform(scene, 455, 200, "BluePlatform.png");
	CreatePlatform(scene, 495, 200, "BluePlatform.png");
	CreatePlatform(scene, 535, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 200, "BluePlatform.png");
	CreatePlatform(scene, 615, 200, "BluePlatform.png");
	CreatePlatform(scene, 655, 200, "BluePlatform.png");
	CreatePlatform(scene, 695, 200, "LightBluePlatform.png");
	CreatePlatform(scene, 215, 255, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 255, "BluePlatform.png");
	CreatePlatform(scene, 295, 255, "BluePlatform.png");
	CreatePlatform(scene, 335, 255, "BluePlatform.png");
	CreatePlatform(scene, 375, 255, "LightBluePlatform.png");
	CreatePlatform(scene, 55, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 310, "BluePlatform.png");
	CreatePlatform(scene, 135, 310, "BluePlatform.png");
	CreatePlatform(scene, 175, 310, "BluePlatform.png");
	CreatePlatform(scene, 215, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 535, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 310, "BluePlatform.png");
	CreatePlatform(scene, 615, 310, "BluePlatform.png");
	CreatePlatform(scene, 655, 310, "BluePlatform.png");
	CreatePlatform(scene, 695, 310, "LightBluePlatform.png");
	CreatePlatform(scene, 215, 365, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 365, "BluePlatform.png");
	CreatePlatform(scene, 295, 365, "BluePlatform.png");
	CreatePlatform(scene, 335, 365, "BluePlatform.png");
	CreatePlatform(scene, 375, 365, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 365, "BluePlatform.png");
	CreatePlatform(scene, 455, 365, "BluePlatform.png");
	CreatePlatform(scene, 495, 365, "BluePlatform.png");
	CreatePlatform(scene, 535, 365, "LightBluePlatform.png");
	CreatePlatform(scene, 535, 420, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 420, "BluePlatform.png");
	CreatePlatform(scene, 615, 420, "BluePlatform.png");
	CreatePlatform(scene, 655, 420, "BluePlatform.png");
	CreatePlatform(scene, 695, 420, "LightBluePlatform.png");
	CreatePlatform(scene, 55, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 475, "BluePlatform.png");
	CreatePlatform(scene, 135, 475, "BluePlatform.png");
	CreatePlatform(scene, 175, 475, "BluePlatform.png");
	CreatePlatform(scene, 215, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 475, "BluePlatform.png");
	CreatePlatform(scene, 295, 475, "BluePlatform.png");
	CreatePlatform(scene, 335, 475, "BluePlatform.png");
	CreatePlatform(scene, 375, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 475, "BluePlatform.png");
	CreatePlatform(scene, 455, 475, "BluePlatform.png");
	CreatePlatform(scene, 495, 475, "BluePlatform.png");
	CreatePlatform(scene, 535, 475, "LightBluePlatform.png");
	CreatePlatform(scene, 55, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 95, 585, "BluePlatform.png");
	CreatePlatform(scene, 135, 585, "BluePlatform.png");
	CreatePlatform(scene, 175, 585, "BluePlatform.png");
	CreatePlatform(scene, 215, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 255, 585, "BluePlatform.png");
	CreatePlatform(scene, 295, 585, "BluePlatform.png");
	CreatePlatform(scene, 335, 585, "BluePlatform.png");
	CreatePlatform(scene, 375, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 415, 585, "BluePlatform.png");
	CreatePlatform(scene, 455, 585, "BluePlatform.png");
	CreatePlatform(scene, 495, 585, "BluePlatform.png");
	CreatePlatform(scene, 535, 585, "LightBluePlatform.png");
	CreatePlatform(scene, 575, 585, "BluePlatform.png");
	CreatePlatform(scene, 615, 585, "BluePlatform.png");
	CreatePlatform(scene, 655, 585, "BluePlatform.png");
	CreatePlatform(scene, 695, 585, "LightBluePlatform.png");

}


