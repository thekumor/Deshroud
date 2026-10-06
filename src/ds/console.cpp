#include "console.h"

#define DS_OUT_BUFF 0
#define DS_ERR_BUFF 1
#define DS_LOG_BUFF 2

namespace ds {

	Console::Console(Pos pos, Size size, const std::wstring& title, Control* parent)
		: Control(pos, size, title, parent)
	{	
		// std::cout
		m_Buffers[DS_OUT_BUFF] = BufferInfo(std::cout.rdbuf(), BufferType::Out);
		std::cout.rdbuf(m_Buffers[DS_OUT_BUFF].Stream.rdbuf());

		// std::cerr
		m_Buffers[DS_ERR_BUFF] = BufferInfo(std::cerr.rdbuf(), BufferType::Error);
		std::cerr.rdbuf(m_Buffers[DS_ERR_BUFF].Stream.rdbuf());

		// std::clog
		m_Buffers[DS_LOG_BUFF] = BufferInfo(std::clog.rdbuf(), BufferType::Log);
		std::clog.rdbuf(m_Buffers[DS_LOG_BUFF].Stream.rdbuf());

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
				
				std::int32_t prevBkMode = SetBkMode(dc, TRANSPARENT);

				BufferInfo* outBuffer = &self->m_Buffers[DS_OUT_BUFF];
				BufferInfo* errorBuffer = &self->m_Buffers[DS_ERR_BUFF];
				BufferInfo* logBuffer = &self->m_Buffers[DS_LOG_BUFF];

				COLORREF prevColor = GetTextColor(dc);
#if 0
				if (outBuffer)
				{
					SetTextColor(dc, RGB(255, 255, 255));
					DrawTextA(dc, outBuffer->Stream.str().c_str(), -1, &rc, DT_LEFT | DT_NOCLIP | DT_TOP);
				}
				if (errorBuffer)
				{
					SetTextColor(dc, RGB(255, 0, 0));
					DrawTextA(dc, errorBuffer->Stream.str().c_str(), -1, &rc, DT_LEFT | DT_NOCLIP | DT_TOP);
				}
				if (logBuffer)
				{
					SetTextColor(dc, RGB(240, 150, 90));
					DrawTextA(dc, logBuffer->Stream.str().c_str(), -1, &rc, DT_LEFT | DT_NOCLIP | DT_TOP);
				}
#endif
				std::int32_t yOffset = 0;
				for (auto& k : self->m_Messages)
				{
					static COLORREF s_BadColor = RGB(255, 0, 0);
					static COLORREF s_WarningColor = RGB(240, 240, 0);
					static COLORREF s_NormalColor = RGB(255, 255, 255);

					COLORREF color = s_NormalColor;

					switch (k.Type)
					{
						case MessageType::Error:
						{
							color = s_BadColor;
						} break;

						case MessageType::Warning:
						{
							color = s_WarningColor;
						} break;

						case MessageType::Info:
						{
							color = s_NormalColor;
						} break;
					}

					SetTextColor(dc, color);
					const std::string& str = k.Time.ToString().substr(0, k.Time.ToString().size() - 1) + ": " + k.Content + "\n";
					DrawTextA(dc, str.c_str(), -1, &rc, DT_LEFT | DT_NOCLIP | DT_TOP);

					// Technically, we could use DrawTextA to get text height/position but
					// it works as well.
					yOffset += 20;

					rc.top += yOffset - 20 * (yOffset - 20) / 20;
					rc.bottom += yOffset - 20 * (yOffset - 20) / 20;
				}

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

	BufferInfo* Console::GetBuffer(BufferType type)
	{
		for (auto& k : m_Buffers)
			if (k.Type == type)
				return &k;

		return nullptr;
	}

	void Console::AddMessage(const Message& msg)
	{
		m_Messages.push_back(msg);
		// Force redraw
		InvalidateRect(m_Handle, nullptr, TRUE);
	}

	BufferInfo::BufferInfo(std::streambuf* old, BufferType type)
		: OldBuffer(old), Type(type)
	{}

	Timestamp::Timestamp()
	{
		m_Epoch = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	std::string Timestamp::ToString() const
	{
		char buffer[256];
		ctime_s(buffer, 256, &m_Epoch);

		return std::string(buffer);
	}

	Message::Message(const std::string& string, MessageType type)
		: Content(string), Type(type)
	{
	}

}