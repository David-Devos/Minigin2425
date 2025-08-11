#include "PelletObserver.h"
#include "TextComponent.h"
#include "Event.h"

dae::PelletObserver::PelletObserver(GameObject* gameObject)
	: Component(gameObject)
{
}
void dae::PelletObserver::Notify(const BaseEvent& event, GameObject*)
{
	if (typeid(event) == typeid(PelletEatenEvent))
	{
		// make reference to text component in health observer, so we can change the text
		TextComponent* textComp = static_cast<TextComponent*>(event.args[0].comp);
		textComp->SetText("Player Score: " + std::to_string(event.args[0].i));
		// CATCH THROW TO SEE IF TEXT COMPONENT CAST WORKS
	}
}

void dae::PelletObserver::Update(float)
{
}

void dae::PelletObserver::Render() const
{
}