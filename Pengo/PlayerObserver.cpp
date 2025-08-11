#include "PlayerObserver.h"
#include "ServiceLocator.h"
#include "ColliderManager.h"
#include "Event.h"

namespace dae
{

	PlayerObserver::PlayerObserver(GameObject* gameObject)
		: Component(gameObject)
	{
	}
	PlayerObserver::~PlayerObserver()
	{
		int tin = 0;
		++tin;
	}
	void PlayerObserver::Notify(const BaseEvent& event, GameObject* go)
	{
		if (typeid(event) == typeid(OnCollision))
		{
			if (event.args->go->GetTag() == "Player")
			{

				event.args->go->SetMarkedForDeath();
			}
			else if (go->GetTag() == "Player")
			{
				go->SetMarkedForDeath();

			}
		}
	}

	void PlayerObserver::Update(float)
	{
		ServiceLocator::GetColliderManager().Update();
	}

	void PlayerObserver::Render() const
	{
	}
}
