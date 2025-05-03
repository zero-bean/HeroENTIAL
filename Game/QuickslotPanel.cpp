#include "pch.h"
#include "QuickslotPanel.h"
#include "QuickslotContainer.h"
#include "QuickslotSlot.h"
#include "Inventory.h"
#include "InputManager.h"
#include "UIManager.h"

QuickslotPanel::QuickslotPanel()
{
	// ÄÁÅ×ÀÌ³Ê
	_container = make_shared<QuickslotContainer>();
	AddChild(_container);
	
	// ½½·Ô
	_slots.resize(static_cast<int>(ItemType::Quick));
	for (shared_ptr<QuickslotSlot>& slot : _slots) {
		slot = make_shared<QuickslotSlot>();
		AddChild(slot);
	}
}

QuickslotPanel::~QuickslotPanel()
{
}

void QuickslotPanel::BeginPlay()
{
	Super::BeginPlay();

	// ÆÐ³Î
	SetSize({ 192 * 3, 192 });
	SetPos({ GWinSizeX / 2, (float)GWinSizeY });

	// ÄÁÅ×ÀÌ³Ê
	_container->SetPos(GetPos());

	// ½½·Ô
	const int slotCount = _slots.size();
	const int padding = 6;
	const int width = slotCount * 64 + (slotCount - 1) * padding;
	const int startX = (GetPos().x - 24) / 3 + width;
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
				// ¾ÆÀÌÅÛ Å¸ÀÔÀÌ ´Ù¸£¸é ½º¿Ò ºÒ°¡´É
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

			// µå·¡±× È°¼ºÈ­
			drag.BeginDrag(slot);
			});
	}
  
}

void QuickslotPanel::Tick()
{
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
	Super::Render(hdc);

}

void QuickslotPanel::SetSlotsOwnerPtr(shared_ptr<Inventory> inventory)
{
	if (inventory)
	{
		vector<shared_ptr<Item>>& items = inventory->GetItemsRef(static_cast<int>(ItemType::Quick));

		for (int i = 0; i < _slots.size(); i++)
			_slots[i]->SetOwnerPtr(&items[i]);
	}
}
