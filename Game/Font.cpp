#include "pch.h"
#include "Font.h"

Font::Font(const wstring& fontName, int size)
{
	// https://learn.microsoft.com/ko-kr/windows/win32/api/wingdi/nf-wingdi-createfontw
	_hFont = CreateFont(
		size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontName.c_str()
	);

	_size = size;
}

Font::~Font()
{
	if (_hFont)
		DeleteObject(_hFont);
}