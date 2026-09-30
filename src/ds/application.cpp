#include "application.h"

#define DS_TEMP_CMD "nvidia-smi --query-gpu=temperature.gpu"

namespace ds {

	int Application::Run()
	{
		Window window(Pos(0, 0), Size(900, 700), L"Deshroud UI");
		Console console(Pos(0, 0), Size(640, 480), L"Deshroud Console");

		console.AddMessage("Hello there!");
		Label currentTemperature(Pos(50, 50), Size(120, 32), std::wstring(L"Temperature: 35") + L'\u00B0' + std::wstring(L"C"), &window);

		FILE* pipe = _popen(DS_TEMP_CMD, "rt");
		char buffer[17];
		char buffer1[5];
		fgets(buffer, 17, pipe);
		fgets(buffer1, 5, pipe);
		_pclose(pipe);

		MSG msg = {};

		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return EXIT_SUCCESS;
	}

}