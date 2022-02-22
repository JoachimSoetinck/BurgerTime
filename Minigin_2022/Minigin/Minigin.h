#pragma once
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		void FixedUpdate(float fixedTimeStep);

	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		float m_FixedTimeStep = 0.02f;
		SDL_Window* m_Window{};
	};
}