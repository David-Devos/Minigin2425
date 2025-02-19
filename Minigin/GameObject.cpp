#include <string>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
{
}

dae::GameObject::~GameObject()
{
	m_Components.clear();
}


void dae::GameObject::Update(float deltaTime)
{
	for (const std::unique_ptr<Component>& component : m_Components)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (const std::unique_ptr<Component>& component : m_Components)
	{
		component->Render();
	}
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Transform* dae::GameObject::GetTransform()
{
	return &m_transform;
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> newComponent)
{
	if (newComponent != nullptr)
	{
		m_Components.push_back(std::move(newComponent));
	}
}

void dae::GameObject::RemoveComponent(std::unique_ptr<Component> toRemoveComponent)
{
	if (toRemoveComponent != nullptr)
	{
		m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), toRemoveComponent), m_Components.end());
	}
}