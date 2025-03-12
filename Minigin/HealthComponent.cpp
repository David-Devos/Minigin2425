#include "HealthComponent.h"

HealthComponent::HealthComponent(dae::GameObject* gameObject, int health) : Component(gameObject)
, m_Health{ health }
{
}

void HealthComponent::TakeDamage(int damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		//m_pGameObject->SetMarkedForDeath();
	}
}

int HealthComponent::GetHealth() const
{
	return m_Health;
}
