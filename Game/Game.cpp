#include "pch.h"
#include "Game.h"

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

	hdcBack = ::CreateCompatibleDC(hdc); // hdc와 호환되는 DC를 생성
	_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom); // hdc와 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack); // DC와 BMP를 연결
	::DeleteObject(prev);

	TimeManager::GET_SINGLE()->Init();
	InputManager::GET_SINGLE()->Init(hwnd);
	GameManager::GET_SINGLE()->Init();
	SceneManager::GET_SINGLE()->Init();
	ResourceManager::GET_SINGLE()->Init(hwnd, fs::current_path().parent_path().string() + "\\Resources");
	SoundManager::GET_SINGLE()->Init(hwnd);
	CollisionManager::GET_SINGLE()->Init();
	UIManager::GET_SINGLE()->Init(hwnd);

	SceneManager::GET_SINGLE()->RequestToChangeScene(SceneType::LobbyScene);
}

void Game::Update()
{
	TimeManager::GET_SINGLE()->Update();
	InputManager::GET_SINGLE()->Update();
	GameManager::GET_SINGLE()->Update();
	SceneManager::GET_SINGLE()->Update();
	SoundManager::GET_SINGLE()->Update();
	CollisionManager::GET_SINGLE()->Update();
}

void Game::Render()
{
	SceneManager::GET_SINGLE()->Render(hdcBack);

	unsigned __int32 fps = TimeManager::GET_SINGLE()->GetFPS();
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	{
		wstring str = ::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(hdcBack, 550, 10, str.c_str(), static_cast<__int32>(str.size()));
	}

	// Double Buffering
	::BitBlt(hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY); // 비트 블릿 : 고속 복사
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}