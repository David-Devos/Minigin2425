#pragma once
#include "BaseEvent.h"
#include "GameObject.h"
namespace dae
{
	struct Event;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const BaseEvent& event, GameObject* actor) = 0;
	private:
	};
}

