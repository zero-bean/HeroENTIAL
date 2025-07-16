#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "Consumable.h"
#include "Potion.h"
#include "Scene.h"
#include "Player.h"
#include "BoxCollider.h"

Inventory::Inventory()
{
	_items.resize((int)ItemType::MAX_COUNT);
    _items[static_cast<int>(ItemType::Equipment)].resize(16); // 장비
    _items[static_cast<int>(ItemType::Consumable)].resize(16); // 소비
    _items[static_cast<int>(ItemType::Others)].resize(16); // 기타
    _items[static_cast<int>(ItemType::Quick)].resize(3); // 퀵슬롯
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

    if (category == 4)
    {
        _gold += item->GetItemCount();
        return true;
    }

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

    shared_ptr<Scene> scene = SceneManager::GET_SINGLE()->GetCurrentScene();
    if (!scene) return false;

    shared_ptr<Player> player = scene->FindActor<Player>();
    if (!player) return false;


    // 1. owner 해제
    item->GetOwner().reset();

    // 2. 인벤토리에서 해당 아이템 제거
    const int category = item->GetItemTypeIndex();
    const int idx = FindItemIndex(item, category);
    if (idx != -1)
        _items[category][idx] = nullptr;

    // 3. 씬에게 드랍 요청
    const Vec2Int pos = player->GetCellPos();
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
