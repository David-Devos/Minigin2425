#pragma once
#include <memory>
namespace dae
{
	class StateComponent;

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

		virtual std::shared_ptr<PlayerStateMachine> HandleInput() = 0;
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
	protected:
		std::unique_ptr<StateComponent> m_pPlayer;
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
