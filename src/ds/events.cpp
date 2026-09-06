#include "events.h"

namespace tic {

	Event::Event(EventType type, EventData data)
		: m_Type(type), m_Data(data)
	{}

	void EventDispatcher::PinListener(EventListener* lst)
	{
		m_WaitingListeners.push_back(lst);
	}

	void EventDispatcher::UnpinListener(EventListener* lst)
	{
		for (std::vector<EventListener*>::iterator it = m_Listeners.begin(); it != m_Listeners.end(); it++)
			if (*it == lst)
			{
				m_Listeners.erase(it);
				return;
			}
	}

	void EventDispatcher::AnnounceEvent(const Event& ev)
	{
		for (auto& k : m_Listeners)
			k->AcceptEvent(ev);
	}

	bool EventDispatcher::AnnounceEvent(const Event& ev, event_qualifier id)
	{
		for (auto& k : m_Listeners)
			if (k->GetQualifier() == id)
			{
				k->AcceptEvent(ev);
				return true;
			}

		return false;
	}

	void EventDispatcher::AnnounceEventOmit(const Event& ev, event_qualifier q)
	{
		for (auto& k : m_Listeners)
			if (k->GetQualifier() != q)
				k->AcceptEvent(ev);
	}

	void EventDispatcher::UnpinInvalidListeners()
	{
		for (std::int32_t i = 0 ; i < m_Listeners.size(); i++)
		{
			if (!m_Listeners[i]->IsValid())
			{
				m_Listeners.erase(m_Listeners.begin() + i);
				i--;
			}
		}
	}

	void EventDispatcher::PinValidListeners()
	{
		m_Listeners.reserve(m_Listeners.size() + m_WaitingListeners.size() + 1);
		for (auto& k : m_WaitingListeners)
		{
			m_Listeners.push_back(k);
		}

		m_WaitingListeners.clear();
	}

	void EventListener::SetQualifier(event_qualifier q)
	{
		m_Qualifier = q;
	}

	void EventListener::AddCallback(EventType type, EventCallback callback)
	{
		m_Callbacks[type] = callback;
	}

	void EventListener::AcceptEvent(const Event& ev)
	{
		auto it = m_Callbacks.find(ev.GetType());

		if (it != m_Callbacks.end())
			it->second(ev.GetData());
	}

	void EventListener::Invalidate()
	{
		m_IsValid = false;
	}

	void EventActive::AddCallback(EventType type, EventCallback callback)
	{
		GetListener().AddCallback(type, callback);
	}

}