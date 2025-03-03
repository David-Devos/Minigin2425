#include "RotatorComponent.h"

dae::RotatorComponent::RotatorComponent(dae::GameObject* gameObject, float rotSpeed, float radius)
	:Component(gameObject), m_Speed{ rotSpeed }, m_Radius{ radius }
{
	if (m_Pivot.GetPosition() == glm::vec3{0,0,0})
	{
		parentPivot = true;
	}
}

void dae::RotatorComponent::Update(float deltaTime)
{
	const float twoPi = 2.f*3.141592f;
	m_Angle += m_Speed * deltaTime;
	if (m_Angle >= twoPi)
		m_Angle -= twoPi;
	else if (m_Angle <= -twoPi)
		m_Angle += twoPi;
	m_pGameObject->GetLocalTransform()->SetPosition(glm::vec3{cos(m_Angle)*m_Radius, sin(m_Angle)*m_Radius,0});
	m_pGameObject->SetTransformDirtyFlag();
}

