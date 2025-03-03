#pragma once
#include "Component.h"

namespace dae
{
	class RotatorComponent : public dae::Component
	{
	public:
		RotatorComponent(dae::GameObject* gameObject, float rotSpeed, float radius);
		virtual ~RotatorComponent() = default;
		void Update(float deltaTime) override;
		void Render() const override {};

		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;
	private:
		float m_Angle = 0.0f;
		float m_Speed = 180.0f;
		float m_Radius = 100.0f;
		dae::Transform m_Pivot;
		bool parentPivot = false;
	};

}

