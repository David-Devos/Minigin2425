#pragma once
#include "Observer.h"
#include "Component.h"
namespace dae
{
	class PelletObserver : public Observer, public Component
	{
	public:
		PelletObserver(GameObject* gameObject);
		void Notify(const Event& event, GameObject* actor) override;

		virtual void Update(float deltaTime) override;
		virtual void Render() const override;
	};
}



