#pragma once
#include "Component.h"
namespace dae
{
	class ControllableComponent : public Component
	{
	public:
		ControllableComponent(dae::GameObject* gameObject, float movSpeed);
		virtual ~ControllableComponent() = default;
		void Update(float deltaTime) override;
		void Render() const override {};
		void AddDirection(const glm::vec2& direction) { m_Direction += direction; }

		ControllableComponent(const ControllableComponent& other) = delete;
		ControllableComponent(ControllableComponent&& other) = delete;
		ControllableComponent& operator=(const ControllableComponent& other) = delete;
		ControllableComponent& operator=(ControllableComponent&& other) = delete;

	private:
		glm::vec2 m_Direction = {};
		const float m_Speed = 180.0f;
	};
}

