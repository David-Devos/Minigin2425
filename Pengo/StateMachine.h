#pragma once
#include <memory>
#include <glm.hpp>
namespace dae
{
	class PlayerStateComponent;

	class StandingState;
	class RunningState;
	class PushingState;
	class DyingState;
	class PlayerStateMachine;

	class BaseStateMachine
	{
	public:
		BaseStateMachine() = default;
		~BaseStateMachine() = default;
		BaseStateMachine(const BaseStateMachine& other) = default;
		BaseStateMachine(BaseStateMachine&& other) = default;
		BaseStateMachine& operator=(const BaseStateMachine& other) = default;
		BaseStateMachine& operator=(BaseStateMachine&& other) = default;
		// geen handle input, want dat is playerstate uniek
		virtual void Update() = 0;
	};

	class PlayerStateMachine : public BaseStateMachine
	{
	public:
		PlayerStateMachine();

		static std::shared_ptr<StandingState> standing;
		static std::shared_ptr<RunningState> running;
		static std::shared_ptr<PushingState> pushing;
		static std::shared_ptr<DyingState> dying;
		virtual void Update() override {};
		virtual void OnEnter() {};
		virtual void OnExit() {};
		virtual std::shared_ptr<PlayerStateMachine> HandleInput() = 0;
		virtual void AddMoveDir(const glm::vec2& moveDir) { m_MoveDir += moveDir; }
	protected:
		glm::vec2 m_MoveDir{ 0.f, 0.f };
		// std::unique_ptr<PlayerStateComponent> m_pPlayer;
		// verwijzing naar controllable component
	};


	class StandingState final : public PlayerStateMachine
	{
	public:
		std::shared_ptr<PlayerStateMachine> HandleInput() override;
		void Update();
		void OnEnter() override;
		void OnExit() override;
	};

	class RunningState final : public PlayerStateMachine
	{
	public:


		std::shared_ptr<PlayerStateMachine> HandleInput() override;
		void Update();
		void OnEnter() override;
		void OnExit() override;
	};

	class PushingState final : public PlayerStateMachine
	{
	public:


		std::shared_ptr<PlayerStateMachine> HandleInput() override;
		void Update();
		void OnEnter() override;
		void OnExit() override;
	};

	class DyingState final : public PlayerStateMachine
	{
	public:

		std::shared_ptr<PlayerStateMachine> HandleInput() override;
		void Update();
		void OnEnter() override;
		void OnExit() override;
	};
}
