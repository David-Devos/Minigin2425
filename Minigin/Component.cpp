#include "Component.h"
namespace dae
{
	Component::Component(GameObject* gameObject) : m_pGameObject{ gameObject }
	{
		m_pTransform = m_pGameObject->GetTransform();
	}

	Component::~Component()
	{

	}

	void dae::Component::Update(float /*deltaTime*/)
	{
	}
}