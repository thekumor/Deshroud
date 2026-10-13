#include "application.h"

#define DS_TEMP_CMD "nvidia-smi --query-gpu=temperature.gpu"

namespace ds {

	int Application::Run()
	{
		Window window(Pos(0, 0), Size(900, 700), L"Deshroud UI");
		Console console(Pos(0, 0), Size(640, 480), L"Deshroud Console");

		Timer test(1000, [](void* data) -> std::int32_t
		{
			MessageBoxA(nullptr, "I work!", "Timers", IDOK);
			return 0;
		});

		MSG msg = {};
		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return EXIT_SUCCESS;
	}

}