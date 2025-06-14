#include "SnoBeeComponent.h"
#include "ControllableComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include <iostream>
namespace dae
{
	SnoBeeComponent::SnoBeeComponent(GameObject* gameObject, ControllableComponent* controllableComp, GridComponent* GridComp)
		: Component(gameObject),
		m_pControllableComp(controllableComp),
		m_pGridComponent(GridComp)
	{
		m_pControllableComp->AddDirection(glm::vec2{1,0});

	}

	void SnoBeeComponent::Update(float)
	{
		if (m_pControllableComp->IsMoving())
			return;
		std::srand(int(time(nullptr)));
		if (m_pControllableComp->GetLastDirection().x != 0)
		{
			if (std::rand() % 10 <= 2)
			{
				if (std::rand() % 2 == 0)
				{
					MoveSnoBee(glm::vec2{ 0, 1 });
				}
				else
				{
					MoveSnoBee(glm::vec2{ 0, -1 });
				}
			}
			else
			{
				MoveSnoBee(glm::vec2{ m_pControllableComp->GetLastDirection().x, 0 });
			}
		}
		else if (m_pControllableComp->GetLastDirection().y != 0)
		{
			if (std::rand() % 10 <= 2)
			{
				if (std::rand() % 2 == 0)
				{
					MoveSnoBee(glm::vec2{ 1, 0 });
				}
				else
				{
					MoveSnoBee(glm::vec2{ -1,  0 });
				}
			}
			else
			{
				MoveSnoBee(glm::vec2{ 0, m_pControllableComp->GetLastDirection().y });
			}
		}
	}
	void SnoBeeComponent::MoveSnoBee(glm::vec2 direction)
	{
		if (m_pGridComponent->IsFreeSpot(m_pGameObject, direction))
			m_pControllableComp->AddDirection(direction);
		else
			m_pControllableComp->Interact();


	}
}
