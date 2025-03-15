#include "PelletObserver.h"
#include "TextComponent.h"

dae::PelletObserver::PelletObserver(GameObject* gameObject)
	: Component(gameObject)
{
}
#pragma warning(push)
#pragma warning(disable : 4100) // Disable warning for unreferenced formal parameter
// Ik weet dat dit een beeke de bedoeling van de warning level 4 verbrot
// Maar de warning is fout, want ik gebruik de parameter wel degelijk
// Aanstaande maandag zal ik dit met u bespreken om te zien waar ik fout loop
void dae::PelletObserver::Notify(const Event& event, GameObject* actor)
{
	if (event.id == EventId::PelletEaten)
	{
		// make reference to text component in health observer, so we can change the text
		TextComponent* textComp = static_cast<TextComponent*>(event.args[0].comp);
		textComp->SetText("Player Score: " + std::to_string(event.args[0].i));
	}
}
#pragma warning(pop)

void dae::PelletObserver::Update(float)
{
}

void dae::PelletObserver::Render() const
{
}