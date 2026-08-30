#include "application.h"

namespace ds {

	int Application::Run()
	{
		Window window;

		MSG msg = {};

		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return EXIT_SUCCESS;
	}

}