/* ================================================================
*
*	Console for logging, debugging.
*
*	#Authors: The Kumor
*
* ================================================================ */

// STL
#include <iostream>
#include <sstream>
#include <cstdint>
#include <array>

// Deshroud
#include <ds/controls.h>
#include <ds/vector.h>

namespace ds {

	enum class BufferType : std::int16_t
	{
		Invalid = 0,
		Out,
		Error,
		Log
	};

	struct BufferInfo
	{
		BufferInfo(std::streambuf* old, BufferType type);
		BufferInfo() = default;

		std::streambuf* OldBuffer;
		std::ostringstream Stream;
		BufferType Type;
	};

	class Console : public Control
	{
	public:
		Console(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		Console() = default;

		static LRESULT s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

		BufferInfo* GetBuffer(BufferType type);

	private:
		std::array<BufferInfo, 3> m_Buffers;
	};

}