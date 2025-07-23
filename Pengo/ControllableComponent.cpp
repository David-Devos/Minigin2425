#include "ControllableComponent.h"
#include "GameObject.h"
#include "PushableComponent.h"
#include <iostream>

dae::ControllableComponent::ControllableComponent(dae::GameObject* gameObject, float movSpeed, GridType type, GridComponent* gridComp) :
	Component(gameObject)
	, m_Speed(movSpeed)
	, m_pGridComponent(gridComp)
	, m_Direction(glm::vec2{ 0.0f, 0.0f })
	, m_LastDirection(glm::vec2{ 0.0f, 0.0f })
	, m_Type(type)
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
				m_LastDirection = m_Direction;
				m_Direction = {};
				m_EstimatedEndPos = {};
				if (m_Type == GridType::Block)
				{
					m_pGridComponent->DeBufferBlock(m_pGameObject);
					m_pGameObject->GetComponent<PushableComponent>()->HitWall(m_pGridComponent->GetPosOnGO(m_pGameObject));
				}
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
					m_EstimatedEndPos.x,
					m_EstimatedEndPos.y);
				std::cout << "Moving to: " << m_EstimatedEndPos.x << ", "
					<< m_EstimatedEndPos.y << std::endl;
				m_pGameObject->SetTransformDirtyFlag();
				m_pGridComponent->UpdatePos(m_pGameObject, m_Direction);
				m_TimeMoving = 0.0f;
				m_LastDirection = m_Direction;
				m_Direction = {};
				m_EstimatedEndPos = {};
			}
		}
		else
		{
			m_LastDirection = m_Direction;
			m_Direction = {};
			m_EstimatedEndPos = {};
		}
	}

}

void dae::ControllableComponent::AddDirection(const glm::vec2& direction)
{
	if (!IsMoving())
	{
		auto pos = m_pGameObject->GetLocalTransform()->GetPosition();
		float cellSize = m_pGridComponent->GetCellSize();
		m_Direction += direction;
		m_EstimatedEndPos.x += (std::round((pos.x - 8)/cellSize ) + direction.x) * cellSize + 8; //tijdelijke +8 (hopelijk) omdat grid begint op 8x8
		m_EstimatedEndPos.y += (std::round((pos.y - 8)/cellSize ) + direction.y) * cellSize + 8;
	}
}

bool dae::ControllableComponent::IsMoving() const
{
	return m_Direction.x != 0 || m_Direction.y != 0;
}

void dae::ControllableComponent::Interact()
{
	if (!m_pGridComponent->IsFreeSpot(m_pGameObject, m_LastDirection))
	{
		glm::vec2 pos = m_pGridComponent->GetPosOnGO(m_pGameObject);
		auto block = m_pGridComponent->GetBlockOnPos(glm::vec2{ pos.x + m_LastDirection.x, pos.y + m_LastDirection.y });
		if (block != nullptr)
			block->GetComponent<PushableComponent>()->GetInteracted(m_LastDirection);
		//else voor de water randen
		return;
	}
}
