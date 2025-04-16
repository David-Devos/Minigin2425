#include "ControllableComponent.h"
#include "GameObject.h"

dae::ControllableComponent::ControllableComponent(dae::GameObject* gameObject, float movSpeed) :
	Component(gameObject)
, m_Speed(movSpeed)
{

}

void dae::ControllableComponent::Update(float deltaTime)
{
	if (m_Direction.x != 0 || m_Direction.y != 0)
	{
		m_Direction = glm::normalize(m_Direction);
		auto pos = m_pGameObject->GetLocalTransform()->GetPosition();
		m_pGameObject->SetLocalPosition(pos.x + m_Direction.x * m_Speed * deltaTime,
			pos.y + m_Direction.y *m_Speed*deltaTime);
		m_pGameObject->SetTransformDirtyFlag();
		m_Direction = {};
	}

}
