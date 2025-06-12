#include "ControllableComponent.h"
#include "GameObject.h"
#include "GridComponent.h"

dae::ControllableComponent::ControllableComponent(dae::GameObject* gameObject, float movSpeed, GridComponent* gridComp) :
	Component(gameObject)
	, m_Speed(movSpeed)
	, m_pGridComponent(gridComp)
{

}

void dae::ControllableComponent::Update(float deltaTime)
{
	if (m_Direction.x != 0 || m_Direction.y != 0)
	{
		m_Direction = glm::normalize(m_Direction);
		auto pos = m_pGameObject->GetLocalTransform()->GetPosition();
		if (m_pGridComponent != nullptr)
		{
			if (!m_pGridComponent->IsFreeSpot(m_pGameObject, m_Direction))
			{
				m_Direction = {};
				return;
			}
		}
		m_pGameObject->SetLocalPosition(pos.x + m_Direction.x * m_Speed * deltaTime,
			pos.y + m_Direction.y * m_Speed * deltaTime);
		m_pGameObject->SetTransformDirtyFlag();
		m_TimeMoving += deltaTime;
		if (m_pGridComponent != nullptr)
		{
			float timeToMove = m_pGridComponent->GetCellSize() / m_Speed;
			if (m_TimeMoving >= timeToMove)
			{
				m_pGameObject->SetLocalPosition(
					pos.x - m_Direction.x * m_TimeMoving * m_Speed + m_Direction.x * timeToMove * m_Speed,
					pos.y - m_Direction.y * m_TimeMoving * m_Speed + m_Direction.y * timeToMove * m_Speed);
				m_pGameObject->SetTransformDirtyFlag();
				m_pGridComponent->UpdatePos(m_pGameObject, m_Direction);
				m_TimeMoving = 0.0f;
				m_Direction = {};
			}
		}
		else
		{
			m_Direction = {};
		}
	}

}

bool dae::ControllableComponent::IsMoving() const
{
	return m_Direction.x != 0 || m_Direction.y != 0;
}
