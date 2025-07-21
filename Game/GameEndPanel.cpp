#include "pch.h"
#include "GameEndPanel.h"
#include "GameEndContainer.h"
#include "Button.h"
#include "Font.h"

GameEndPanel::GameEndPanel()
{
	// �г�
	SetPos({ GWinSizeX / 2, GWinSizeY / 2 });
	SetSize({ 683, 384 });

	// �����̳�
	_container = make_shared<GameEndContainer>();
	_container->SetPos(GetPos());
	AddChild(_container);

	// ��ư
	_button = make_shared<Button>();
	_button->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Return"), BS_Default);
	_button->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Return_Pressed"), BS_Pressed);
	AddChild(_button);

	// ��Ʈ
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

	// ��ư Ŭ�� ��,
	auto self = shared_from_this();
	_button->AddOnClickDelegate([self]() {
		// ���� ���
		SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");

		// �� ��ü ��û
		SceneManager::GET_SINGLE()->RequestToChangeScene(SceneType::LobbyScene);

		// ���� ���� ��û
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

		// ��� �߽� ���� ��ġ
		Vec2 center = GetPos();
		Vec2 textPos = {
			center.x - textSize.cx / 2.0f,
			center.y - 100 
		};

		Utils::DrawTextColored(hdc, textPos, str, font, RGB(0, 0, 0));
	}
}
