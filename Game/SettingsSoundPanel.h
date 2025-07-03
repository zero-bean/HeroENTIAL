#pragma once
#include "Panel.h"

class Button;
class Slider;
class Font;
class SettingsContainer;

class SettingsSoundPanel : public Panel, public enable_shared_from_this<SettingsSoundPanel>
{
	using Super = Panel;
public:
	SettingsSoundPanel();
	virtual ~SettingsSoundPanel() override;

public:
	virtual void BeginPlay();
	virtual void Tick() override;
	virtual void Render(HDC hdc);

public:
	void SetBtnClick(function<void()> func) { _onBackBtnClick = func; }

private:
	shared_ptr<SettingsContainer> _container = nullptr;
	shared_ptr<Button> _button = nullptr;
	shared_ptr<Slider> _sfxSlider = nullptr;
	shared_ptr<Slider> _bgmSlider = nullptr;
	shared_ptr<Font> _font = nullptr;
	function<void()> _onBackBtnClick = {};
};

