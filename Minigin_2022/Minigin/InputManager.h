#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include <memory>

#include "Command.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,

		ButtonUp = 0x0001,
		ButtonDown = 0x0002,
		ButtonLeft = 0x0004,
		ButtonRight = 0x0008,
		ButtonStart = 0x0010,
		ButtonBack = 0x0020,
		ButtonLTrigger = 0x0100,
		ButtonRTrigger = 0x0200,
		ButtonLStick = 0x0040,
		ButtonRStick = 0x0080,

	};

	enum class KeyboardButton
	{
		A = SDL_SCANCODE_A,
		Z = SDL_SCANCODE_Z,
		E = SDL_SCANCODE_E,
		R = SDL_SCANCODE_R,
		T = SDL_SCANCODE_T,
		Y = SDL_SCANCODE_Y,
		U = SDL_SCANCODE_U,
		I = SDL_SCANCODE_I,
		O = SDL_SCANCODE_O,
		P = SDL_SCANCODE_P,
		Q = SDL_SCANCODE_Q,
		S = SDL_SCANCODE_S,
		D = SDL_SCANCODE_D,
		F = SDL_SCANCODE_F,
		G = SDL_SCANCODE_G,
		H = SDL_SCANCODE_H,
		J = SDL_SCANCODE_J,
		K = SDL_SCANCODE_K,
		L = SDL_SCANCODE_L,
		M = SDL_SCANCODE_M,
		W = SDL_SCANCODE_W,
		X = SDL_SCANCODE_X,
		C = SDL_SCANCODE_C,
		V = SDL_SCANCODE_V,
		B = SDL_SCANCODE_B,
		N = SDL_SCANCODE_N,
		SPACE = SDL_SCANCODE_SPACE,
		LEFTCONTROL = SDL_SCANCODE_LCTRL,
		RIGHTCONTROL = SDL_SCANCODE_RCTRL,
		LEFTSHIFT = SDL_SCANCODE_LSHIFT,
		RIGHTSHIFT = SDL_SCANCODE_RSHIFT,
		ESCAPE = SDL_SCANCODE_ESCAPE,
		DEL = SDL_SCANCODE_DELETE,
		F1 = SDL_SCANCODE_F1,
		F2 = SDL_SCANCODE_F2,
		F3 = SDL_SCANCODE_F3,
		F4 = SDL_SCANCODE_F4,
		F5 = SDL_SCANCODE_F5,
		F6 = SDL_SCANCODE_F6,
		F7 = SDL_SCANCODE_F7,
		F8 = SDL_SCANCODE_F8,
		F9 = SDL_SCANCODE_F9,
		F10 = SDL_SCANCODE_F10,
		F11 = SDL_SCANCODE_F11,
		F12 = SDL_SCANCODE_F12,
		LEFTARROW = SDL_SCANCODE_LEFT,
		RIGHTARROW = SDL_SCANCODE_RIGHT,
		UPARROW = SDL_SCANCODE_UP,
		DOWNARROW = SDL_SCANCODE_DOWN



	};

	enum class ButtonPressType
	{
		IsDown, IsPressed, IsUp
	};
	struct CommandWithActor
	{
		std::shared_ptr<dae::GameObject> actor{};
		Command* command{};
		int playerController = 0;
		ButtonPressType type = ButtonPressType::IsPressed;
	};




	class InputManager final : public Singleton<InputManager>
	{
		class ControllerImpl;
		ControllerImpl* pImpl;

	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		bool IsPressed(ControllerButton button, int playerIndex) const;
		bool IsUp(ControllerButton button, int playerIndex) const;
		bool IsDown(ControllerButton button, int playerIndex) const;

		bool IsPressed(unsigned int key) const;
		bool IsDownThisFrame(unsigned int key)const;
		bool IsUpThisFrame(unsigned int key)const;

		void AddCommand(ControllerButton button, Command* command, std::shared_ptr<dae::GameObject> object, int playerController = 0, ButtonPressType type = ButtonPressType::IsPressed);
		void AddCommand(KeyboardButton button, Command* command, std::shared_ptr<dae::GameObject> object, ButtonPressType type = ButtonPressType::IsPressed);
		void RemoveCommand(ControllerButton button);
		void Update();
	private:

		int* m_pKeys{};
		const Uint8* m_pCurrentState{};
		Uint8* m_pPreviousState{};

		void ProcessInputKeyboard();

		std::map< CommandWithActor*, ControllerButton> m_pCommands;
		std::map<CommandWithActor*, KeyboardButton> m_KeyboardCommandss{};

	};

}
