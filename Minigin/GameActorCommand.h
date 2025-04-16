#pragma once
#include "Command.h"
//#include "GameObject.h"
namespace dae
{
	class GameObject;
}

class GameActorCommand : public Command
{
protected:
	dae::GameObject* m_pActor;
	dae::GameObject* GetActor() const { return m_pActor; }
public:
	GameActorCommand(dae::GameObject* actor);
	virtual ~GameActorCommand();
	virtual void Execute() = 0;
	//virtual void Undo() = 0;
};
