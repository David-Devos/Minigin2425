#pragma once
#include <cstdint>
struct EventArg {};
enum class EventId {
	// Game event ids here
};
struct Event {
	const EventId id;
	static const uint8_t MAX_ARGS = 8;
	uint8_t nbArgs = 0;
	EventArg args[MAX_ARGS] = {};
	explicit Event(EventId _id) : id{ _id } {}
};
