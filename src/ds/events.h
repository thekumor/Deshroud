/* ================================================================
*
*	Event management and calling.
*
*	#Authors: The Kumor
*
* ================================================================ */

#pragma once

// STL
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <functional>

// WinAPI
#include <windows.h>

#define TIC_EV_CAST_TYPE(var, type) *(type*)var
#define TIC_EV_CAST(var, data) *(decltype(var)*)data

namespace tic {

	typedef std::int32_t event_qualifier;

	enum class EventType : std::uint32_t
	{
		None = 0U,
		Resize,
		ButtonClicked,
		SceneClosed,
		SceneCreated,
		FontRecreated,
		Draw
	};

	using EventData = void*;

	class Event
	{
	public:
		Event(EventType type, EventData data = nullptr);
		Event() = default;

		inline EventType GetType() const { return m_Type; }
		inline EventData GetData() const { return m_Data; }

	private:
		EventType m_Type;
		EventData m_Data;
	};

	using EventCallback = std::function<std::int32_t(EventData)>;

	class EventListener
	{
	public:
		EventListener() = default;

		inline bool const IsValid() { return m_IsValid; }
		inline event_qualifier const GetQualifier() { return m_Qualifier; }
		void SetQualifier(event_qualifier q);
		void AddCallback(EventType type, EventCallback callback);
		void AcceptEvent(const Event& ev);
		void Invalidate();

	private:
		std::unordered_map<EventType, EventCallback> m_Callbacks;
		event_qualifier m_Qualifier;
		bool m_IsValid = true;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher() = default;

		bool AnnounceEvent(const Event& ev, event_qualifier q);
		void PinListener(EventListener* lst);
		void UnpinListener(EventListener* lst);
		void AnnounceEvent(const Event& ev);
		void AnnounceEventOmit(const Event& ev, event_qualifier q);
		void UnpinInvalidListeners();
		void PinValidListeners();

	private:
		std::vector<EventListener*> m_Listeners;
		std::vector<EventListener*> m_WaitingListeners;
	};

	class EventActive
	{
	public:
		EventActive() = default;

		inline EventDispatcher& GetDispatcher() { return m_Disp; }
		inline EventListener& GetListener() { return m_Listener; }
		void AddCallback(EventType type, EventCallback callback);

	private:
		EventDispatcher m_Disp;
		EventListener m_Listener;
	};

	extern EventDispatcher g_Dispatcher;

}