#include "MiniginPCH.h"
#include "Minigin.h"
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
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");


	auto backGround = std::make_shared<GameObject>();
	backGround = std::make_shared<GameObject>();
	backGround->AddComponent(std::make_shared<RenderComponent>("background.jpg", backGround));
	scene.Add(backGround);

	auto logo = std::make_shared<GameObject>();
	logo = std::make_shared<GameObject>();
	logo->GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 216, 180, 0 });
	logo->AddComponent(std::make_shared<RenderComponent>("logo.png", logo));
	scene.Add(logo);

	auto text = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	text = std::make_shared<GameObject>();
	text-> GetComponent<TransformComponent>()->SetPosition(glm::vec3{ 80, 20, 0 });
	text->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font, text));
	scene.Add(text);


	auto fpsObject = std::make_shared<GameObject>();
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	fpsObject->AddComponent(std::make_shared<TextComponent>("0 fps", fpsFont, SDL_Color{ 255, 255, 0 }, fpsObject));
	fpsObject->AddComponent(std::make_shared<FPSComponent>(fpsObject));
	
	scene.Add(fpsObject);
}


void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
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
			const auto sleepTime = currentTime + std::chrono::milliseconds(MsPerFrame/1000) - std::chrono::high_resolution_clock::now();
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
