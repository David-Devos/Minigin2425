#pragma once
#include "Singleton.h"
#include "Command.h"
#include <map>
#include <memory>
#include <vector>
#include <SDL.h>

namespace dae
{
	enum class KeyState
	{
		Down,
		Up,
		Tapped,
		Released
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput();
		void BindCommand(KeyState controllerButton,SDL_Scancode key,std::unique_ptr<Command> command);
		void UnbindCommand(KeyState controllerButton, SDL_Scancode key);
		std::vector<Uint8> GetPrevState() const { return m_PrevState; }
	private:
		std::vector<Uint8> m_PrevState;
		std::map<std::tuple<KeyState, SDL_Scancode>, std::unique_ptr<Command>> m_Commands;
	};

}
