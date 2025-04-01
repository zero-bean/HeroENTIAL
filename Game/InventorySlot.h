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

public:
	void SetOwner(shared_ptr<Item> owner) { _owner = owner; }
	shared_ptr<Item> GetOwner() const { return _owner.lock(); }

private:
	weak_ptr<Item> _owner;
};

