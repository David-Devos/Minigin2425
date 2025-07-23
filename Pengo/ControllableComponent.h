#pragma once
#include "Component.h"
#include "GridComponent.h"
namespace dae
{
	class ControllableComponent : public Component
	{
	public:
		ControllableComponent(dae::GameObject* gameObject, float movSpeed, GridType type, GridComponent* gridComp = nullptr);
		virtual ~ControllableComponent() = default;
		void Update(float deltaTime) override;
		void Render() const override {};
		void AddDirection(const glm::vec2& direction);
		bool IsMoving() const;
		void Interact();
		glm::vec2 GetLastDirection() const { return m_LastDirection; }

		ControllableComponent(const ControllableComponent& other) = delete;
		ControllableComponent(ControllableComponent&& other) = delete;
		ControllableComponent& operator=(const ControllableComponent& other) = delete;
		ControllableComponent& operator=(ControllableComponent&& other) = delete;

	private:
		glm::vec2 m_Direction = {};
		glm::vec2 m_LastDirection = {};
		glm::vec2 m_EstimatedEndPos = {};
		const float m_Speed = 180.0f;
		float m_TimeMoving = 0.0f;
		GridComponent* m_pGridComponent = nullptr;
		GridType m_Type;
	};
}

