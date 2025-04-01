#include "pch.h"
#include "InventorySlot.h"
#include "Item.h"
#include "Flipbook.h"
#include "Texture.h"

InventorySlot::InventorySlot()
{

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

}

void InventorySlot::Render(HDC hdc)
{
	shared_ptr<Item> item = _owner.lock();

	if (!item)
		return;

	const FlipbookInfo& info = item->GetFlipbook()->GetInfo();
	const Vec2Int size = info.size;

	::TransparentBlt(hdc,
		(__int32)_pos.x - size.x / 2,
		(__int32)_pos.y - size.y / 2,
		size.x * 2,
		size.y * 2,
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
	::TextOut(hdc, (__int32)_pos.x + size.x - 1, (__int32)_pos.y + size.y - 2, 
		str.c_str(), static_cast<__int32>(str.size()));
	::RestoreDC(hdc, oldDC);
}
