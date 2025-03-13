#include "GameActorCommand.h"
#include "GameObject.h"
#include "ControllableComponent.h"

GameActorCommand::GameActorCommand(dae::GameObject* actor) :
	m_pActor(actor)
{
}

GameActorCommand::~GameActorCommand()
{
}

MoveCommand::MoveCommand(dae::GameObject* actor, int moveRight, int moveDown) :
	GameActorCommand(actor),
	m_MoveRight(moveRight),
	m_MoveDown(moveDown)
{	
}

void MoveCommand::Execute()
{
	if (m_pActor->HasComponent<dae::ControllableComponent>())
		m_pActor->GetComponent<dae::ControllableComponent>()->AddDirection(glm::vec3{ m_MoveRight, m_MoveDown,0 });
}
