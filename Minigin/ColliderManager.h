#pragma once
#include <vector>
#include "Subject.h"
namespace dae
{
	class CollisionComponent;
	class ColliderManager : public Subject
	{
	public:
		ColliderManager() = default;
		~ColliderManager() = default;
		ColliderManager(const ColliderManager&) = delete;
		ColliderManager(ColliderManager&&) = delete;
		ColliderManager& operator=(const ColliderManager&) = delete;
		ColliderManager& operator=(ColliderManager&&) = delete;

		void AddCollider(class CollisionComponent* pCollide);
		void RemoveCollider(const class CollisionComponent* pCollider);
		void Update();
		void ClearColliders() { m_Colliders.clear(); };//overweeg of deze wel nodig zijn
		bool IsEmpty() const { return m_Colliders.empty(); };
	private:
		std::vector<class CollisionComponent*> m_Colliders;
	};
}

