#pragma once
#include "Command.h"
//#include "GameObject.h"
namespace dae
{
	class GameObject;
}

class GameActorCommand : public Command
{
	dae::GameObject* m_pActor;
protected:
	dae::GameObject* GetActor() const { return m_pActor; }
public:
	GameActorCommand(dae::GameObject* actor);
	virtual ~GameActorCommand();
	virtual void Execute() = 0;
	//virtual void Undo() = 0;
};

class MoveCommand final : public GameActorCommand
{
public:
	MoveCommand(dae::GameObject* actor, float moveX, float moveY);
	float m_MoveX;
	float m_MoveY;
};
