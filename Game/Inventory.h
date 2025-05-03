#pragma once

#include "Component.h"

class Item;

class Inventory : public Component
{
	using Super = Component;
public:
	Inventory();
	virtual ~Inventory();

public:
	virtual void BeginPlay();
	virtual void TickComponent();
	virtual void Render(HDC hdc);

public:
	bool AddItem(shared_ptr<Item>& item);
	bool DropItem(shared_ptr<Item>& item);

	vector<shared_ptr<Item>> GetItems(const int category) { return _items[category]; }
	vector<shared_ptr<Item>>& GetItemsRef(int category) { return _items[category]; }

private:
	int FindItemIndex(shared_ptr<Item> item, const int idx);

private:
	vector<vector<shared_ptr<Item>>> _items;
};
