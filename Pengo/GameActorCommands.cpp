#include "GameActorCommands.h"
#include "HealthComponent.h"
#include "PelletEatComponent.h"
#include "ControllableComponent.h"

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

DamageCommand::DamageCommand(dae::GameObject* actor) :
	GameActorCommand(actor)
{
	m_pActor = actor;
}

void DamageCommand::Execute()
{
	if (m_pActor->HasComponent<dae::HealthComponent>())
		m_pActor->GetComponent<dae::HealthComponent>()->TakeDamage(1);
}

PelletEatCommand::PelletEatCommand(dae::GameObject* actor)
	: GameActorCommand(actor)
{
	m_pActor = actor;
}
void PelletEatCommand::Execute()
{
	if (m_pActor->HasComponent<dae::PelletEatComponent>())
		m_pActor->GetComponent<dae::PelletEatComponent>()->EatPellet(1);
}
