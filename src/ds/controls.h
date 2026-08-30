/* ================================================================
*
*	Contains all controls used in this app.
*
*	#Authors: The Kumor
*
* ================================================================ */

#pragma once

// WinAPI
#include <windows.h>

namespace ds {

	class Control
	{
	public:
		Control() = default;

	protected:
		HWND m_Handle;
	};

	class Window : public Control
	{
	public:
		Window() = default;

	private:

	};

	class Button : public Control
	{
	public:
		Button() = default;
	};

}