#include "PlayerStateComponent.h"
#include "StateMachine.h"
namespace dae
{
	PlayerStateComponent::PlayerStateComponent(GameObject* gameObject, std::shared_ptr<PlayerStateMachine> startingState)
		:Component(gameObject),
		m_CurrentState(std::move(startingState))
	{
	}
	void PlayerStateComponent::Update(float)
	{
		if (m_CurrentState == nullptr)
			return;
		auto state = m_CurrentState->HandleInput();
		if (state != m_CurrentState && state != nullptr)
		{
			m_CurrentState = std::move(state);
		}
	}
	void PlayerStateComponent::AddMoveDirection(const glm::vec2& moveDir)
	{
		m_CurrentState->AddMoveDir(moveDir);
	}
}