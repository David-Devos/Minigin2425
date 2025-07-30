#pragma once
#include "Transform.h"
#include "GameObject.h"
namespace dae
{
	class Component
	{
	protected:
		Component(GameObject* gameObject);
		//Component() = default; no default, case a component can only exist with an owning game object

	public:
		virtual ~Component();
		virtual void Update(float) = 0;
		virtual void LateUpdate(float);
		virtual void Render() const = 0;
		bool GetMarkedForDeath() const { return m_MarkedForDeath; }
		GameObject* GetGameObject() const { return m_pGameObject; }

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	private:
		GameObject* m_pGameObject;
		Transform* m_pTransform;
		bool m_MarkedForDeath{ false };
	};

}