#include "console.h"

namespace ds {

	Console::Console(Pos pos, Size size, const std::wstring& title, Control* parent)
		: Control(pos, size, title, parent)
	{
		HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));
		constexpr const wchar_t* c_ClassName = L"DsConsole";
		static WNDCLASSEXW s_Class = { 0 };

		if (s_Class.cbSize == 0)
		{
			s_Class.cbSize = sizeof(WNDCLASSEXW);
			s_Class.hInstance = instance;
			s_Class.lpszClassName = c_ClassName;
			s_Class.lpfnWndProc = Console::s_Procedure;
			s_Class.hCursor = LoadCursorW(instance, IDC_ARROW);

			RegisterClassExW(&s_Class);
		}

		m_Handle = CreateWindowExW(
			0,
			c_ClassName,
			title.c_str(),
			WS_OVERLAPPEDWINDOW | (parent ? WS_CHILD : 0),
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			size.x,
			size.y,
			parent ? parent->m_Handle : nullptr,
			nullptr,
			instance,
			0
		);

		ShowWindow(m_Handle, SW_SHOW);
	}

	LRESULT Console::s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				RECT rc;
				GetClientRect(handle, &rc);

				HDC dc = BeginPaint(handle, &ps);
				FillRect(dc, &rc, reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				EndPaint(handle, &ps);

				return 0;
			} break;

			case WM_DESTROY:
			{
				return 0;
			}

			case WM_CLOSE:
			{
				DestroyWindow(handle);
				return 0;
			}
		}

		return Window::s_Procedure(handle, msg, wp, lp);
	}

}