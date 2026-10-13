/* ================================================================
*
*	Contains the Timer class, which is used to create timers that
*	can trigger events after a specified delay.
*
*	#Authors: The Kumor
*
* ================================================================ */

#pragma once

// STL
#include <vector>
#include <cstdint>
#include <unordered_map>

// Deshroud
#include <ds/events.h>

namespace ds {

	class Timer
	{
	public:
		Timer(std::int32_t delay, EventCallback callback);
		Timer() = default;

		static void s_Callback(HWND handle, UINT msg, UINT_PTR id, DWORD miliseconds);

		void SetCallback(EventCallback callback);

	private:
		EventCallback m_Callback;
		std::int32_t m_Delay, m_Id;
	};

}