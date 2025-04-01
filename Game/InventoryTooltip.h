#pragma once

#include "UI.h"

class Item;

class InventoryTooltip : public UI
{
	using Super = UI;
public:
	InventoryTooltip();
	virtual ~InventoryTooltip();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

public:
	void SetOwner(shared_ptr<Item> owner) { _owner = owner; }

	void SetVisible(bool visible) { isVisible = visible; }

private:
	weak_ptr<Item> _owner;
	bool isVisible = false;
};

