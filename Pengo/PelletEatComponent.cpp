#include "PelletEatComponent.h"
#include "Event.h"

dae::PelletEatComponent::PelletEatComponent(dae::GameObject* gameObject, int health, TextComponent* textComp) : Component(gameObject)
, m_Score{ health }, m_pTextComponent{ textComp }
{

}

void dae::PelletEatComponent::Update(float)
{
	//empty cause I dont want to do anything, but it also cannot be an abstract class
}

void dae::PelletEatComponent::Render() const
{
	//empty cause I dont want to do anything, but it also cannot be an abstract class
}

void dae::PelletEatComponent::EatPellet(int points)
{
	m_Score += points;
	PelletEatenEvent event{};
	event.args[0] = EventArg(m_Score, m_pTextComponent);
	Notify(event, GetGameObject());
	if (m_Score <= 0)
	{
		GetGameObject()->SetMarkedForDeath();
	}
}

int dae::PelletEatComponent::GetScore() const
{
	return m_Score;
}
