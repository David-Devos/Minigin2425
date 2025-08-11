#pragma once
#include "Observer.h"
#include "Component.h"
namespace dae
{

	class PlayerObserver : public Observer, public Component
	{
	public:
		PlayerObserver(GameObject* gameObject);
		~PlayerObserver();
		void Notify(const BaseEvent& event, GameObject* actor) override;

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;
	};
}

