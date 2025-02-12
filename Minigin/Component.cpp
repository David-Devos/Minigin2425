#include "Component.h"
namespace dae
{
	Component::Component(std::shared_ptr<GameObject> gameObject) : m_pGameObject{ gameObject }
	{
		m_pTransform = m_pGameObject->GetTransform();
	}

	void dae::Component::Update(float /*deltaTime*/)
	{
	}
}