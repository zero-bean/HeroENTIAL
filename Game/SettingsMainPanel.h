#pragma once
#include "Panel.h"

class Button;
class SettingsContainer;

class SettingsMainPanel : public Panel, public enable_shared_from_this<SettingsMainPanel>
{
	using Super = Panel;
public:
	SettingsMainPanel();
	virtual ~SettingsMainPanel() override;

public:
	virtual void BeginPlay();
	virtual void Tick() override;
	virtual void Render(HDC hdc);

public:
	void SetSoundBtnClick(function<void()> func) { _onSoundBtnClick = func; }
	void SetBackBtnClick(function<void()> func) { _onBackBtnClick = func; }
	void SetQuitBtnClick(function<void()> func) { _onQuitBtnClick = func; }

private:
	shared_ptr<SettingsContainer> _container = nullptr;
	vector<shared_ptr<Button>> _buttons = {};
	function<void()> _onSoundBtnClick = {};
	function<void()> _onBackBtnClick = {};
	function<void()> _onQuitBtnClick = {};
};