#pragma once

// STL
#include <cstdint>
#include <string>

// WinAPI
#include <windows.h>

// Deshroud
#include <ds/vector.h>

#define DS_HAS_BITS(x, y) (x & y) == y

namespace ds {
	enum FontStyle : std::int16_t
	{
		Default = DS_BIT(0),
		Bold = DS_BIT(1),
		Italic = DS_BIT(2),
		Underline = DS_BIT(3),
		Strikeout = DS_BIT(4),
	};
	using FontStyles = std::int16_t;

	class Font
	{
	public:
		Font(const std::wstring& faceName, std::int32_t size, FontStyles style);
		Font() = default;

		friend class Control;

	private:
		HFONT m_Handle;
		std::wstring m_FaceName;
		std::int32_t m_Size;
		FontStyles m_Styles;
	};
}

//[[nodiscard]] ds::FontStyles operator&(ds::FontStyles styles, ds::FontStyle style) noexcept;
//[[nodiscard]] ds::FontStyles operator&(ds::FontStyle style, ds::FontStyles styles) noexcept;
//[[nodiscard]] ds::FontStyles operator&(ds::FontStyle style1, ds::FontStyle style2) noexcept;
//
//[[nodiscard]] ds::FontStyles operator|(ds::FontStyle style, ds::FontStyles styles) noexcept;
//[[nodiscard]] ds::FontStyles operator|(ds::FontStyles styles, ds::FontStyle style) noexcept;
//[[nodiscard]] ds::FontStyles operator|(ds::FontStyle style1, ds::FontStyle style2) noexcept;
//
//[[nodiscard]] bool operator==(ds::FontStyles styles, ds::FontStyle style) noexcept;
//[[nodiscard]] bool operator==(ds::FontStyle style, ds::FontStyles styles) noexcept;