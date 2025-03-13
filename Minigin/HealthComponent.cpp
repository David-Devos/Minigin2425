#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(dae::GameObject* gameObject, int health) : Component(gameObject)
, m_Health{ health }
{
}

void dae::HealthComponent::TakeDamage(int damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		//m_pGameObject->SetMarkedForDeath();
	}
}

int dae::HealthComponent::GetHealth() const
{
	return m_Health;
}
