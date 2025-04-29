#pragma once
#include "UI.h"

class Item;


class QuickslotSlot : public UI, public enable_shared_from_this<QuickslotSlot>
{
	using Super = UI;
public:
	QuickslotSlot();
	virtual ~QuickslotSlot();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetItem(shared_ptr<Item> item);
	shared_ptr<Item> GetItem() const;

	void UseItem();

	void SetHotkey(int key);
	int GetHotkey() const;

private:
	shared_ptr<Item> _item;
	int _hotkey = -1;
};