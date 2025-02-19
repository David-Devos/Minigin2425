#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject) : Component(gameObject)
{
}
void dae::RenderComponent::Update(float /*deltaTime*/)
{

}

void dae::RenderComponent::Render(Texture2D* texture) const
{
	if (m_pGameObject != nullptr)
	{
		const auto& pos = m_pGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture = texture;
}

void dae::RenderComponent::Render() const
{
	if (m_pGameObject != nullptr && m_texture != nullptr)
	{
		const auto& pos = m_pGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture.get(), pos.x, pos.y);

	}
}

