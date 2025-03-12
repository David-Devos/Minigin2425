#pragma once
#include "Singleton.h"
#include "Command.h"
#include <map>
#include <memory>

namespace dae
{
	enum class KeyState
	{
		Down,
		Up
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void BindCommand(KeyState controllerButton,SDL_Scancode key,std::unique_ptr<Command> command);
		void UnbindCommand(KeyState controllerButton, SDL_Scancode key);
	private:
		std::map<std::tuple<KeyState, SDL_Scancode>, std::unique_ptr<Command>> m_Commands;
	};

}
