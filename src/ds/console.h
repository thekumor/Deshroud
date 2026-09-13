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

// Deshroud
#include <ds/controls.h>
#include <ds/vector.h>

namespace ds {

	class Console : public Control
	{
	public:
		Console(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		Console() = default;

		static LRESULT s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	private:
		std::streambuf* m_OldBuffer;
		std::ostringstream m_Out;
	};

}