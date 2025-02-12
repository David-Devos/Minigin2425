#pragma once
#include <memory>
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
		void Render() const;

		void SetPosition(float x, float y);
		Transform* GetTransform();
		void AddComponent(std::unique_ptr<Component> newComponent);
		void RemoveComponent(std::unique_ptr<Component> toRemoveComponent);
		template<typename T>
		T* GetComponent();
		template<typename T>
		bool HasComponent();

		GameObject();
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::list<std::unique_ptr<Component>> m_pComponents = std::list<std::unique_ptr<Component>>();

		Transform m_transform{};
	};

	template<typename T>
	T* dae::GameObject::GetComponent()
	{
		for (const std::unique_ptr<Component>& component : m_pComponents)
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
}
