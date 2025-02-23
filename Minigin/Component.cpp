#include "Component.h"
namespace dae
{
	Component::Component(GameObject* gameObject) : m_pGameObject{ gameObject }
	{
		m_pTransform = m_pGameObject->GetLocalTransform();
	}

	Component::~Component()
	{

	}

	void dae::Component::Update(float /*deltaTime*/)
	{
	}
	void Component::LateUpdate(float)
	{
	}
}