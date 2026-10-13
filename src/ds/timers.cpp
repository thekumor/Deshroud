#include "timers.h"

namespace ds {

	static std::unordered_map<std::int32_t, Timer*> s_Timers = {};

	Timer::Timer(std::int32_t delay, EventCallback callback)
		: m_Delay(delay), m_Callback(callback)
	{
		m_Id = SetTimer(nullptr, 0, delay, s_Callback);
		s_Timers[m_Id] = this;
	}

	void Timer::s_Callback(HWND handle, UINT msg, UINT_PTR id, DWORD miliseconds)
	{
		auto it = s_Timers.find(id);
		
		if (it != s_Timers.end())
		{
			it->second->m_Callback(&msg);
		}
	}

	void Timer::SetCallback(EventCallback callback)
	{
		m_Callback = callback;
	}

}