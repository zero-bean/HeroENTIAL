#pragma once

#include "UI.h"

class Sprite;

class QuickslotContainer : public UI
{
	using Super = UI;
public:
	QuickslotContainer();
	virtual ~QuickslotContainer() override;

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
	vector<shared_ptr<Sprite>> _sprites;
};