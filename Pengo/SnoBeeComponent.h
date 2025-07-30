#pragma once
#include "Component.h"
namespace dae
{
	class GameObject;
	class ControllableComponent;
	class GridComponent;
	class SnoBeeComponent : public Component
	{
	public:
		SnoBeeComponent(GameObject* gameObject, ControllableComponent* controllableComp, GridComponent* gridComp);
		void Update(float deltaTime) override;
		void Render() const override {};
	private:
		void MoveSnoBee(glm::vec2 direction);
		ControllableComponent* m_pControllableComp;
		GridComponent* m_pGridComponent;
		glm::vec2 m_direction{};
	};

}

