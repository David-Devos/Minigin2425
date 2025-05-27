#pragma once
#include <glm.hpp>
#include <SDL.h>
class Action
{
protected:
	std::vector<SDL_Scancode> m_ActionInputs;
public:
	virtual ~Action() = default;
	virtual int GetName() const = 0;
	virtual glm::vec2 GetActionValue() const
	{
		return glm::vec2{0,0};
	}
};
