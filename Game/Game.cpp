#include "pch.h"
#include "Game.h"
#include "TimeManager.h"

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	hdcBack = ::CreateCompatibleDC(hdc); // hdc�� ȣȯ�Ǵ� DC�� ����
	_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom); // hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack); // DC�� BMP�� ����
	::DeleteObject(prev);

	TimeManager::GET_SINGLE()->Init();
}

void Game::Update()
{
	TimeManager::GET_SINGLE()->Update();

}

void Game::Render()
{
	unsigned __int32 fps = TimeManager::GET_SINGLE()->GetFPS();
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	{
		wstring str = ::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(hdcBack, 550, 10, str.c_str(), static_cast<__int32>(str.size()));
	}

	// Double Buffering
	::BitBlt(hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY); // ��Ʈ �� : ��� ����
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
