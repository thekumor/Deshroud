#include "console.h"

namespace ds {

	Console::Console(Pos pos, Size size, const std::wstring& title, Control* parent)
		: Control(pos, size, title, parent)
	{
		m_OldBuffer = std::cout.rdbuf();
		std::cout.rdbuf(m_Out.rdbuf());

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
		SetWindowLongPtrW(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	LRESULT Console::s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_PAINT:
			{
				Console* self = reinterpret_cast<Console*>(GetWindowLongPtr(handle, GWLP_USERDATA));

				if (!self)
					return 0;

				PAINTSTRUCT ps;
				RECT rc;
				GetClientRect(handle, &rc);

				HDC dc = BeginPaint(handle, &ps);
				FillRect(dc, &rc, reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
				
				COLORREF prevColor = SetTextColor(dc, RGB(255, 255, 255));
				std::int32_t prevBkMode = SetBkMode(dc, TRANSPARENT);

				DrawTextA(dc, self->m_Out.str().c_str(), -1, &rc, DT_LEFT | DT_NOCLIP | DT_TOP);
				
				SetTextColor(dc, prevColor);
				SetBkMode(dc, prevBkMode);

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