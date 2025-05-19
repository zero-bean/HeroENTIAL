#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "Flipbook.h"
#include "Texture.h"
#include "InventoryPanel.h"
#include "Slot.h"
#include "InventoryTooltip.h"
#include "InventoryContainer.h"
#include "Button.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "UIManager.h"

InventoryPanel::InventoryPanel()
{
	// �����̳�
	_container = make_shared<InventoryContainer>();
	AddChild(_container);

	// ��ư
	_buttons.resize(3, nullptr);

	_buttons[0] = make_shared<Button>();
	_buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button"), BS_Default);
	_buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Pressed"), BS_Pressed);
	_buttons[0]->SetCoverSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Icon_1"), BS_Default);
	_buttons[0]->SetCoverSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Icon_1_Pressed"), BS_Pressed);
	AddChild(_buttons[0]);

	_buttons[1] = make_shared<Button>();
	_buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button"), BS_Default);
	_buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Pressed"), BS_Pressed);
	_buttons[1]->SetCoverSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Icon_2"), BS_Default);
	_buttons[1]->SetCoverSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Icon_2_Pressed"), BS_Pressed);
	AddChild(_buttons[1]);

	_buttons[2] = make_shared<Button>();
	_buttons[2]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button"), BS_Default);
	_buttons[2]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Pressed"), BS_Pressed);
	_buttons[2]->SetCoverSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Icon_3"), BS_Default);
	_buttons[2]->SetCoverSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Icon_3_Pressed"), BS_Pressed);
	AddChild(_buttons[2]);

	// ����
	_slots.resize(16);
	for (shared_ptr<Slot>& slot : _slots) {
		slot = make_shared<Slot>();
		AddChild(slot);
	}

	// ����
	_tooltip = make_shared<InventoryTooltip>();
	AddChild(_tooltip);
}

InventoryPanel::~InventoryPanel()
{
}

void InventoryPanel::BeginPlay()
{
	Super::BeginPlay();

	// �г�
	SetSize({ 260, 260 });
	SetPos({ GWinSizeX / 2, GWinSizeY / 2 });

	// �����̳�
	_container->SetPos(GetPos());

	// ��ư
	float startX = GetPos().x - 96.f;
	float btnY = GetPos().y - static_cast<float>(GetSize().y) / 2.f - 24.f;
	for (int i = 0; i < 3; i++)
	{
		_buttons[i]->SetSize({ 64, 64 });
		_buttons[i]->SetPos({ startX + 64.f * i, btnY });
	}

	_buttons[0]->AddOnClickDelegate(shared_from_this(), [this]() {UpdateSlots(ItemType::Equipment); });
	_buttons[1]->AddOnClickDelegate(shared_from_this(), [this]() {UpdateSlots(ItemType::Consumable); });
	_buttons[2]->AddOnClickDelegate(shared_from_this(), [this]() {UpdateSlots(ItemType::Others); });

	// ����
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int index = (y * 4) + x;
			int dx = 32 + (__int32)_pos.x - _size.x / 2 + (64 * x);
			int dy = 32 + (__int32)_pos.y - _size.y / 2 + (64 * y);
			Vec2 pos(dx, dy);

			_slots[index]->SetPos(pos);

			_slots[index]->SetHover([this, &pos, &index](shared_ptr<Slot> slot) {
				shared_ptr<Item> item = slot->GetOwner();
				if (!item) return;
				
				_tooltip->SetOwner(item);
				_tooltip->SetPos(slot->GetPos() + Vec2(48, 0));
				_tooltip->SetVisible(true);
				});

			_slots[index]->SetUnhover([this]() {
				_tooltip->SetVisible(false);
				});

			_slots[index]->SetOnClick([this](shared_ptr<Slot> slot) {
				DragState& drag = UIManager::GET_SINGLE()->GetDragState();

				if (!slot) 
					return;

				if (drag.IsDrag())
				{
				// ������ Ÿ���� �ٸ��� ���� �Ұ���
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

				// �巡�� Ȱ��ȭ
				drag.BeginDrag(slot);
				});

		}
	}

	UpdateSlots(ItemType::Equipment);
}

void InventoryPanel::Tick()
{
	if (!_inventory.lock())
		return;

	Super::Tick();

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::I)) 
	{
		_isActivated = !_isActivated;

		// �κ��丮 ������ �巡�� ���� �ʱ�ȭ
		if (!_isActivated)
		{
			DragState& drag = UIManager::GET_SINGLE()->GetDragState();
			drag.EndDrag();
		}
	}

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::LEFT_MOUSE))
		DropDraggedItem();
}

void InventoryPanel::Render(HDC hdc)
{
	if (!_inventory.lock())
		return;

	if (!_isActivated)
		return;

	Super::Render(hdc);

	// �巡�� �� ������ ǥ��
	const DragState& drag = UIManager::GET_SINGLE()->GetDragState();
	if (drag.IsDrag())
	{
		if (shared_ptr<Item> item = drag.GetSlot()->GetOwner())
		{
			const auto& info = item->GetFlipbook()->GetInfo();
			Vec2 mousePos = InputManager::GET_SINGLE()->GetMousePos();

			TransparentBlt(hdc,
				mousePos.x - info.size.x,
				mousePos.y - info.size.y,
				info.size.x * 2,
				info.size.y * 2,
				info.texture->GetDC(),
				info.start * info.size.x,
				info.line * info.size.y,
				info.size.x,
				info.size.y,
				info.texture->GetTransparent());
		}
	}

}

void InventoryPanel::OnClickEquitmentButton()
{
	UpdateSlots(ItemType::Equipment);
}

void InventoryPanel::OnClickConsumableButton()
{
	UpdateSlots(ItemType::Consumable);
}

void InventoryPanel::OnClickOthersButton()
{
	UpdateSlots(ItemType::Others);
}

void InventoryPanel::UpdateSlots(const ItemType category)
{
	if (shared_ptr<Inventory> inventory = _inventory.lock())
	{
		vector<shared_ptr<Item>>& items = inventory->GetItemsRef(static_cast<int>(category));

		for (int i = 0; i < _slots.size(); i++)
		{
			_slots[i]->SetOwnerPtr(&items[i]);
			_slots[i]->SetSlotType(category);
		}
	}
}

void InventoryPanel::DropDraggedItem()
{
	DragState& drag = UIManager::GET_SINGLE()->GetDragState();

	if (!drag.IsDrag() || UIManager::GET_SINGLE()->IsMouseInUIs())
		return;

	shared_ptr<Item> item = drag.GetSlot()->GetOwner();
	if (!item) return;

	if (shared_ptr<Inventory> inventory = _inventory.lock()) {
		const ItemType itemtype = item->GetItemType();
		inventory->DropItem(item);
		drag.EndDrag();
		UpdateSlots(itemtype);
	}
}

