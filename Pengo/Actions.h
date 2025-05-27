#pragma once
#include "Action.h"
#include <vector>

enum class ActionName
{
	move
	//voor mochten er meer nodig zijn (nogmaals, ik wil niet de move action hardcoden in de inputmanager)
};

class MoveAction final : public Action
{
private:
	ActionName m_Name = ActionName::move;
	glm::vec2 m_MoveDir;
public:
	MoveAction(std::vector<SDL_Scancode> actionInputs)
	{
		m_ActionInputs = actionInputs;
	}
	int GetName() const override { return int(m_Name); }
	glm::vec2 GetActionValue() const override
	{
		// Hier zou ik dan de SDL_Scancodes overlopen zoals ik momenteel nog doe in StateMachine.cpp...
		// Het voelt voornamelijk aan alsof ik het probleem aan het verplaatsen ben idpv op te lossen.
		// (maw, ik ben fout bezig, toch?)
		return m_MoveDir;
	}
};