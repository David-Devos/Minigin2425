#include "GridComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "CollisionComponent.h"
#include "Subject.h"
#include <iostream>
namespace dae
{

	GridComponent::GridComponent(GameObject* gameObj, int cols, int rows, float cellSize)
		: Component(gameObj), m_Rows(rows), m_Cols(cols), m_CellSize(cellSize) {
		m_GridlockedObjects = std::map<GameObject*, GridLockedObject*>();
		m_BlocksOnGrid = std::map<std::tuple<int, int>, GridLockedObject*>();
	}

	void GridComponent::AddGridlockedGO(dae::GameObject* go, int col, int row, GridType type)
	{
		go->SetParent(GetGameObject(), true);
		if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) {
			return;
		}
		//auto pos = GetGameObject()->GetGlobalTransform()->GetPosition();
		GridLockedObject temp{};
		temp.pGameObject = go;
		temp.row = row;
		temp.col = col;
		if (go->GetTag() != "Water")
		{
			temp.type = type;
			if (!IsFreeSpot(col, row))
			{
				return;
			}

			go->SetLocalPosition(col * m_CellSize, row * m_CellSize);
			go->SetTransformDirtyFlag();
			if (type == GridType::Block)
			{
				m_BlocksOnGrid.emplace(std::make_tuple(col, row), new GridLockedObject(temp));
			}
		}
		else
		{
			temp.type = GridType::Water;

		}
		m_GridlockedObjects.emplace(go, new GridLockedObject(temp));
		int counter = 0;
		std::cout << counter << std::endl;
	}
	void GridComponent::RemoveGridlockedGO(GameObject* go, GridType type)
	{
		if (type == GridType::Block)
		{
			auto gridObj = m_GridlockedObjects.find(go)->second;
			m_BlocksOnGrid.erase(std::tuple<int, int>{(*gridObj).col, (*gridObj).row});
			ServiceLocator::GetColliderManager().RemoveCollider(go->GetComponent<CollisionComponent>());
		}
		m_GridlockedObjects.erase(go);
		go->SetMarkedForDeath();
	}
	bool GridComponent::IsFreeSpot(int col, int row) const
	{
		auto block = m_BlocksOnGrid.find(std::make_tuple(col, row));
		if (block != m_BlocksOnGrid.end())
		{
			return false;
		}

		if (row >= m_Rows || row < 0 || col >= m_Cols || col < 0)
		{
			return false;
		}

		return true;
	}
	bool GridComponent::IsFreeSpot(GameObject* go, glm::vec2 direction) const
	{
		auto obj = m_GridlockedObjects.find(go);
		if (obj == m_GridlockedObjects.end())
		{
			return false; // object is nie op de grid
		}
		return IsFreeSpot(obj->second->col + static_cast<int>(direction.x),
			obj->second->row + static_cast<int>(direction.y));
	}
	void GridComponent::UpdatePos(GameObject* go, glm::vec2 direction)
	{
		auto obj = m_GridlockedObjects.find(go);
		if (obj == m_GridlockedObjects.end())
		{
			return;
		}
		if (direction == glm::vec2{ 0,0 })
			return;
		if (go->GetTag() == "Block") // nogal duur om in hotcode te zitten :(
		{
			go->GetComponent<CollisionComponent>()->m_Check = true;
		}
		obj->second->col += static_cast<int>(direction.x);
		obj->second->row += static_cast<int>(direction.y);
	}
	glm::vec2 GridComponent::GetPosOnGO(GameObject* go)
	{
		auto it = m_GridlockedObjects.find(go);
		if (it != m_GridlockedObjects.end())
		{
			return glm::vec2{ static_cast<float>(it->second->col), static_cast<float>(it->second->row) };
		}
		return glm::vec2{ -1.f, -1.f }; // not found
	}
	void GridComponent::BufferBlock(glm::vec2 position)
	{
		auto block = m_BlocksOnGrid.find(std::make_tuple(static_cast<int>(position.x), static_cast<int>(position.y)));
		if (block == m_BlocksOnGrid.end())
		{
			return;
		}
		m_BlockBuffer.push_back(block->second);
		m_BlocksOnGrid.erase(block);
	}
	void GridComponent::DeBufferBlock(GameObject* go)
	{
		auto it = m_GridlockedObjects.find(go);
		if (it == m_GridlockedObjects.end())
		{
			return;
		}
		for (auto& block : m_BlockBuffer)
		{
			if (block->pGameObject == go)
			{
				m_BlocksOnGrid.emplace(std::make_tuple(it->second->col, it->second->row), it->second);
				m_BlockBuffer.erase(std::remove(m_BlockBuffer.begin(), m_BlockBuffer.end(), block), m_BlockBuffer.end());
				return;
			}
		}
	}
	GameObject* GridComponent::GetBlockOnPos(glm::vec2 position)
	{
		auto block = m_BlocksOnGrid.find(std::make_tuple(static_cast<int>(position.x), static_cast<int>(position.y)));
		if (block == m_BlocksOnGrid.end())
		{
			return nullptr;
		}
		return block->second->pGameObject;
	}
	void GridComponent::Notify(const BaseEvent& event, GameObject* go)
	{
		if (typeid(event) != typeid(OnCollision))
			return;

		if (go->GetTag() == "Player" && event.args->go->GetTag() == "SnoBee")
		{
			m_GridlockedObjects.erase(go);
			ServiceLocator::GetColliderManager().RemoveCollider(go->GetComponent<CollisionComponent>());
		}
		else if (go->GetTag() == "SnoBee" && event.args->go->GetTag() == "Player")
		{
			m_GridlockedObjects.erase(event.args->go);
			ServiceLocator::GetColliderManager().RemoveCollider(event.args->go->GetComponent<CollisionComponent>());
		}
		if (go->GetTag() == "Block" && event.args->go->GetTag() == "SnoBee")
		{
			m_GridlockedObjects.erase(event.args->go);
			event.args->go->SetMarkedForDeath();
			ServiceLocator::GetColliderManager().RemoveCollider(event.args->go->GetComponent<CollisionComponent>());
		}
		else if (event.args->go->GetTag() == "Block" && go->GetTag() == "SnoBee")
		{
			m_GridlockedObjects.erase(go);
			go->SetMarkedForDeath();
			ServiceLocator::GetColliderManager().RemoveCollider(go->GetComponent<CollisionComponent>());
		}

	}
	bool GridComponent::IsOOB(GameObject* go, glm::vec2 direction) const
	{
		auto obj = m_GridlockedObjects.find(go);
		int col = obj->second->col + static_cast<int>(direction.x);
		int row = obj->second->row + static_cast<int>(direction.y);
		if (row >= m_Rows || row < 0 || col >= m_Cols || col < 0)
		{
			return true;
		}
		return false;
	}
}