#include "pch.h"
#include "QuickslotPanel.h"
#include "QuickslotContainer.h"
#include "QuickslotSlot.h"
#include "Inventory.h"
#include "InputManager.h"
#include "UIManager.h"

QuickslotPanel::QuickslotPanel()
{	
	SetVisible(true);

	// 패널
	SetSize({ 192 * 3, 192 });
	SetPos({ GWinSizeX / 2, (float)GWinSizeY });

	// 컨테이너
	_container = make_shared<QuickslotContainer>();
	_container->SetPos(GetPos());
	AddChild(_container);

	// 슬롯
	_slots.resize(static_cast<int>(ItemType::Quick));
	for (shared_ptr<QuickslotSlot>& slot : _slots) {
		slot = make_shared<QuickslotSlot>();
		AddChild(slot);
	}

	const int slotCount = _slots.size();
	const int padding = 6;
	const int startX = GetPos().x - 64 - padding;
	const int slotY = GetPos().y - 64 / 2;

	for (int i = 0; i < slotCount; i++)
	{
		int slotX = startX + i * (64 + padding);
		Vec2 pos(slotX, slotY);

		_slots[i]->SetPos(pos);
		_slots[i]->SetSlotType(ItemType::Consumable);

		_slots[i]->SetOnClick([this](shared_ptr<Slot> slot) {
			DragState& drag = UIManager::GET_SINGLE()->GetDragState();

			if (!slot)
				return;

			if (drag.IsDrag())
			{
				const ItemType from = drag.GetSlot()->GetSlotType();
				const ItemType To = slot->GetSlotType();
				if (from != To)
					return;

				shared_ptr<Item>* srcPtr = drag.GetSlot()->GetOwnerPtr();
				shared_ptr<Item>* dstPtr = slot->GetOwnerPtr();

				if (srcPtr && dstPtr)
					std::swap(*srcPtr, *dstPtr);

				drag.EndDrag();
				return;
			}

			drag.BeginDrag(slot);
			});
	}
}

QuickslotPanel::~QuickslotPanel()
{
}

void QuickslotPanel::BeginPlay()
{
	Super::BeginPlay();
}

void QuickslotPanel::Tick()
{
	if (!_inventory.lock())
		return;

	Super::Tick();

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::KEY_1))
		_slots[0]->UseItem();
	else if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::KEY_2))
		_slots[1]->UseItem();
	else if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::KEY_3))
		_slots[2]->UseItem();

}

void QuickslotPanel::Render(HDC hdc)
{
	if (!_inventory.lock())
		return;

	if (!GetVisible())
		return;

	Super::Render(hdc);
}

void QuickslotPanel::SetSlotsOwnerPtr(shared_ptr<Inventory> inventory)
{
	_inventory = inventory;
	if (inventory)
	{
		vector<shared_ptr<Item>>& items = inventory->GetItemsRef(static_cast<int>(ItemType::Quick));

		for (int i = 0; i < _slots.size(); i++)
			_slots[i]->SetOwnerPtr(&items[i]);
	}
}
