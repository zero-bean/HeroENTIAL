#include "pch.h"
#include "GameEndPanel.h"
#include "GameEndContainer.h"
#include "Button.h"
#include "Font.h"

GameEndPanel::GameEndPanel()
{
	// 패널
	SetPos({ GWinSizeX / 2, GWinSizeY / 2 });
	SetSize({ 683, 384 });

	// 컨테이너
	_container = make_shared<GameEndContainer>();
	_container->SetPos(GetPos());
	AddChild(_container);

	// 버튼
	_button = make_shared<Button>();
	_button->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Return"), BS_Default);
	_button->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Return_Pressed"), BS_Pressed);
	AddChild(_button);

	// 폰트
	_font = ResourceManager::GET_SINGLE()->GetFont(L"DungeonFont64");
}

GameEndPanel::~GameEndPanel()
{
}

void GameEndPanel::BeginPlay()
{
	_button->SetSize({ 384, 96 });
	
	const Vec2 panelCenter = GetPos(); 
	const Vec2Int buttonSize = _button->GetSize();
	const float verticalOffset = 100.0f;

	_button->SetPos({
		panelCenter.x,
		panelCenter.y + verticalOffset
		});

	// 버튼 클릭 시,
	auto self = shared_from_this();
	_button->AddOnClickDelegate([self]() {
		// 사운드 출력
		SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");

		// 씬 교체 요청
		SceneManager::GET_SINGLE()->RequestToChangeScene(SceneType::LobbyScene);

		// 본인 삭제 요청
		UIManager::GET_SINGLE()->RemoveUI(self);
		});

	Super::BeginPlay();
}


void GameEndPanel::Tick()
{
	Super::Tick();
}

void GameEndPanel::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_font)
	{
		const HFONT font = _font->GetHandle();
		const int fontSize = _font->GetSize(); 

		const wstring str = _content;
		SIZE textSize{};
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, font);
		GetTextExtentPoint32(memDC, str.c_str(), static_cast<int>(str.length()), &textSize);
		DeleteDC(memDC);

		// 배너 중심 기준 위치
		Vec2 center = GetPos();
		Vec2 textPos = {
			center.x - textSize.cx / 2.0f,
			center.y - 100 
		};

		Utils::DrawTextColored(hdc, textPos, str, font, RGB(0, 0, 0));
	}
}
