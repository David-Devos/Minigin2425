#pragma once
#include <cstdint>
#include "Component.h"
#include "BaseEvent.h"
namespace dae
{

	struct PlayerDiedEvent : public BaseEvent {};
	struct HealthChangedEvent : public BaseEvent {};
	struct PelletEatenEvent : public BaseEvent {};
}
