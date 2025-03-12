#pragma once
#include "Transform.h"
#include "GameObject.h"
namespace dae
{

	class Component
	{
	protected:
		Component(GameObject* gameObject);
		//Component() = default; no default, cause a component can only exist with an owning game object
		GameObject* m_pGameObject;

	public:
		virtual ~Component();
		virtual void Update(float) = 0;
		virtual void LateUpdate(float);
		virtual void Render() const = 0;
		bool GetMarkedForDeath() const { return m_MarkedForDeath; }

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	private:
		Transform* m_pTransform;
		bool m_MarkedForDeath{ false };
	};

}