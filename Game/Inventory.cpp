#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "Consumable.h"
#include "Potion.h"
#include "Scene.h"
#include "DevScene.h"
#include "Player.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "CollisionManager.h"

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

bool Inventory::AddItem(shared_ptr<Item>& item)
{
    const int category = item->GetItemTypeIndex();
    const int idx = FindItemIndex(item, category);

    if (idx != -1)
    {
        _items[category][idx]->AddItemCount(item->GetItemCount());
        return true;
    }

    for (auto& slot : _items[category])
    {
        if (!slot)
        {
            slot = item;
            return true;
        }
    }

	return false;
}

bool Inventory::DropItem(shared_ptr<Item>& item)
{
    if (!item) return false;

    shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
    if (!scene) return false;

    shared_ptr<Player> player = dynamic_pointer_cast<Player>(GetOwner());
    if (!player) return false;

    Vec2Int pos = player->GetCellPos();

    // 1. 인벤토리에서 해당 아이템 제거
    const int category = item->GetItemTypeIndex();
    const int idx = FindItemIndex(item, category);
    if (idx != -1)
        _items[category][idx] = nullptr;

    // 2. 씬에게 드랍 요청
    scene->DropItem(item, pos);

    return true;
}

int Inventory::FindItemIndex(shared_ptr<Item> item, const int idx)
{
    for (int i=0; i < _items[idx].size(); i++)
    {
        const auto& target = _items[idx][i];

        if (target && target->GetObjectID() == item->GetObjectID())
            return i;
    }


    return -1;
}
