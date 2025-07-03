#include "pch.h"
#include "UI.h"

UI::UI()
{

}

UI::~UI()
{

}

void UI::BeginPlay()
{

}

void UI::Tick()
{
	if (!GetEnabled())
		return;
}

void UI::Render(HDC hdc)
{
	if (!GetVisible())
		return;
}

RECT UI::GetRect()
{
	RECT rect =
	{
		_pos.x - _size.x / 2,
		_pos.y - _size.y / 2,
		_pos.x + _size.x / 2,
		_pos.y + _size.y / 2
	};

	return rect;
}

bool UI::IsMouseInRect()
{
	RECT rect = GetRect();

	POINT mousePos = InputManager::GET_SINGLE()->GetMousePos();

	//return ::PtInRect(&rect, mousePos);
	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}