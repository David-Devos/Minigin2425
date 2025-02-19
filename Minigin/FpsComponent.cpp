#include "FpsComponent.h"
#include <ios>
#include <iomanip>


dae::FpsComponent::FpsComponent(TextComponent* textComponent, GameObject* gameObject) :Component(gameObject), m_Fps{ 0 }, m_pTextComponent{ textComponent }
{
}

dae::FpsComponent::~FpsComponent()
{
}

void dae::FpsComponent::Update(float deltaTime)
{
	m_Fps = 1 / deltaTime;
	std::stringstream text{};
	text << std::fixed << std::setprecision(1) << m_Fps << " FPS";
	m_pTextComponent->SetText(text.str());


}

void dae::FpsComponent::Render() const
{
}


