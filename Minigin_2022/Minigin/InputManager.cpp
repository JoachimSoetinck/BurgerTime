#include "MiniginPCH.h"
#include "InputManager.h"

#include "Scene.h"
#include "SceneManager.h"
#include "backends/imgui_impl_sdl.h"

class dae::InputManager::ControllerImpl
{
	XINPUT_STATE currentState{ };
	XINPUT_STATE previousState{ };
	bool m_ConnectedController[XUSER_MAX_COUNT];

	XINPUT_STATE m_CurrentInputStates[XUSER_MAX_COUNT]{};
	XINPUT_STATE m_PreviousInputStates[XUSER_MAX_COUNT]{};

	WORD m_buttonPressedThisFrame;
	WORD m_buttonReleasedThisFrame;

public:
	ControllerImpl()
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	};


	void ProcessInput()
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		for (int i = 0; i < XUSER_MAX_COUNT; i++)
		{
			// Set Previous State
			m_PreviousInputStates[i] = m_CurrentInputStates[i];
			// Zeroise the state
			ZeroMemory(&m_CurrentInputStates[i], sizeof(XINPUT_STATE));
			//Input State Result
			DWORD dwResult;
			// Get Current state
			dwResult = XInputGetState(i, &m_CurrentInputStates[i]);
			m_ConnectedController[i] = (dwResult == ERROR_SUCCESS); // Controller is connected

		}
	}

	int GetNrOfPlayers()
	{
		int total = 0;
		for (auto controller : m_ConnectedController)
		{
			if (controller)
				total++;
		}
		return  total;
	}

	bool IsPressed(ControllerButton button, int playerIndex)
	{
		if (!(m_ConnectedController[playerIndex] && static_cast<int>(button) >= 0)) return false;

		return (m_CurrentInputStates[playerIndex].Gamepad.wButtons & static_cast<int>(button)) != 0 && (m_PreviousInputStates[playerIndex].Gamepad.wButtons & static_cast<int>(button)) == 0;
	}

	bool IsUp(ControllerButton button, int playerIndex) const
	{

		if (!(m_ConnectedController[playerIndex] && static_cast<int>(button) >= 0)) return false;

		return (m_CurrentInputStates[playerIndex].Gamepad.wButtons & static_cast<int>(button)) == 0 && (m_PreviousInputStates[playerIndex].Gamepad.wButtons & static_cast<int>(button)) != 0;
	}

	bool IsDown(ControllerButton button, int playerIndex) const
	{
		if (!(m_ConnectedController[playerIndex] && static_cast<int>(button) >= 0)) return false;

		return (m_CurrentInputStates[playerIndex].Gamepad.wButtons & static_cast<int>(button)) != 0 && (m_PreviousInputStates[playerIndex].Gamepad.wButtons & static_cast<int>(button)) != 0;
	}


};

dae::InputManager::InputManager()
{
	pImpl = new ControllerImpl();

	m_pKeys = new int();
	m_pCurrentState = SDL_GetKeyboardState(m_pKeys);
	m_pPreviousState = new UINT8[*m_pKeys];
}

dae::InputManager::~InputManager()
{
	for (auto pair : m_pCommands)
	{
		if (pair.first != nullptr)
		{
			delete pair.first->command;
			delete pair.first;
		}
	}

	for (auto pair : m_KeyboardCommandss)
	{
		if (pair.first != nullptr)
		{
			delete pair.first->command;
			delete pair.first;
		}
	}

	delete pImpl;
	pImpl = nullptr;

	delete m_pPreviousState;
	m_pPreviousState = nullptr;

	delete m_pKeys;
	m_pKeys = nullptr;
}

