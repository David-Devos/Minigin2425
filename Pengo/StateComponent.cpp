#include "StateComponent.h"
#include "StateMachine.h"
namespace dae
{
	StateComponent::StateComponent(GameObject* gameObject) :Component(gameObject)
	{
	}
	void StateComponent::Update(float)
	{
		if (m_CurrentState == nullptr)
			return;
		auto state = m_CurrentState->HandleInput();
		if (state != m_CurrentState && state != nullptr)
		{
			m_CurrentState = std::move(state);
		}
	}
	void StateComponent::SetState(std::shared_ptr<PlayerStateMachine> stateMachine)
	{
		m_CurrentState = std::move(stateMachine);
	}
}