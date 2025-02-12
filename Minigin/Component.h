#pragma once
#include "Transform.h"
#include "GameObject.h"
namespace dae
{
	class Component
	{
	protected:
		Component(std::shared_ptr< GameObject> gameObject);
		Component() = default;
		std::shared_ptr< GameObject> m_pGameObject;

	public:
		virtual ~Component() = default;
		virtual void Update(float) = 0;
		virtual void Render() = 0;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	private:
		Transform* m_pTransform;
	};

}