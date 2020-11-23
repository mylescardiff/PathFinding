#include "EventDispatcher.h"
#include <Logger/Logger.h>

using slth::EventDispatcher;



size_t slth::EventDispatcher::AddEventListener(EventType type, EventListener listener)
{
	auto& listeners = m_listenerMap[type];
	for (size_t index = 0; index < listeners.size(); ++index)
	{
		if (listeners[index] == nullptr)
		{
			listeners[index] = listener;
			return index;
		}
	}
	listeners.emplace_back(listener);
	return listeners.size() - 1;
}

void slth::EventDispatcher::RemoveEventListener(EventType type, size_t index)
{
	auto listenerItr = m_listenerMap.find(type);

	if (listenerItr == m_listenerMap.end())
	{
		_LOGW("Attempt to remove event that no listener exists for.");
		return;
	}

	if (index < listenerItr->second.size())
	{
		listenerItr->second[index] = nullptr;
	}
	else
	{
		_LOGE("Remove listener attempted at invalid index.");
	}
}

void slth::EventDispatcher::QueueEvent(IEvent * pEvent)
{
	m_queue.emplace_back(pEvent); // std::move(pEvent) would be the argument here
}

void slth::EventDispatcher::FireEvent(IEvent* pEvent)
{
	auto listenerItr = m_listenerMap.find(pEvent->GetType());

	for (auto& listener : listenerItr->second)
	{
		if (listener != nullptr)
		{
			// call the std:: function, and pass the event poitner to it
			listener(pEvent);
		}
	}
}

void slth::EventDispatcher::ProcessEvents()
{
	// we're doing this so that we can process this queue without being interupted by new ones being added during the process
	auto queue = std::move(m_queue); 
	for (auto& pEvent : queue)
	{
		auto& listeners = m_listenerMap[pEvent->GetType()];
		for (auto& listener : listeners)
		{
			if (listener != nullptr)
			{
				// call the std:: function, and pass the event poitner to it
				listener(pEvent);
			}
		}
	}
}


