#include "HealthComponent.h"
#include "Event.h"
#include <ServiceLocator.h>

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
	Notify(event, GetGameObject());
	if (m_Health <= 0)
	{
		auto& ss = dae::ServiceLocator::GetSoundSystem();
		ss.playSound(0, 10);
		GetGameObject()->SetMarkedForDeath();
	}
}

int dae::HealthComponent::GetHealth() const
{
	return m_Health;
}