bool dae::InputManager::ProcessInput()
{

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		if (e.type == SDL_KEYUP) {
			{
				if (e.key.keysym.sym == SDLK_1) {
					SceneManager::GetInstance().SetActiveScene(SceneManager::GetInstance().GetScene(1).get());
				}

				if (e.key.keysym.sym == SDLK_2) {
					SceneManager::GetInstance().SetActiveScene(SceneManager::GetInstance().GetScene(5).get());
				}


			}
		}
	}
	pImpl->ProcessInput();

	Update();

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button, int player) const
{
	// todo: return whether the given button is pressed or not.
	return pImpl->IsPressed(button, player);
}

bool dae::InputManager::IsUp(ControllerButton button, int player) const
{
	return pImpl->IsUp(button, player);
}

bool dae::InputManager::IsDown(ControllerButton button, int player) const
{
	return pImpl->IsDown(button, player);
}

bool dae::InputManager::IsPressed(unsigned int key)const
{
	if (m_pCurrentState[key])
	{
		return true;
	}

	return false;
}

bool dae::InputManager::IsDown(unsigned int key)const
{

	if (m_pCurrentState[key] && !m_pPreviousState[key])
	{
		return true;
	}
	return false;
}

bool dae::InputManager::IsUp(unsigned int key)const
{
	if (m_pCurrentState[key] && !m_pPreviousState[key])
	{
		return true;
	}
	return false;
}

void dae::InputManager::AddCommand(ControllerButton button, Command* command, std::shared_ptr<dae::GameObject>  actor, int playerController, ButtonPressType type)
{
	CommandWithActor* command_with_actor = new CommandWithActor();
	command_with_actor->actor = actor;
	command_with_actor->command = command;
	command_with_actor->playerController = playerController;
	command_with_actor->type = type;

	m_pCommands.insert({ command_with_actor, button });
}

void dae::InputManager::AddCommand(KeyboardButton button, Command* command, std::shared_ptr<dae::GameObject> object, ButtonPressType type)
{
	CommandWithActor* command_with_actor = new CommandWithActor();
	command_with_actor->actor = object;
	command_with_actor->command = command;
	command_with_actor->playerController = 0;
	command_with_actor->type = type;

	m_KeyboardCommandss.insert({ command_with_actor, button });
}

void dae::InputManager::RemoveCommand(ControllerButton)
{
}

void dae::InputManager::Update()
{
	std::memcpy(m_pPreviousState, m_pCurrentState, *m_pKeys);

	int players = pImpl->GetNrOfPlayers();
	for (int i = 0; i < players; ++i)
	{
		for (auto pair : m_pCommands)
		{
			switch (pair.first->type)
			{
			case ButtonPressType::IsPressed:
				if (pImpl->IsPressed(pair.second, i) && i == pair.first->playerController)
				{
					pair.first->command->Execute(pair.first->actor);
				}
				break;

			case ButtonPressType::IsDown:
				if (pImpl->IsDown(pair.second, i) && i == pair.first->playerController)
				{
					pair.first->command->Execute(pair.first->actor);
				}
				break;

			case ButtonPressType::IsUp:
				if (pImpl->IsUp(pair.second, i) && i == pair.first->playerController)
				{
					pair.first->command->Execute(pair.first->actor);
				}
				break;
			}

		}
	}

	ProcessInputKeyboard();


}

void dae::InputManager::ProcessInputKeyboard()
{
	for (auto pair : m_KeyboardCommandss)
	{
		switch (pair.first->type)
		{
		case ButtonPressType::IsPressed:
			if (IsPressed(static_cast<unsigned int>(pair.second)))
			{
				pair.first->command->Execute(pair.first->actor);
				break;
			}
			

		case ButtonPressType::IsDown:
			if (IsDown(static_cast<unsigned int>(pair.second)))
			{
				pair.first->command->Execute(pair.first->actor);
				break;
			}
		

		case ButtonPressType::IsUp:
			if (IsUp(static_cast<unsigned int>(pair.second)))
			{
				pair.first->command->Execute(pair.first->actor);
				break;
			}
		
		}

	}
}
