#include "GridComponent.h"
#include "GameObject.h"
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
		if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) {
			return;
		}
		if (!IsFreeSpot(col, row))
		{
			return;
		}
		auto pos = m_pGameObject->GetGlobalTransform()->GetPosition();
		go->SetLocalPosition(pos.x + col * m_CellSize, pos.y + row * m_CellSize);
		go->SetTransformDirtyFlag();
		GridLockedObject temp{};
		temp.pGameObject = go;
		temp.row = row;
		temp.col = col;
		temp.type = type;
		if (type == GridType::Block)
		{
			m_BlocksOnGrid.emplace(std::make_tuple(col, row), new GridLockedObject(temp));
		}
		m_GridlockedObjects.emplace(go, new GridLockedObject(temp));
		int counter = 0;
		std::cout << counter << std::endl;
	}
	bool GridComponent::IsFreeSpot(int col, int row) const
	{
		auto block = m_BlocksOnGrid.find(std::make_tuple(col, row));
		if (block != m_BlocksOnGrid.end())
		{
			return false;
		}
		if (row > m_Rows || row < 0 || col > m_Cols || col < 0)
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
}