#include "pch.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Pos pos, const wstring& str)
{
	::TextOut(hdc,
		static_cast<__int32>(pos.x),
		static_cast<__int32>(pos.y),
		str.c_str(),
		static_cast<__int32>(str.size()));
}

void Utils::DrawTextColored(HDC hdc, Pos pos, const wstring& str, HFONT font, COLORREF color)
{
	int oldDC = ::SaveDC(hdc);
	SelectObject(hdc, font);
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);
	Utils::DrawText(hdc, pos, str);
	::RestoreDC(hdc, oldDC);
}

void Utils::DrawTextTransparent(HDC hdc, Pos pos, const wstring& str)
{
	int oldDC = ::SaveDC(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::SetTextColor(hdc, RGB(0, 0, 0));
	::TextOut(hdc,
		static_cast<__int32>(pos.x),
		static_cast<__int32>(pos.y),
		str.c_str(),
		static_cast<__int32>(str.size()));
	::RestoreDC(hdc, oldDC);
}

void Utils::DrawTextMultiline(HDC hdc, const wstring& str, const RECT& rect, HFONT font, COLORREF color)
{
	HFONT oldFont = (HFONT)::SelectObject(hdc, font);
	::SetTextColor(hdc, color);
	::SetBkMode(hdc, TRANSPARENT);

	::DrawTextW(hdc, str.c_str(), -1, const_cast<RECT*>(&rect),
		DT_LEFT | DT_TOP | DT_WORDBREAK);

	::SelectObject(hdc, oldFont);
}

void Utils::DrawRect(HDC hdc, Pos pos, __int32 w, __int32 h)
{
	::Rectangle(hdc,
		static_cast<__int32>(pos.x - static_cast<float>(w / 2)),
		static_cast<__int32>(pos.y - static_cast<float>(h / 2)),
		static_cast<__int32>(pos.x + static_cast<float>(w / 2)),
		static_cast<__int32>(pos.y + static_cast<float>(h / 2)));
}

void Utils::DrawRoundRectColored(HDC hdc, Pos pos, __int32 w, __int32 h, COLORREF color, COLORREF borderColor)
{
	HBRUSH hbrush = CreateSolidBrush(color);

	HPEN hPen = CreatePen(PS_SOLID, 1, borderColor);

	RECT r = { pos.x, pos.y, pos.x + w, pos.y + h };

	HGDIOBJ oldBrush = SelectObject(hdc, hbrush);
	HGDIOBJ oldPen = SelectObject(hdc, hPen);

	RoundRect(hdc, pos.x, pos.y, pos.x + w, pos.y + h, 10.f, 10.f);

	// 리소스 정리
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(hbrush);
	DeleteObject(hPen);
}

void Utils::DrawRectColored(HDC hdc, Pos pos, __int32 w, __int32 h, COLORREF color, COLORREF borderColor)
{
	HBRUSH hbrush = CreateSolidBrush(color);

	HPEN hPen = CreatePen(PS_SOLID, 1, borderColor);

	RECT r = { pos.x, pos.y, pos.x + w, pos.y + h };

	HGDIOBJ oldBrush = SelectObject(hdc, hbrush);
	HGDIOBJ oldPen = SelectObject(hdc, hPen);

	DrawRect(hdc, pos, pos.x + w, pos.y + h);

	// 리소스 정리
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(hbrush);
	DeleteObject(hPen);
}

void Utils::DrawRectTransparent(HDC hdc, Pos pos, int width, int height, COLORREF color, BYTE alpha)
{
	// 중심 기준 사각형 좌표 계산
	RECT rect = {
		static_cast<LONG>(pos.x - width / 2),
		static_cast<LONG>(pos.y - height / 2),
		static_cast<LONG>(pos.x + width / 2),
		static_cast<LONG>(pos.y + height / 2)
	};

	// 메모리 DC와 비트맵 생성
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP bmp = CreateCompatibleBitmap(hdc, width, height);
	HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, bmp);

	// 브러시 생성 후 색상 채우기
	HBRUSH brush = CreateSolidBrush(color);
	RECT fillRect = { 0, 0, width, height };
	FillRect(memDC, &fillRect, brush);
	DeleteObject(brush);

	// 반투명 블렌드 설정
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = alpha;
	blend.AlphaFormat = 0;

	// 화면에 알파 블렌딩 출력
	AlphaBlend(hdc,
		rect.left, rect.top,
		width, height,
		memDC,
		0, 0,
		width, height,
		blend);

	// 리소스 정리
	SelectObject(memDC, oldBmp);
	DeleteObject(bmp);
	DeleteDC(memDC);
}


void Utils::DrawCircle(HDC hdc, Pos pos, __int32 radius)
{
	::Ellipse(hdc,
		static_cast<__int32>(pos.x - radius),
		static_cast<__int32>(pos.y - radius),
		static_cast<__int32>(pos.x + radius),
		static_cast<__int32>(pos.y + radius));
}

void Utils::DrawLine(HDC hdc, Pos from, Pos to)
{
	::MoveToEx(hdc, static_cast<__int32>(from.x), static_cast<__int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<__int32>(to.x), static_cast<__int32>(to.y));
}

void Utils::DrawLineColored(HDC hdc, Pos from, Pos to, COLORREF color)
{
	HPEN pen = ::CreatePen(PS_SOLID, 1, color);
	HPEN oldPen = (HPEN)::SelectObject(hdc, (HGDIOBJ)pen);

	::MoveToEx(hdc, static_cast<__int32>(from.x), static_cast<__int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<__int32>(to.x), static_cast<__int32>(to.y));

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

void Utils::ReadBmp(const wstring& path)
{
	FILE* fp = nullptr;

	if (::_wfopen_s(&fp, path.c_str(), L"rb") != 0)
		return;

	BITMAPFILEHEADER fileHeader = {};
	::fread_s(&fileHeader, sizeof(fileHeader), sizeof(fileHeader), 1, fp);

	BITMAPINFOHEADER infoHeader = {};
	::fread_s(&infoHeader, sizeof(infoHeader), sizeof(infoHeader), 1, fp);

	__int32 imgSize = infoHeader.biWidth * infoHeader.biHeight * 4;
	char* buffer = (char*)::malloc(imgSize);
	fread_s(buffer, imgSize, imgSize, 1, fp);

	//::free(buffer);
}

Vec2 Utils::FromAngleDeg(float deg)
{
	float rad = deg * PI / 180.f;
	Vec2 dir(cosf(rad), sinf(rad));
	dir.Normalize(); 
	return dir;
}
