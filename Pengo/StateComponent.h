#pragma once
#include "Component.h"
namespace dae
{
	class StateMachine;
	class PlayerStateMachine;

	class StateComponent final : public Component
	{
	public:
		StateComponent(GameObject* gameObject);
		void Update(float) override;
		void Render() const override {};
		void SetState(std::shared_ptr<PlayerStateMachine> stateMachine);
	private:
		std::shared_ptr<PlayerStateMachine> m_CurrentState;
	};

}
