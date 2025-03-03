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

void dae::GameObject::RemoveChild(GameObject* child)
{
	if (child != nullptr)
	{
		m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	if (child != nullptr)
	{
		m_pChildren.push_back(child);
	}
}


void dae::GameObject::Update(float deltaTime)
{
	for (const std::unique_ptr<Component>& component : m_Components)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (int i = int(m_Components.size()) - 1; i >= 0; i--)
	{
		if (m_Components[i]->GetMarkedForDeath())
		{

			RemoveComponent(m_Components[i]);
			//m_Components.erase(m_Components.begin() + i);
			continue;
		}
		m_Components[i]->LateUpdate(deltaTime);
	}
	/*
	for (const std::unique_ptr<Component>& component : m_Components)
	{
		if (component->GetMarkedForDeath())
		{
			RemoveComponent(component);
			continue;
		}
		component->LateUpdate(deltaTime);
	}*/
}

void dae::GameObject::Render() const
{
	for (const std::unique_ptr<Component>& component : m_Components)
	{
		component->Render();
	}
}


void dae::GameObject::SetTransformDirtyFlag()
{
	m_posDirtyFlag = true;
	for (GameObject* go : m_pChildren)
	{
		go->SetTransformDirtyFlag();
	}
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_localTransform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetGlobalPosition(float x, float y)
{
	m_globalTransform.SetPosition(x, y, 0.0f);
}

dae::Transform* dae::GameObject::GetGlobalTransform()
{
	if (m_posDirtyFlag)
	{
		if (m_pParent != nullptr)
			m_globalTransform.SetPosition(m_pParent->GetGlobalTransform()->GetPosition() + m_localTransform.GetPosition());
		else
			m_globalTransform = m_localTransform;
		m_posDirtyFlag = false;
	}
	return &m_globalTransform;
}

dae::Transform* dae::GameObject::GetLocalTransform()
{
	return &m_localTransform;
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> newComponent)
{
	if (newComponent != nullptr)
	{
		m_Components.push_back(std::move(newComponent));
	}
}

void dae::GameObject::RemoveComponent(const std::unique_ptr<Component>& toRemoveComponent)
{
	if (toRemoveComponent != nullptr)
	{
		//m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), toRemoveComponent), m_Components.end());

		m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(),
			[&toRemoveComponent](const std::unique_ptr<Component>& component) {
				return component.get() == toRemoveComponent.get();
			}), m_Components.end());
	}
}

void dae::GameObject::SetParent(GameObject* parent, bool worldPosStays)
{
	if (parent != nullptr)
	{
		if (worldPosStays)
		{
			m_localTransform.SetPosition(m_globalTransform.GetPosition() - parent->GetGlobalTransform()->GetPosition());
			m_posDirtyFlag = true;
		}	
		
		if (m_pParent != nullptr)
			m_pParent->RemoveChild(this);
		m_pParent = parent;
		m_pParent->AddChild(this);
	}
	else
	{
		if (m_pParent != nullptr)
			m_pParent->RemoveChild(this);
		m_pParent = nullptr;
		m_localTransform = m_globalTransform;
	}
}
