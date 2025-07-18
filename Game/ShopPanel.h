#pragma once
#include "Panel.h"

class QuestContainer;
class ShopSlot;
class Button;
class Item;

class ShopPanel : public Panel, public enable_shared_from_this<ShopPanel>
{
	using Super = Panel;
public:
	ShopPanel();
	virtual ~ShopPanel() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetShopItems(const vector<shared_ptr<Item>>& items) { _items = items; }

public:
	void Refresh();

private:
	void OnScrollUp();
	void OnScrollDown();

private:
	vector<shared_ptr<Item>> _items;
	vector<shared_ptr<ShopSlot>> _slots;
	shared_ptr<QuestContainer> _container;
	vector<shared_ptr<Button>> _buttons;
	int _scrollOffset = 0;
	const int _visibleSlotCount = 4;
};

