#include "GameActorCommand.h"
#include "GameObject.h"

GameActorCommand::GameActorCommand(dae::GameObject* actor) :
	m_pActor(actor)
{
}

GameActorCommand::~GameActorCommand()
{
}

MoveCommand::MoveCommand(dae::GameObject* actor, float moveX, float moveY) :
	GameActorCommand(actor),
	m_MoveX(moveX),
	m_MoveY(moveY)
{	
}
