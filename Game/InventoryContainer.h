#pragma once

#include "UI.h"

class Sprite;

class InventoryContainer : public UI
{
	using Super = UI;
public:
	InventoryContainer();
	virtual ~InventoryContainer() override;

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
	vector<shared_ptr<Sprite>> _sprites;
};

