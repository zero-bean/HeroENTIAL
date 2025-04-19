#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "Flipbook.h"
#include "Texture.h"
#include "InventoryPanel.h"
#include "InventorySlot.h"
#include "InventoryTooltip.h"
#include "InventoryContainer.h"
#include "Button.h"
#include "ResourceManager.h"
#include "InputManager.h"

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
	for (shared_ptr<InventorySlot>& slot : _slots) {
		slot = make_shared<InventorySlot>();
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

	_buttons[0]->AddOnClickDelegate(shared_from_this(), &InventoryPanel::OnClickEquitmentButton);
	_buttons[1]->AddOnClickDelegate(shared_from_this(), &InventoryPanel::OnClickConsumableButton);
	_buttons[2]->AddOnClickDelegate(shared_from_this(), &InventoryPanel::OnClickOthersButton);

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
			
			_slots[index]->SetHover([this, &pos, &index](shared_ptr<InventorySlot> slot) {
				shared_ptr<Item> item = slot->GetOwner();
				if (!item) return;
				
				_tooltip->SetOwner(item);
				_tooltip->SetPos(slot->GetPos() + Vec2(48, 0));
				_tooltip->SetVisible(true);
				});

			_slots[index]->SetUnhover([this]() {
				_tooltip->SetVisible(false);
				});

			_slots[index]->SetOnClick([this](shared_ptr<InventorySlot> slot) {
				if (!slot && !_drag.IsDrag()) 
					return;

				if (_drag.IsDrag())
				{
					shared_ptr<Item>* srcPtr = _drag.GetSlot()->GetOwnerPtr();
					shared_ptr<Item>* dstPtr = slot->GetOwnerPtr();

					if (srcPtr && dstPtr)
						std::swap(*srcPtr, *dstPtr);

					_drag.EndDrag();
					return;
				}

				// �巡�� Ȱ��ȭ
				_drag.BeginDrag(slot);
				});

		}
	}

	UpdateSlots(0);
}

void InventoryPanel::Tick()
{
	Super::Tick();

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::I)) 
	{
		_isActivated = !_isActivated;

		// �κ��丮 ������ �巡�� ���� �ʱ�ȭ
		if (!_isActivated)
			_drag.EndDrag();
	}

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::LEFT_MOUSE))
		DropDraggedItem();
}

void InventoryPanel::Render(HDC hdc)
{
	if (!_isActivated)
		return;

	Super::Render(hdc);

	// �巡�� �� ������ ǥ��
	if (_drag.IsDrag())
	{
		if (shared_ptr<Item> item = _drag.GetSlot()->GetOwner())
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
	UpdateSlots(0);
}

void InventoryPanel::OnClickConsumableButton()
{
	UpdateSlots(1);
}

void InventoryPanel::OnClickOthersButton()
{
	UpdateSlots(2);
}

void InventoryPanel::UpdateSlots(int category)
{
	if (shared_ptr<Inventory> inventory = _inventory.lock())
	{
		vector<shared_ptr<Item>>& items = inventory->GetItemsRef(category);

		for (int i = 0; i < _slots.size(); i++)
			_slots[i]->SetOwnerPtr(&items[i]);
	}
}

void InventoryPanel::DropDraggedItem()
{
	if (!_drag.IsDrag() || IsMouseInRect()) 
		return;

	shared_ptr<Item> item = _drag.GetSlot()->GetOwner();
	if (!item) return;

	if (shared_ptr<Inventory> inventory = _inventory.lock()) {
		int idx = item->GetItemTypeIndex();
		inventory->DropItem(item);
		_drag.EndDrag();
		UpdateSlots(idx);
	}
}

