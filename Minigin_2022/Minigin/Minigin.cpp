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
	backGround->AddComponent(std::make_shared<TransformComponent>());
	backGround->AddComponent(std::make_shared<RenderComponent>("background.jpg"));
	scene.Add(backGround);

	auto logo = std::make_shared<GameObject>();
	logo = std::make_shared<GameObject>();
	logo->AddComponent(std::make_shared<TransformComponent>(glm::vec3{ 216, 180, 0 }));
	logo->AddComponent(std::make_shared<RenderComponent>("logo.png"));
	scene.Add(logo);

	auto text = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	text = std::make_shared<GameObject>();
	text->AddComponent(std::make_shared<TransformComponent>(glm::vec3{ 80, 20, 0 }));
	text->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	scene.Add(text);


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

		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();

		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			Time::SetDeltaTime(deltaTime);
			

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
			lastTime = currentTime;
		}
	}

	Cleanup();
}
