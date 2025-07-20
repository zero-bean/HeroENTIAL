#include "pch.h"
#include "SettingsSoundPanel.h"
#include "SettingsContainer.h"
#include "Button.h"
#include "Slider.h"
#include "Font.h"

SettingsSoundPanel::SettingsSoundPanel()
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
	_button = make_shared<Button>();
	_button->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Back"), BS_Default);
	_button->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Back_Pressed"), BS_Pressed);
	AddChild(_button);

	// 슬라이더
	_sfxSlider = make_shared<Slider>();
	_sfxSlider->SetRange(0.0f, 1.0f);
	AddChild(_sfxSlider);

	// 슬라이더
	_bgmSlider = make_shared<Slider>();
	_bgmSlider->SetRange(0.0f, 1.0f);
	AddChild(_bgmSlider);

	// 폰트
	_font = ResourceManager::GET_SINGLE()->GetFont(L"DungeonFont48");
}

SettingsSoundPanel::~SettingsSoundPanel()
{
}

void SettingsSoundPanel::BeginPlay()
{
	// 버튼
	const float panelCenterX = GetPos().x;
	const float panelTopY = GetPos().y - GetSize().y / 2.0f;
	const float y = panelTopY + 320.f;
	auto self = shared_from_this();

	_button->SetSize({ 370, 100 });
	_button->SetPos({ panelCenterX, y });
	_button->AddOnClickDelegate([this]() {
		SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");
		if (_onBackBtnClick)
			_onBackBtnClick();
		});

	// 슬라이더
	_sfxSlider->SetPos({ panelCenterX, y - 240.f });
	_sfxSlider->SetSize({ 400, 40 });
	_sfxSlider->SetOnValueChanged([this](float value) {
		SoundManager::GET_SINGLE()->SetSFXVolume(value);
		});

	// 슬라이더
	_bgmSlider->SetPos({ panelCenterX, y - 160.f });
	_bgmSlider->SetSize({ 400, 40 });
	_bgmSlider->SetOnValueChanged([this](float value) {
		SoundManager::GET_SINGLE()->SetBGMVolume(value);
		});

	Super::BeginPlay();
}

void SettingsSoundPanel::Tick()
{
	Super::Tick();
}

void SettingsSoundPanel::Render(HDC hdc)
{
	Super::Render(hdc);

	const wstring str[2] = { L"SFX", L"BGM" };
	const Vec2 sliderPos[2] = { _sfxSlider->GetPos(),_bgmSlider->GetPos() };
	for (int i = 0; i < 2; i++)
	{
		const HFONT font = _font->GetHandle();
		const int fontSize = _font->GetSize();
		SIZE textSize{};
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, font);
		GetTextExtentPoint32(memDC, str[i].c_str(), static_cast<int>(str[i].length()), &textSize);
		DeleteDC(memDC);
		const Vec2 textPos = {
			sliderPos[i].x - 300.0f, 
			sliderPos[i].y - textSize.cy / 2.0f 
		};

		Utils::DrawTextColored(hdc, textPos, str[i], font, RGB(0, 0, 0));
	}
}
