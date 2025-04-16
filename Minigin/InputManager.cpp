
#include <algorithm> 
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>
#include <iostream>

dae::InputManager::InputManager() {
	m_PrevState.resize(SDL_NUM_SCANCODES);
}
bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// ImGui schtuff
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (auto& command : m_Commands)
	{
		bool wasPressed = false;
		wasPressed = m_PrevState[std::get<1>(command.first)];
		bool isPressed = state[std::get<1>(command.first)];
		switch (std::get<0>(command.first))
		{
		case KeyState::Down:
			if (isPressed)
			{
				command.second->Execute();

			}
			break;
		case KeyState::Up:
			if (!isPressed)
				command.second->Execute();
			break;
		case KeyState::Tapped:
			if (!wasPressed && isPressed)
				command.second->Execute();
			break;
		case KeyState::Released:
			if (wasPressed && !isPressed)
				command.second->Execute();
			break;
		}
	}
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_PrevState[i] = state[i];
	}

	return true;
}

void dae::InputManager::BindCommand(KeyState controllerButton, SDL_Scancode key, std::unique_ptr<Command> command)
{
	m_Commands[std::make_tuple(controllerButton, key)] = std::move(command);
}

void dae::InputManager::UnbindCommand(KeyState controllerButton, SDL_Scancode key)
{
	m_Commands.erase(std::make_tuple(controllerButton, key));
}
