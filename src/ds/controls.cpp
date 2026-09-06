#include "controls.h"

namespace ds {

	Control::Control(Pos pos, Size size, const std::wstring& title, Control* parent)
		: m_Pos(pos), m_Size(size), m_Title(title), m_Parent(parent)
	{
	}

	LRESULT Control::s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		return DefWindowProcW(handle, msg, wp, lp);
	}

	Window::Window(Pos pos, Size size, const std::wstring& title, Control* parent)
		: Control(pos, size, title, parent)
	{
		HINSTANCE instance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));
		constexpr const wchar_t* c_ClassName = L"DsWindow";
		static WNDCLASSEXW s_Class = { 0 };

		if (s_Class.cbSize == 0)
		{
			s_Class.cbSize = sizeof(WNDCLASSEXW);
			s_Class.hInstance = instance;
			s_Class.lpszClassName = c_ClassName;
			s_Class.lpfnWndProc = Window::s_Procedure;
			s_Class.hCursor = LoadCursorW(instance, IDC_ARROW);

			RegisterClassExW(&s_Class);
		}

		Pos perfectPos = GetScreenCenter();
		perfectPos.x /= 2;
		perfectPos.y /= 2;
		perfectPos.x -= size.x / 2;
		perfectPos.y -= size.y / 2;

		m_Handle = CreateWindowExW(
			0,
			c_ClassName,
			title.c_str(),
			WS_OVERLAPPEDWINDOW | (parent ? WS_CHILD : 0),
			perfectPos.x,
			perfectPos.y,
			size.x,
			size.y,
			parent ? parent->m_Handle : nullptr,
			nullptr,
			instance,
			0
		);

		ShowWindow(m_Handle, SW_SHOW);
	}

	LRESULT Window::s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			} break;

			case WM_CLOSE:
			{
				DestroyWindow(handle);
			} break;

			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				RECT rc;
				GetClientRect(handle, &rc);

				HDC dc = BeginPaint(handle, &ps);
				FillRect(dc, &rc, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
				EndPaint(handle, &ps);
			} break;

			case WM_SIZE:
			{

			} break;
		}

		return Control::s_Procedure(handle, msg, wp, lp);
	}

	Pos GetScreenCenter()
	{
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		return { width, height };
	}

	Button::Button(Pos pos, Size size, const std::wstring& title, Control* parent)
		: Control(pos, size, title, parent)
	{
		m_Handle = CreateWindowExW(
			0,
			L"BUTTON",
			title.c_str(),
			WS_VISIBLE | (parent ? WS_CHILD : 0),
			pos.x,
			pos.y,
			size.x,
			size.y,
			parent ? parent->m_Handle : nullptr,
			nullptr,
			static_cast<HINSTANCE>(GetModuleHandleW(nullptr)),
			0
		);
	}

	Label::Label(Pos pos, Size size, const std::wstring& title, Control* parent)
	{
		m_Handle = CreateWindowExW(
			0,
			L"STATIC",
			title.c_str(),
			WS_VISIBLE | (parent ? WS_CHILD : 0),
			pos.x,
			pos.y,
			size.x,
			size.y,
			parent ? parent->m_Handle : nullptr,
			nullptr,
			static_cast<HINSTANCE>(GetModuleHandleW(nullptr)),
			0
		);
	}

	ComboBox::ComboBox(Pos pos, Size size, const std::wstring& title, Control* parent)
	{
		m_Handle = CreateWindowExW(
			0,
			L"COMBOBOX",
			title.c_str(),
			WS_VISIBLE | (parent ? WS_CHILD : 0) | CBS_DROPDOWN | CBS_HASSTRINGS,
			pos.x,
			pos.y,
			size.x,
			size.y,
			parent ? parent->m_Handle : nullptr,
			nullptr,
			static_cast<HINSTANCE>(GetModuleHandleW(nullptr)),
			0
		);
	}

	void ComboBox::AddEntry(const std::wstring& entry)
	{
		SendMessageW(m_Handle, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(entry.c_str()));
		SendMessageW(m_Handle, CB_SETCURSEL, 0, 0);
	}

	void ComboBox::AddEntries(const std::vector<std::wstring>& entries)
	{
		for (auto& k : entries)
			SendMessageW(m_Handle, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(k.c_str()));

		SendMessageW(m_Handle, CB_SETCURSEL, 0, 0);
	}

	Numeric::Numeric(Pos pos, Size size, const std::wstring& title, Control* parent)
	{
		m_Handle = CreateWindowExW(
			0,
			L"NUMERIC",
			title.c_str(),
			WS_VISIBLE | (parent ? WS_CHILD : 0),
			pos.x,
			pos.y,
			size.x,
			size.y,
			parent ? parent->m_Handle : nullptr,
			nullptr,
			static_cast<HINSTANCE>(GetModuleHandleW(nullptr)),
			0
		);
	}

}