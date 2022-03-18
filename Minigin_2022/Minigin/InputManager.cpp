#include "MiniginPCH.h"
#include "InputManager.h"

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
}

dae::InputManager::~InputManager()
{
	for (auto pair : m_pCommands)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
		}
	}

	delete pImpl;
	pImpl = nullptr;
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

void dae::InputManager::AddCommand(ControllerButton button, Command* command)
{
	m_pCommands.insert({ button, command });
}

void dae::InputManager::RemoveCommand(ControllerButton)
{
}

void dae::InputManager::Update()
{
	int players = pImpl->GetNrOfPlayers();
	for (int i = 0; i < players; ++i)
	{
		for (auto pair : m_pCommands)
		{
			if (IsPressed(pair.first, i))
			{
				pair.second->Execute();
			}
		}
	}

}

