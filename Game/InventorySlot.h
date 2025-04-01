#pragma once

#include "UI.h"

class Item;

class InventorySlot : public UI
{
	using Super = UI;
public:
	InventorySlot();
	virtual ~InventorySlot();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
};

