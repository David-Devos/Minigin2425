#include "ColliderManager.h"
#include "CollisionComponent.h"
#include "BaseEvent.h"
#include <iostream>

void dae::ColliderManager::AddCollider(CollisionComponent* pCollide)
{
	if (pCollide)
	{
		m_Colliders.push_back(pCollide);
	}
}

void dae::ColliderManager::RemoveCollider(const CollisionComponent* pCollider)
{
	if (pCollider)
	{
		m_Colliders.erase(std::find(m_Colliders.begin(), m_Colliders.end(), pCollider));
	}
}

void dae::ColliderManager::Update()
{
	for (size_t i = 0; i < m_Colliders.size(); ++i) {
		CollisionComponent* a = m_Colliders[i];
		if (a->m_Check == false)
			continue;
		for (size_t j = i + 1; j < m_Colliders.size(); ++j) {
			CollisionComponent* b = m_Colliders[j];
			if (b->m_Check == false)
				continue;
			if (a->TriggerContainsCollider(b->GetMin(), b->GetMax())) {
				OnCollision event{};
				event.args[0] = EventArg(0, nullptr, a->GetGameObject());
				Notify(event, b->GetGameObject());
				std::cout << "Overlapping\n";
			}
		}
	}
}
