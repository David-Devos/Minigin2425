#include "SnoBeeComponent.h"
#include "ControllableComponent.h"
#include "GameObject.h"
namespace dae
{
	SnoBeeComponent::SnoBeeComponent(GameObject* gameObject, ControllableComponent* controllableComponentHandle)
		: Component(gameObject),
		m_pControllableComponentHandle(controllableComponentHandle) {

	}

	void SnoBeeComponent::Update(float)
	{
		// hier mn behaviour voor de snobee in stoppen
		m_pControllableComponentHandle->AddDirection(glm::vec2{ 0,1 });
	}
}
