#include "GameActorCommands.h"
#include "HealthComponent.h"
#include "PelletEatComponent.h"
#include "ControllableComponent.h"
#include <ServiceLocator.h>

MoveCommand::MoveCommand(dae::GameObject* actor, glm::vec2 moveDir) :
	GameActorCommand(actor),
	m_MoveDir(moveDir)
{
}

void MoveCommand::Execute()
{
	if (m_pActor->HasComponent<dae::ControllableComponent>())
		m_pActor->GetComponent<dae::ControllableComponent>()->AddDirection(glm::vec3{ m_MoveDir.x, m_MoveDir.y,0 });
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

TempSoundCommand::TempSoundCommand(dae::GameObject* actor)
	: GameActorCommand(actor)
{
	m_pActor = actor;
}

void TempSoundCommand::Execute()
{
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.playSound(0, 10);
}
