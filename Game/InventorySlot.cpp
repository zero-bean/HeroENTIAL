#include "pch.h"
#include "InputManager.h"
#include "InventorySlot.h"
#include "Item.h"
#include "Flipbook.h"
#include "Texture.h"

InventorySlot::InventorySlot()
{
	SetSize({ 48,48 });
}

InventorySlot::~InventorySlot()
{

}

void InventorySlot::BeginPlay()
{
	Super::BeginPlay();


}

void InventorySlot::Tick()
{
	Super::Tick();

	if (IsMouseInRect()) {
		// 슬롯 위에 커서가 있는지
		if (!isHovered) {
			isHovered = true;

			if (_hover)
				_hover(shared_from_this());
		}

		// 슬롯을 클릭했는지 . . .
		if (!isClicked && InputManager::GET_SINGLE()->GetButtonDown(KeyType::LEFT_MOUSE))
		{
			if (_onClick)
				_onClick(shared_from_this());
		}
	}
	else {
		if (isHovered) {
			isHovered = false;

			if (_unhover)
				_unhover();
		}
	}

	isClicked = InputManager::GET_SINGLE()->GetButtonDown(KeyType::LEFT_MOUSE);
}

void InventorySlot::Render(HDC hdc)
{
	shared_ptr<Item> item = GetOwner();

	if (!item)
		return;

	const FlipbookInfo& info = item->GetFlipbook()->GetInfo();
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

	wstring str = ::format(L"{0}", item->GetItemCount());
	int oldDC = ::SaveDC(hdc); 
	::SetBkMode(hdc, TRANSPARENT); 
	::SetTextColor(hdc, RGB(0, 0, 0));
	::TextOut(hdc, (__int32)_pos.x + 15, (__int32)_pos.y + 14, 
		str.c_str(), static_cast<__int32>(str.size()));
	::RestoreDC(hdc, oldDC);
}
