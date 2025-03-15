#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(dae::GameObject* gameObject, int health, TextComponent* textComp) : Component(gameObject)
, m_Health{ health }, m_pTextComponent{ textComp }
{

}

void dae::HealthComponent::Update(float )
{
	//empty cause I dont want to do anything, but it also cannot be an abstract class
}

void dae::HealthComponent::Render() const
{
	//empty cause I dont want to do anything, but it also cannot be an abstract class
}

void dae::HealthComponent::TakeDamage(int damage)
{
	m_Health -= damage;
	Event event(EventId::HealthChanged);
	event.args[0] = EventArg(m_Health, m_pTextComponent);
	Notify(event, m_pGameObject);
	if (m_Health <= 0)
	{
		m_pGameObject->SetMarkedForDeath();
	}
}

int dae::HealthComponent::GetHealth() const
{
	return m_Health;
}
