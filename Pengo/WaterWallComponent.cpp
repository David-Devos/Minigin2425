#include "WaterWallComponent.h"
#include "PushableComponent.h"
#include <CollisionComponent.h>

namespace dae
{

	WaterWallComponent::WaterWallComponent(GameObject* gameObject, GridComponent* gridComp, glm::vec2 gridSide)
		:Component(gameObject), m_GridSide(gridSide)
	{
		float x = gridComp->GetGameObject()->GetGlobalTransform()->GetPosition().x +
			gridComp->GetCellSize() * gridComp->GetColRow().x / 2 + (gridComp->GetCellSize() * gridComp->GetColRow().x / 2) * gridSide.x;
		float y = gridComp->GetGameObject()->GetGlobalTransform()->GetPosition().y +
			gridComp->GetCellSize() * gridComp->GetColRow().y / 2 + (gridComp->GetCellSize() * gridComp->GetColRow().y / 2) * gridSide.y;
		gameObject->SetGlobalPosition(x,y);

	}


	void WaterWallComponent::Update(float deltaTime)
	{
		if (m_Timer > 0)
		{
			m_Timer -= deltaTime;
			if (m_Timer <= 0)
			{
				auto col = GetGameObject()->GetComponent<CollisionComponent>();
				col->m_Check = false;
			}
		}
	}

	void WaterWallComponent::Notify(const BaseEvent& event, GameObject*)
	{
		if (typeid(event) != typeid(WaterInteractEvent))
			return;
		if(event.args->vec2 != m_GridSide)
			return;
		GetGameObject()->GetComponent<PushableComponent>()->GetInteracted(m_GridSide);
	}
	void WaterWallComponent::ActivateWall()
	{
		m_Timer = m_MaxTime;
		GetGameObject()->GetComponent<CollisionComponent>()->m_Check = true;
		GetGameObject()->GetComponent<PushableComponent>()->HitWall(glm::vec2{0,0});
	}
}

