#include "HealthObserver.h"
#include "TextComponent.h"

dae::HealthObserver::HealthObserver(GameObject* gameObject)
	: Component(gameObject)
{
}
#pragma warning(push)
#pragma warning(disable : 4100) // Disable warning for unreferenced formal parameter
// Ik weet dat dit een beeke de bedoeling van de warning level 4 verbrot
// Maar de warning is fout, want ik gebruik de parameter wel degelijk
// Aanstaande maandag zal ik dit met u bespreken om te zien waar ik fout loop
void dae::HealthObserver::Notify(const Event& event, GameObject* actor)
{
	if (event.id == EventId::HealthChanged)
	{
		// make reference to text component in health observer, so we can change the text
		TextComponent* textComp = static_cast<TextComponent*>(event.args[0].comp);
		textComp->SetText("Mono Health: " + std::to_string(event.args[0].i));
	}
}
#pragma warning(pop)

void dae::HealthObserver::Update(float )
{
}

void dae::HealthObserver::Render() const
{
}
