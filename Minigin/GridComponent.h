#pragma once
#include "Component.h"
#include <vector>
#include <memory>
#include <map>
namespace dae
{
	enum class GridType
	{
		Block,
		Pengo,
		SnoBee
	};
	class GameObject;
	struct GridLockedObject
	{
		GameObject* pGameObject;
		int row;
		int col;
		GridType type;
	};

	class GridComponent : public Component
	{
	public:
		GridComponent(GameObject* gameObj, int cols, int rows, float cellSize);
		virtual ~GridComponent() = default;
		void Update(float) override {};
		void Render() const override {};
		float GetCellSize() const { return m_CellSize; }
		void AddGridlockedGO(GameObject* go, int col, int row, GridType type);
		bool IsFreeSpot(int row, int col) const;
		bool IsFreeSpot(GameObject* go, glm::vec2 direction) const; // voor alles behalve blokken
		void UpdatePos(GameObject* go, glm::vec2 direction);
		GameObject* GetBlockOnPos(glm::vec2 direction) ;
		glm::vec2 GetPosOnGO(GameObject* go);
		void BufferBlock(glm::vec2 position);
		void DeBufferBlock(GameObject* go);

		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;
	private:
		int m_Rows;
		int m_Cols;
		float m_CellSize;
		std::map<GameObject*, GridLockedObject*> m_GridlockedObjects;
		std::map<std::tuple<int, int>, GridLockedObject*> m_BlocksOnGrid;// map met glm:vec2 deed raar en wou nie werken
		std::vector<GridLockedObject*> m_BlockBuffer;
	};
}

