#include "application.h"

#define DS_TEMP_CMD "nvidia-smi --query-gpu=temperature.gpu"

namespace ds {

	int Application::Run()
	{
		Window window(Pos(0, 0), Size(900, 700), L"Deshroud UI");
		Console console(Pos(0, 0), Size(640, 480), L"Deshroud Console");

		std::cout << "Hello there! :)";

		std::system(DS_TEMP_CMD);

		std::wstring tempString(std::wstring(L"Temperature: 35") + L'\u00B0' + std::wstring(L"C"));
		Label currentTemperature(Pos(50, 50), Size(120, 32), tempString, &window);
		
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