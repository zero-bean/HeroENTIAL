#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class Utils
{
public:
	static void DrawText(HDC hdc, Pos pos, const wstring& str);
	
	static void DrawTextMultiline(HDC hdc, const wstring& str, const RECT& rect, HFONT font, COLORREF color);

	static void DrawRect(HDC hdc, Pos pos, __int32 w, __int32 h);

	static void DrawRectColored(HDC hdc, Pos pos, __int32 w, __int32 h, COLORREF color, COLORREF borderColor);

	static void DrawCircle(HDC hdc, Pos pos, __int32 radius);

	static void DrawLine(HDC hdc, Pos from, Pos to);

	static void DrawLineColored(HDC hdc, Pos from, Pos to, COLORREF color);

	static void ReadBmp(const wstring& path);
};

