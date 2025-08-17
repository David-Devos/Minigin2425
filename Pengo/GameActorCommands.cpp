#include "GameActorCommands.h"
#include "HealthComponent.h"
#include "PelletEatComponent.h"
#include "ControllableComponent.h"
#include <ServiceLocator.h>
#include "PlayerStateComponent.h"
#include <iostream>
#include "PushableComponent.h"
#include "CollisionComponent.h"
#include "WaterWallComponent.h"

MoveCommand::MoveCommand(dae::GameObject* actor, glm::vec2 moveDir) :
	GameActorCommand(actor),
	m_MoveDir(moveDir)
{
}

void MoveCommand::Execute()
{
	if (m_pActor->HasComponent<dae::ControllableComponent>())
	{
		auto temp = m_pActor->GetComponent<dae::ControllableComponent>();
		if (!temp->IsMoving())// zodat ik niet mid moving mn direction kan switchen
		{
			temp->AddDirection(glm::vec2{ m_MoveDir.x, m_MoveDir.y });
			if (m_pActor->HasComponent<dae::PlayerStateComponent>()) // abstraheer tot basestatecomponent, sinds sno bees en blokken ook movement nodig zullen hebben
				m_pActor->GetComponent<dae::PlayerStateComponent>()->AddMoveDirection(glm::vec2{ m_MoveDir.x, m_MoveDir.y });
		}
	}
}

PushCommand::PushCommand(dae::GameObject* actor) :
	GameActorCommand(actor)
{
}
void PushCommand::Execute()
{
	auto temp = m_pActor->GetComponent<dae::ControllableComponent>();
	temp->Interact();

}
SplashedCommand::SplashedCommand(dae::GameObject* actor) :
	GameActorCommand(actor)
{
}
void SplashedCommand::Execute()
{
	// render comp
	auto ww = m_pActor->GetComponent<dae::WaterWallComponent>();
	ww->ActivateWall();
	std::cout << "Splashed!" << std::endl;
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

