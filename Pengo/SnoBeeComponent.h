#pragma once
#include "Component.h"
namespace dae
{
	class GameObject;
	class ControllableComponent;
	class SnoBeeComponent : public Component
	{
	public:
		SnoBeeComponent(GameObject* gameObject, ControllableComponent* controllableComponentHandle);
		void Update(float deltaTime) override;
		void Render() const override {};
	private:
		ControllableComponent* m_pControllableComponentHandle; //meaning NO OWNERSHIP
	};

}

