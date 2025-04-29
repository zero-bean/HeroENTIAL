#include "pch.h"
#include "QuickslotSlot.h"
#include "Item.h"
#include "Flipbook.h"
#include "Texture.h"
#include "InputManager.h"

QuickslotSlot::QuickslotSlot()
{
}

QuickslotSlot::~QuickslotSlot()
{
}

void QuickslotSlot::BeginPlay()
{
	Super::BeginPlay();
	// 슬롯 크기와 위치 등 초기화 가능
	SetSize({ 64, 64 });
}

void QuickslotSlot::Tick()
{
	Super::Tick();

	// 키 입력 확인
	if (_hotkey >= 0 && ::GetAsyncKeyState('1' + _hotkey) & 0x8000)
	{
		UseItem();
	}
}

void QuickslotSlot::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_item)
		return;

	const FlipbookInfo& info = _item->GetFlipbook()->GetInfo();
	const Vec2Int spriteSize = info.size;

	::TransparentBlt(hdc,
		(__int32)_pos.x - spriteSize.x,
		(__int32)_pos.y - spriteSize.y,
		spriteSize.x * 2,
		spriteSize.y * 2,
		info.texture->GetDC(),
		(info.start) * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent());
}

void QuickslotSlot::SetItem(shared_ptr<Item> item)
{
	_item = item;
}

shared_ptr<Item> QuickslotSlot::GetItem() const
{
	return _item;
}

void QuickslotSlot::UseItem()
{
	if (_item)
	{
		_item->Use();
	}
}

void QuickslotSlot::SetHotkey(int key)
{
	_hotkey = key;
}

int QuickslotSlot::GetHotkey() const
{
	return _hotkey;
}
