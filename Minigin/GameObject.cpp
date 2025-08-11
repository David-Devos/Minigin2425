#include <string>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::GameObject(std::string tag)
	:m_Tag{tag}
{
	m_pChildren = std::vector<GameObject*>();
	m_Components = std::vector<std::unique_ptr<Component>>();
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
	if (m_MarkedForDeath)
	{
		m_Components.clear();
		m_pChildren.clear();
		if (m_pParent != nullptr)
		{
			m_pParent->RemoveChild(this);
			m_pParent = nullptr;

		}
	}
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

bool dae::GameObject::IsChild(GameObject* child)
{
	for (GameObject* currChild : m_pChildren)
	{
		if (child == currChild)
			return true;
	}
	return false;
}
void dae::GameObject::SetMarkedForDeath()
{
	m_MarkedForDeath = true;
	for (int i = 0; i < GetChildCount(); ++i)
	{
		GetChildAt(i)->SetMarkedForDeath();
	}
	
}
void dae::GameObject::SetParent(GameObject* parent, bool worldPosStays)
{
	if (IsChild(parent) || parent == this || parent == m_pParent)
		return;
	if (parent == nullptr)
	{
		auto globalTransform = GetGlobalTransform()->GetPosition();
		SetLocalPosition(globalTransform.x, globalTransform.y);
	}
	else
	{
		if (worldPosStays)
		{
			glm::vec3 pos = GetGlobalTransform()->GetPosition() - parent->GetGlobalTransform()->GetPosition();
			SetLocalPosition(pos.x, pos.y);
		}
		SetTransformDirtyFlag();
	}
	if (m_pParent) m_pParent->RemoveChild(this);
	m_pParent = parent;
	if (m_pParent) m_pParent->AddChild(this);

}