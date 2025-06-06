#include "StateMachine.h"
#include "PlayerStateComponent.h"
#include "InputManager.h"
#include "SDL.h"
#include <iostream>

namespace dae
{
	std::shared_ptr<StandingState> PlayerStateMachine::standing = std::make_shared<StandingState>();
	std::shared_ptr<RunningState> PlayerStateMachine::running = std::make_shared<RunningState>();
	std::shared_ptr<PushingState> PlayerStateMachine::pushing = std::make_shared<PushingState>();
	std::shared_ptr<DyingState> PlayerStateMachine::dying = std::make_shared<DyingState>();

	PlayerStateMachine::PlayerStateMachine()
	{
	}
	//standing state
	std::shared_ptr<PlayerStateMachine> StandingState::HandleInput()
	{
	if (m_MoveDir.x != 0 || m_MoveDir.y != 0)
	{
		m_MoveDir = glm::vec2{ 0,0 };
		std::cout << "Turned to running\n";
		return PlayerStateMachine::running;
	}

		return nullptr;
	}

	void StandingState::Update()
	{
		// idle sprite staat gwn stil
	}
	
	void StandingState::OnEnter()
	{
		// 'idle sprite' is gwn de laatste pose die door de running state gepakt was, dus die gwn inladen
		// (of de eerste aan de start vh spel (moet ik dan iets passen naar de OnEnter? surely not...))
		// overweeg om de standing state te mergen met de running state met direction vector (0,0)
	}
	void StandingState::OnExit()
	{
		// idle sprite unloaden
	}

	//running state
	std::shared_ptr<PlayerStateMachine> RunningState::HandleInput()
	{
		// if colliding with enemy (best te checken adhv event idpv collision check), dying state
		if (m_MoveDir == glm::vec2{ 0,0 })
		{
			std::cout << "Turned to standing\n";
			return PlayerStateMachine::standing;
		}
		m_MoveDir = glm::vec2{ 0,0 };
		return nullptr;
	}

	void RunningState::Update()
	{
		// functionaliteit zit nog steeds in de commands
		// loop gwn de running sprite afhankelijk van direction
	}
	void RunningState::OnEnter()
	{
		// weeral inloaden... tzelfde voor de rest
	}
	void RunningState::OnExit()
	{
	}

	//pushing state
	std::shared_ptr<PlayerStateMachine> PushingState::HandleInput()
	{
		return nullptr;
	}

	void PushingState::Update()
	{
		// meet hier wanneer de push gedaan is, om dan in de handle input te checken of et naar running of idle moet gaan
		//(duidt er ook op dak ben vergeten deltatime in de update te passen...)
	}
	void PushingState::OnEnter()
	{
	}
	void PushingState::OnExit()
	{
	}

	//dying state
	std::shared_ptr<PlayerStateMachine> DyingState::HandleInput()
	{

		return nullptr;
	}

	void DyingState::Update()
	{

	}
	void DyingState::OnEnter()
	{
	}
	void DyingState::OnExit()
	{
		// deleten van de player naar hier verplaatsen zodat het nog de death animation kan vervolledigen?
		// beter gezegd, semi resetten van de game
	}
}
