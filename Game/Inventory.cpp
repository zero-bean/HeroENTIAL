#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "Consumable.h"
#include "Potion.h"

Inventory::Inventory() : _equipmentItems(16, nullptr), _consumableItems(16, nullptr), _otherItems(16, nullptr)
{
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
    vector<shared_ptr<Item>>* targetInventory = nullptr;

    if (dynamic_pointer_cast<ItemEquipment>(item))
        targetInventory = &_equipmentItems;
    else if (dynamic_pointer_cast<ItemConsumable>(item))
        targetInventory = &_consumableItems;
    else
        targetInventory = &_miscItems;

    for (auto& slot : *targetInventory)
    {
        if (slot == nullptr)
        {
            slot = item;
            return true;
        }
    }
    return false; // 인벤토리 공간 부족
}

bool Inventory::RemoveItem()
{
    vector<shared_ptr<Item>>* targetInventory = nullptr;

    if (dynamic_pointer_cast<ItemEquipment>(item))
        targetInventory = &_equipmentItems;
    else if (dynamic_pointer_cast<ItemConsumable>(item))
        targetInventory = &_consumableItems;
    else
        targetInventory = &_miscItems;

    for (auto& slot : *targetInventory)
    {
        if (slot == item)
        {
            slot.reset(); // 아이템 제거
            return true;
        }
    }
    return false; // 해당 아이템을 찾을 수 없음
}

shared_ptr<Item> Inventory::GetItem(int index, ItemType type)
{
    vector<shared_ptr<Item>>* targetInventory = nullptr;

    switch (type)
    {
    case ItemType::Equipment:
        targetInventory = &_equipmentItems;
        break;
    case ItemType::Consumable:
        targetInventory = &_consumableItems;
        break;
    case ItemType::Misc:
        targetInventory = &_miscItems;
        break;
    default:
        return nullptr;
    }

    if (index < 0 || index >= targetInventory->size())
        return nullptr;

    return (*targetInventory)[index];
}
