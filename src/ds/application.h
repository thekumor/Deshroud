/* ================================================================
*
*	Contains main loop of the app.
*
*	#Authors: The Kumor
*
* ================================================================ */

#pragma once

// STL
#include <cstdlib>
#include <iostream>
#include <sstream>

// WinAPI
#include <windows.h>

// Deshroud
#include <ds/controls.h>
#include <ds/console.h>

namespace ds {

	class Application
	{
	public:
		Application() = default;

		int Run();

	private:
		
	};

}