#include "GridComponent.h"
#include "GameObject.h"
#include <iostream>
namespace dae
{

	GridComponent::GridComponent(GameObject* gameObj, int rows, int cols, float cellSize)
		: Component(gameObj), m_Rows(rows), m_Cols(cols), m_CellSize(cellSize) {
		m_GridlockedObjects = std::map<GameObject*, GridLockedObject*>();
		m_BlocksOnGrid = std::map<std::tuple<int, int>, GridLockedObject*>();
	}

	void GridComponent::AddGridlockedGO(dae::GameObject* go, int row, int col, GridType type)
	{
		if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) {
			return;
		}
		go->SetLocalPosition(col * m_CellSize, row * m_CellSize);
		go->SetTransformDirtyFlag();
		GridLockedObject temp{};
		temp.pGameObject = go;
		temp.row = row;
		temp.col = col;
		temp.type = type;
		if (type == GridType::Block)
		{
			m_BlocksOnGrid.emplace(std::make_tuple(row, col), new GridLockedObject(temp));
		}
		else
		{
			m_GridlockedObjects.emplace(go, new GridLockedObject(temp));
		}
	}
	bool GridComponent::IsFreeSpot(int row, int col) const
	{
		auto block = m_BlocksOnGrid.find(std::make_tuple(row, col));
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
		return IsFreeSpot(obj->second->row + static_cast<int>(direction.y),
			obj->second->col + static_cast<int>(direction.x));
	}
	void GridComponent::UpdatePos(GameObject* go, glm::vec2 direction)
	{
		auto obj = m_GridlockedObjects.find(go);
		if (obj == m_GridlockedObjects.end())
		{
			return;
		}
		obj->second->row += static_cast<int>(direction.y);
		obj->second->col += static_cast<int>(direction.x);
	}
}