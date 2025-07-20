#include "pch.h"
#include "SettingsMainPanel.h"
#include "SettingsContainer.h"
#include "Button.h"

SettingsMainPanel::SettingsMainPanel()
{
	// 패널
	SetPos({ GWinSizeX / 2, GWinSizeY / 2 });
	SetSize({ 683, 384 });

	// 컨테이너
	_container = make_shared<SettingsContainer>();
	_container->SetPos(GetPos());
	_container->SetSize({ 683, 384 });
	AddChild(_container);

	// 버튼
	_buttons.resize(3);
	_buttons[0] = make_shared<Button>();
	_buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Sound"), BS_Default);
	_buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Sound_Pressed"), BS_Pressed);
	AddChild(_buttons[0]);
	_buttons[1] = make_shared<Button>();
	_buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Back"), BS_Default);
	_buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Back_Pressed"), BS_Pressed);
	AddChild(_buttons[1]);
	_buttons[2] = make_shared<Button>();
	_buttons[2]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Quit"), BS_Default);
	_buttons[2]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Quit_Pressed"), BS_Pressed);
	AddChild(_buttons[2]);
}

SettingsMainPanel::~SettingsMainPanel()
{
}

void SettingsMainPanel::BeginPlay()
{
	// 버튼
	const float panelCenterX = GetPos().x;
	const float panelTopY = GetPos().y - GetSize().y / 2.0f;
	const Vec2 buttonSize = { 370, 100 };
	auto self = shared_from_this();

	for (int i = 0; i < _buttons.size(); ++i)
	{
		_buttons[i]->SetSize(buttonSize);
		const float y = panelTopY + 80.0f + i * (buttonSize.y + 20.0f);
		_buttons[i]->SetPos({ panelCenterX, y });
	}

	_buttons[0]->AddOnClickDelegate([this]() {
		SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");
		if (_onSoundBtnClick)
			_onSoundBtnClick();
		});

	_buttons[1]->AddOnClickDelegate([this]() {
		SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");
		if (_onBackBtnClick)
			_onBackBtnClick();
		});

	_buttons[2]->AddOnClickDelegate([this]() {
		SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");
		if (_onQuitBtnClick)
			_onQuitBtnClick();
		});
}

void SettingsMainPanel::Tick()
{
	Super::Tick();
}

void SettingsMainPanel::Render(HDC hdc)
{
	Super::Render(hdc);
}
