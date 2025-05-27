#pragma once
#include "Singleton.h"
#include "Command.h"
#include <map>
#include <memory>
#include <vector>
#include "Action.h"

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
		void BindCommand(KeyState stateOfButton,SDL_Scancode key,std::unique_ptr<Command> command);
		void UnbindCommand(KeyState stateOfButton, SDL_Scancode key);
		std::vector<Uint8> GetPrevState() const { return m_PrevState; }
		glm::vec2 GetActionValue(int actionName) const
		{
			auto it = m_Actions.find(actionName);
			if (it != m_Actions.end())
			{
				return it->second->GetActionValue();
			}
			assert(false && "Action not found");//ik wil nie dat dit stilletjes fout loopt
			return glm::vec2{ 0,0 };
		}
	private:
		std::vector<Uint8> m_PrevState;
		std::map<std::tuple<KeyState, SDL_Scancode>, std::unique_ptr<Command>> m_Commands;
		std::map<int, std::unique_ptr<Action>> m_Actions;
	};

}
