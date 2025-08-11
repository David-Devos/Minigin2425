#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include <string>
#include <list>

namespace dae
{
	class Texture2D;
	class Component;

	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render() const;


		void SetTransformDirtyFlag();
		void SetLocalPosition(float x, float y);
		void SetGlobalPosition(float x, float y);
		Transform* GetGlobalTransform();
		Transform* GetLocalTransform();
		void AddComponent(std::unique_ptr<Component> newComponent);
		void RemoveComponent(const std::unique_ptr<Component>& toRemoveComponent);
		template<typename T>
		T* GetComponent();
		template<typename T>
		bool HasComponent();
		bool GetMarkedForDeath() const { return m_MarkedForDeath; }
		void SetMarkedForDeath();
		void SetParent(GameObject* parent, bool worldPosStays);
		GameObject* GetParent() const { return m_pParent; }
		int GetChildCount() const { return int(m_pChildren.size()); }
		GameObject* GetChildAt(int index) const { return m_pChildren[index]; }
		std::string GetTag() { return m_Tag; };


		GameObject(std::string tag = "");
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);
		bool IsChild(GameObject* child);

		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren;
		std::vector<std::unique_ptr<Component>> m_Components;
		bool m_MarkedForDeath{ false };
		Transform m_globalTransform{};
		Transform m_localTransform{};
		bool m_posDirtyFlag{ false };
		const std::string m_Tag{""};
	};

}
template<typename T>
T* dae::GameObject::GetComponent()
{
	for (const std::unique_ptr<Component>& component : m_Components)
	{
		T* castedComponent = dynamic_cast<T*>(component.get());

		if (castedComponent != nullptr)
		{
			return castedComponent;
		}
	}
	return nullptr;
}

template<typename T>
bool dae::GameObject::HasComponent()
{
	return GetComponent<T>() != nullptr;
}
