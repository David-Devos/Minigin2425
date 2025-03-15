#pragma once
#include "Observer.h"
#include "Component.h"
namespace dae
{
	class HealthObserver : public Observer, public Component
	{
	public:
		HealthObserver(GameObject* gameObject);
		void Notify(const Event& event, GameObject* actor) override;

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;
	};
}

