#include "GameActorCommand.h"
#include "GameObject.h"

GameActorCommand::GameActorCommand(dae::GameObject* actor) :
	m_pActor(actor)
{
}

GameActorCommand::~GameActorCommand()
{
}
