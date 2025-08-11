#pragma once
#include "Component.h"
namespace dae
{
	class CollisionComponent : public Component
	{
	public:
		CollisionComponent(GameObject* gameObj, glm::vec2 center, float width, float height, bool check = false);
		virtual ~CollisionComponent() = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		bool TriggerContainsCollider(glm::vec2 min, glm::vec2 max);
		glm::vec2 GetMin();
		glm::vec2 GetMax();
		void Update(float) override {};
		void Render() const override {};

		
		bool m_Check;
	private:
		const glm::vec2 m_Center; //localpos van parent + center = center van de collision 
		const float m_Width;
		const float m_Height;
	};
}

