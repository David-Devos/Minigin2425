#pragma once
#include "Component.h"
#include "GameObject.h"
namespace dae
{
	struct EventArg {
		int i = 0;
		Component* comp;
		GameObject* go;
	};

	struct BaseEvent
	{
		BaseEvent() = default;
		virtual ~BaseEvent() = default;
		static const uint8_t MAX_ARGS = 8;
		EventArg args[MAX_ARGS] = {};

	};

	struct OnCollision final : public BaseEvent
	{

	};
}