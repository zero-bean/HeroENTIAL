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
	bool AddItem(shared_ptr<Item> item);
	vector<shared_ptr<Item>> GetItems(const int idx) { return _items[idx]; }
private:
	vector<vector<shared_ptr<Item>>> _items;
};
