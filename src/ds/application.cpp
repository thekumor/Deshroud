#include "application.h"

#define DS_TEMP_CMD "nvidia-smi --query-gpu=temperature.gpu"

namespace ds {

	int Application::Run()
	{
		Window window(Pos(0, 0), Size(900, 700), L"Deshroud UI");
		Console console(Pos(0, 0), Size(640, 480), L"Deshroud Console");

		console.AddMessage(Message("Hello there! 1", MessageType::Error));
		console.AddMessage(Message("Hello there! 2", MessageType::Warning));
		console.AddMessage(Message("Hello there! 3", MessageType::Info));
		console.AddMessage(Message("Hello there! 4", MessageType::Info));

#if 0
		FILE* pipe = _popen(DS_TEMP_CMD, "rt");
		char buffer[17];
		char buffer1[5];
		fgets(buffer, 17, pipe);
		fgets(buffer1, 5, pipe);
		_pclose(pipe);

		std::wstring temperatureWstring = std::to_wstring(std::atoi(buffer1));

		Label currentTemperature(Pos(50, 50), Size(120, 32), std::wstring(L"Temperature: ") + temperatureWstring + L'\u00B0' + std::wstring(L"C"), &window);

#endif
		Timer test(1 * 1000, [](void* data) -> std::int32_t
			{
				exit(1);
			}, dynamic_cast<Control*>(&window));

		MSG msg = {};
		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return EXIT_SUCCESS;
	}

}