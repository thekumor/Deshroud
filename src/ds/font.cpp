#include "font.h"

namespace ds
{
	Font::Font(const std::wstring& faceName, std::int32_t size, FontStyles style)
		: m_FaceName(faceName), m_Size(size), m_Styles(style)
	{
		m_Handle = CreateFontW(
			size,
			0,
			0,
			0,
			DS_HAS_BITS(style, FontStyle::Bold) ? FW_BOLD : FW_DONTCARE,
			DS_HAS_BITS(style, FontStyle::Italic) ? TRUE : FALSE,
			DS_HAS_BITS(style, FontStyle::Underline) ? TRUE : FALSE,
			DS_HAS_BITS(style, FontStyle::Strikeout) ? TRUE : FALSE,
			DEFAULT_CHARSET,
			OUT_TT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY,
			FF_DONTCARE,
			faceName.c_str()
		);
	}
}

//ds::FontStyles operator&(ds::FontStyles styles, ds::FontStyle style) noexcept
//{
//	return ds::FontStyles(styles & static_cast<ds::FontStyles>(style));
//}
//
//ds::FontStyles operator&(ds::FontStyle style, ds::FontStyles styles) noexcept
//{
//	return operator&(styles, style);
//}
//
//ds::FontStyles operator&(ds::FontStyle style1, ds::FontStyle style2) noexcept
//{
//	return ds::FontStyles(static_cast<ds::FontStyles>(style1) & static_cast<ds::FontStyles>(style2));
//}
//
//ds::FontStyles operator|(ds::FontStyles styles, ds::FontStyle style) noexcept
//{
//	return ds::FontStyles(styles | static_cast<ds::FontStyles>(style));
//}
//
//ds::FontStyles operator|(ds::FontStyle style1, ds::FontStyle style2) noexcept
//{
//	return ds::FontStyles(static_cast<ds::FontStyles>(style1) | static_cast<ds::FontStyles>(style2));
//}
//
//bool operator==(ds::FontStyles styles, ds::FontStyle style) noexcept
//{
//	return styles == static_cast<ds::FontStyles>(style);
//}
//
//bool operator==(ds::FontStyle style, ds::FontStyles styles) noexcept
//{
//	return operator==(styles, style);
//}
//
//ds::FontStyles operator|(ds::FontStyle style, ds::FontStyles styles) noexcept
//{
//	return operator|(style, styles);
//}