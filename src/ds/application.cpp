#include "application.h"

constexpr const char* c_TempCmd = "nvidia-smi --query-gpu=temperature.gpu";

namespace ds
{
	int Application::Run()
	{
		Window window(Pos(0, 0), Size(900, 700), L"Deshroud UI");
		Console console(Pos(0, 0), Size(640, 480), L"Deshroud Console");

		Font arial(L"Arial", 32, FontStyle::Default);

		Label title(Pos(64, 64), Size(128, 64), L"Deshroud", dynamic_cast<Control*>(&window));
		Button cancel(Pos(200, 500), Size(128, 64), L"Cancel", dynamic_cast<Control*>(&window));
		Button apply(Pos(400, 500), Size(128, 64), L"Apply", dynamic_cast<Control*>(&window));

		title.SetFont(arial);

		MSG msg = {};
		while (GetMessageA(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

		return EXIT_SUCCESS;
	}
}