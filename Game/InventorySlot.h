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
	void SetOwnerPtr(shared_ptr<Item>* ptr) { _owner = ptr; }
	shared_ptr<Item> GetOwner() const { return _owner ? *_owner : nullptr; }
	shared_ptr<Item>* GetOwnerPtr() const { return _owner; }

	void SetHover(function<void(shared_ptr<InventorySlot>)> hover) { _hover = hover; }
	void SetUnhover(function<void()> unhover) { _unhover = unhover; }
	
	void SetOnClick(function<void(shared_ptr<InventorySlot>)> onClick) { _onClick = onClick; }

private:
	shared_ptr<Item>* _owner = nullptr;

	bool isHovered = false;
	function<void(shared_ptr<InventorySlot>)> _hover;
	function<void()> _unhover;

	bool isClicked = false;
	function<void(shared_ptr<InventorySlot>)> _onClick;
};
