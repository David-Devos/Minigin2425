#include "HealthObserver.h"
#include "TextComponent.h"
#include "Event.h"

dae::HealthObserver::HealthObserver(GameObject* gameObject)
	: Component(gameObject)
{
}
void dae::HealthObserver::Notify(const BaseEvent& event, GameObject*)
{
	if (typeid(event) == typeid(HealthChangedEvent))
	{
		// make reference to text component in health observer, so we can change the text
		TextComponent* textComp = static_cast<TextComponent*>(event.args[0].comp);
		textComp->SetText("Player Health: " + std::to_string(event.args[0].i));
	}
}

void dae::HealthObserver::Update(float )
{
}

void dae::HealthObserver::Render() const
{
}
