#pragma once

#include "Component.h"

class Item;

class Inventory : public Component
{
	using Super = Inventory;
public:
	Inventory();
	virtual ~Inventory();

public:
	virtual void BeginPlay();
	virtual void TickComponent();
	virtual void Render(HDC hdc);

public:
	bool AddItem(shared_ptr<Item> item);
	bool RemoveItem();
	shared_ptr<Item> GetItem(int index, ItemType type);

private:
	vector<shared_ptr<Item>> _equipmentItems;
	vector<shared_ptr<Item>> _consumableItems;
	vector<shared_ptr<Item>> _otherItems;
};

