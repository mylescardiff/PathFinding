#pragma once
/** \file EventDispatcher.h */
// Created by Myles Cardiff

#include <unordered_map>
#include <functional>
#include <vector>
#include <Logic/Events/IEvent.h>
#include <Common.h>

//! \namespace Sloth Engine
namespace slth
{
/** \class EventDispatcher */
/** Manager class that stores handles all events */
class EventDispatcher
{
public:
	
	using EventListener = std::function<void(IEvent*)>;

	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	EventDispatcher() {};

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //

	SLTH_API size_t AddEventListener(EventType type, EventListener listener);

	SLTH_API void RemoveEventListener(EventType type, size_t index);

	SLTH_API void QueueEvent(IEvent* pEvent);
	
	SLTH_API void FireEvent(IEvent* pEvent);
	
	/** Only call this from IGameLayer::Update or a child of that class */
	SLTH_API void ProcessEvents();

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	using EventListeners = std::vector<EventListener>;
	
	std::unordered_map<EventType, EventListeners> m_listenerMap;

	std::unordered_map<int, int> m_test;
	std::vector<IEvent*> m_queue;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

	

	// sigleton deletes for making this not copyable
	EventDispatcher(const EventDispatcher& other) = delete;
	EventDispatcher& operator=(const EventDispatcher& other) = delete;
	EventDispatcher(EventDispatcher&& other) = delete;
	EventDispatcher& operator=(EventDispatcher&& other) = delete;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}