#pragma once
#include "UI.h"

class Sprite;

class SettingsContainer : public UI
{
	using Super = UI;
public:
	SettingsContainer();
	virtual ~SettingsContainer() override;

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
	shared_ptr<Sprite> _sprite;
};

