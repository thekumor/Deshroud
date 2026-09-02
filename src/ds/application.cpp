#include "application.h"

namespace ds {

	int Application::Run()
	{
		Window window(Pos(0, 0), Size(900, 700), L"Deshroud");
		ComboBox test(Pos(30, 30), Size(120, 120), L"String", &window);

		test.AddEntry(L"One");
		test.AddEntry(L"Two");
		test.AddEntry(L"Three");

		MSG msg = {};

		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return EXIT_SUCCESS;
	}

}