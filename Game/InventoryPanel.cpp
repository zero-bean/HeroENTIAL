#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "InventoryPanel.h"
#include "InventorySlot.h"
#include "InventoryTooltip.h"
#include "InventoryContainer.h"
#include "Button.h"
#include "ResourceManager.h"
#include "InputManager.h"

InventoryPanel::InventoryPanel()
{
	// 컨테이너
	_container = make_shared<InventoryContainer>();
	AddChild(_container);

	// 버튼
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

	// 슬롯
	_slots.resize(16);
	for (shared_ptr<InventorySlot>& slot : _slots) {
		slot = make_shared<InventorySlot>();
		AddChild(slot);
	}

	// 툴팁
	_tooltip = make_shared<InventoryTooltip>();
	AddChild(_tooltip);
}

InventoryPanel::~InventoryPanel()
{
}

void InventoryPanel::BeginPlay()
{
	Super::BeginPlay();

	// 패널
	SetSize({ 260, 260 });
	SetPos({ GWinSizeX / 2, GWinSizeY / 2 });

	// 컨테이너
	_container->SetPos(GetPos());

	// 버튼
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

	// 슬롯
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
				if (item)
				{
					_tooltip->SetOwner(item);
					_tooltip->SetPos(slot->GetPos() + Vec2(48, 48));
					_tooltip->SetVisible(true);
				}
				});

			_slots[index]->SetUnhover([this]() {
				_tooltip->SetVisible(false);
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
	}
}

void InventoryPanel::Render(HDC hdc)
{
	if (!_isActivated)
		return;

	Super::Render(hdc);
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

void InventoryPanel::UpdateSlots(const int idx)
{
	shared_ptr<Inventory> owner = _inventory.lock();
	if (!owner)
		return;

	vector<shared_ptr<Item>> items = owner->GetItems(idx);
	for (int i = 0; i < _slots.size(); i++)
		_slots[i]->SetOwner(items[i]);
}
