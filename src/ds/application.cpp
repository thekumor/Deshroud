#include "application.h"

namespace ds {

	int Application::Run()
	{
		Window window(Pos(0, 0), Size(900, 700), L"Deshroud");
		Label currentTemperature(Pos(50, 50), Size(120, 32), L"Temperature: 35*C", &window);
		ComboBox test(Pos(30, 30), Size(120, 120), L"String", &window);

		test.AddEntries({ L"One", L"Two", L"Three", L"Four" });

		MSG msg = {};

		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return EXIT_SUCCESS;
	}

}