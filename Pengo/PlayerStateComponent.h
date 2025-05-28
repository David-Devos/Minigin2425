#pragma once
#include "Component.h"
namespace dae
{
	class StateMachine;
	class PlayerStateMachine;

	class PlayerStateComponent final : public Component
	{
	public:
		PlayerStateComponent(GameObject* gameObject, std::shared_ptr <PlayerStateMachine> startingState);
		void Update(float) override;
		void Render() const override {};
		void AddMoveDirection(const glm::vec2& moveDir);
	private:
		std::shared_ptr<PlayerStateMachine> m_CurrentState;
	};

}
