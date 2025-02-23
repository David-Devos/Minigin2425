#include "RotatorComponent.h"

dae::RotatorComponent::RotatorComponent(dae::GameObject* gameObject, float rotSpeed, float radius, dae::Transform pivot)
	:Component(gameObject), m_Speed{ rotSpeed }, m_Radius{ radius }, m_Pivot{ pivot }
{
	if (m_Pivot.GetPosition() == glm::vec3{0,0,0})
	{
		m_Pivot = *m_pGameObject->GetParent()->GetGlobalTransform();
	}
}

void dae::RotatorComponent::Update(float deltaTime)
{
	m_Angle += m_Speed * deltaTime;
	m_pGameObject->GetLocalTransform()->SetPosition(m_Pivot.GetPosition()
		+ glm::vec3{cos(m_Angle)*m_Radius, sin(m_Angle)*m_Radius,0});
}

