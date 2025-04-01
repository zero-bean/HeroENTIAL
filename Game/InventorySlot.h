#pragma once

#include "UI.h"

class Item;

class InventorySlot : public UI, public enable_shared_from_this<InventorySlot>
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
	void SetOwner(shared_ptr<Item> owner) { _owner = owner; };
	shared_ptr<Item> GetOwner() const { return _owner.lock(); }

	void SetHover(function<void(shared_ptr<InventorySlot>)> hover) { _hover = hover; }
	void SetUnhover(function<void()> unhover) { _unhover = unhover; }

private:
	weak_ptr<Item> _owner;
	function<void(shared_ptr<InventorySlot>)> _hover;
	function<void()> _unhover;
	bool isHovered = false;
};
