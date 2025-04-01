#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "Consumable.h"
#include "Potion.h"

Inventory::Inventory()
{
	_items.resize(3, vector<shared_ptr<Item>>(16));
}

Inventory::~Inventory()
{
}

void Inventory::BeginPlay()
{
	Super::BeginPlay();

    
}

void Inventory::TickComponent()
{
	Super::TickComponent();
}

void Inventory::Render(HDC hdc)
{
	Super::Render(hdc);


}

bool Inventory::AddItem(shared_ptr<Item> item)
{
	const int itemIdx = item->GetItemTypeIndex() - 1;

    for (auto& slot : _items[itemIdx])
    {
        if (slot && slot->GetObjectID() == item->GetObjectID()) 
        {
            slot->SetItemCount(slot->GetItemCount() + 1);
            return true;
        }
    }

    for (auto& slot : _items[itemIdx])
    {
        if (!slot)
        {
            slot = item;
            return true;
        }
    }

	return false;
}
