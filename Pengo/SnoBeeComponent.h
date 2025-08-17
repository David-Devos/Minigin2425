#pragma once
#include "Component.h"
#include "Observer.h"
namespace dae
{
	class GameObject;
	class ControllableComponent;
	class GridComponent;
	class SnoBeeComponent : public Component, public Observer
	{
	public:
		SnoBeeComponent(GameObject* gameObject, ControllableComponent* controllableComp, GridComponent* gridComp);
		~SnoBeeComponent();
		void Update(float deltaTime) override;
		void Render() const override {};
		void Notify(const BaseEvent& event, GameObject* go) override;
	private:
		void GetStunned() { m_Counter = m_MaxCount; }
		void MoveSnoBee(glm::vec2 direction);
		ControllableComponent* m_pControllableComp;
		GridComponent* m_pGridComponent;
		glm::vec2 m_direction{};
		float m_Counter{ 0 };
		const float m_MaxCount{ 4 };
	};

}

