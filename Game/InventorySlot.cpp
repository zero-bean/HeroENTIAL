#include "pch.h"
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
		if (!isHovered) {
			isHovered = true;

			if (_hover)
				_hover(shared_from_this());
		}
	}
	else {
		if (isHovered) {
			isHovered = false;

			if (_unhover)
				_unhover();
		}
	}
}
void InventorySlot::Render(HDC hdc)
{
	shared_ptr<Item> item = _owner.lock();

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
