#include "CollisionComponent.h"
#include <iostream>
namespace dae
{

	CollisionComponent::CollisionComponent(GameObject* gameObj, glm::vec2 center, float width, float height, bool check)
		: Component(gameObj),
		m_Center{ center },
		m_Width{ width },
		m_Height{ height },
		m_Check{ check }
	{

	}
	bool CollisionComponent::TriggerContainsCollider(glm::vec2 min, glm::vec2 max)
	{
		return (min.x <= GetMax().x && max.x >= GetMin().x) &&
			(min.y <= GetMax().y && max.y >= GetMin().y);
	}
	glm::vec2 CollisionComponent::GetMin()
	{
		glm::vec2 min{};
		glm::vec3 parentPos{ GetGameObject()->GetGlobalTransform()->GetPosition() };
		min.x = parentPos.x + m_Center.x - m_Width / 2 ;
		min.y = parentPos.y + m_Center.y - m_Height / 2;
		return min;
	}
	glm::vec2 CollisionComponent::GetMax()
	{
		glm::vec2 max{};
		glm::vec3 parentPos{ GetGameObject()->GetGlobalTransform()->GetPosition() };
		max.x = parentPos.x + m_Center.x + m_Width / 2;
		max.y = parentPos.y + m_Center.y + m_Height / 2;
		return max;
	}
}
