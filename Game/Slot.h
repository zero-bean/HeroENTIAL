#pragma once

#include "UI.h"

class Item;

class Slot : public UI, public enable_shared_from_this<Slot>
{
	using Super = UI;
public:
	Slot();
	virtual ~Slot();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

public:
	void SetOwnerPtr(shared_ptr<Item>* ptr) { _owner = ptr; }
	shared_ptr<Item> GetOwner() const { return _owner ? *_owner : nullptr; }
	shared_ptr<Item>* GetOwnerPtr() const { return _owner; }

	void SetSlotType(ItemType type) { _slotType = type; }
	ItemType GetSlotType() const { return _slotType; }

	void SetHover(function<void(shared_ptr<Slot>)> hover) { _hover = hover; }
	void SetUnhover(function<void()> unhover) { _unhover = unhover; }

	void SetOnClick(function<void(shared_ptr<Slot>)> onClick) { _onClick = onClick; }

protected:
	shared_ptr<Item>* _owner = nullptr;
	ItemType _slotType = ItemType::MAX_COUNT;

	bool isHovered = false;
	function<void(shared_ptr<Slot>)> _hover;
	function<void()> _unhover;

	bool isClicked = false;
	function<void(shared_ptr<Slot>)> _onClick;
};
