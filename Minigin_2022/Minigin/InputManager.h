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

	struct CommandWithActor
	{
		std::shared_ptr<dae::GameObject> actor{};
		Command* command{};
		int playerController = 0;
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

		void AddCommand(ControllerButton button, Command* command, std::shared_ptr<dae::GameObject> object, int playerController = 0);
		void RemoveCommand(ControllerButton button);
		void Update();
	private:
		XINPUT_STATE m_CurrentState{};

		std::map< CommandWithActor*, ControllerButton> m_pCommands;
	};

}
