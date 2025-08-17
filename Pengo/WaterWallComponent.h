#pragma once
#include "Component.h"
#include "GridComponent.h"
#include "Observer.h"
#include "Event.h"
namespace dae
{

	class WaterWallComponent : public Component, public Observer
	{
	public:
		WaterWallComponent(GameObject* gameObject, GridComponent* gridComp, glm::vec2 gridSide);
		void Update(float deltaTime) override;
		void Render() const override {};
		void Notify(const BaseEvent& event, GameObject* actor) override;
		void ActivateWall();
	private:
		glm::vec2 m_GridSide;
		float m_Timer{ 0.f };
		float m_MaxTime{ 1.f };
	};
}

