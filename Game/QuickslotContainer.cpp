#include "pch.h"
#include "QuickslotContainer.h"
#include "Sprite.h"

QuickslotContainer::QuickslotContainer()
{
	SetSize({ 192 * 3, 192 });
	_sprites.resize(2);
	_sprites[0] = ResourceManager::GET_SINGLE()->GetSprite(L"Banner_Horizontal");
	_sprites[1] = ResourceManager::GET_SINGLE()->GetSprite(L"Inventory_Slot");
}

QuickslotContainer::~QuickslotContainer()
{
}

void QuickslotContainer::BeginPlay()
{
	Super::BeginPlay();
}

void QuickslotContainer::Tick()
{
	Super::Tick();
}

void QuickslotContainer::Render(HDC hdc)
{
	Super::Render(hdc);

	// Äü½½·Ô ÄÁÅ×ÀÌ³Ê
	const int containerHeightPadding = 18;
	::TransparentBlt(hdc,
		(__int32)_pos.x - GetSize().x / 2,
		(__int32)_pos.y - GetSize().y / 2 - containerHeightPadding,
		GetSize().x,
		GetSize().y,
		_sprites[0]->GetDC(),
		_sprites[0]->GetPos().x,
		_sprites[0]->GetPos().y,
		_sprites[0]->GetSize().x,
		_sprites[0]->GetSize().y,
		_sprites[0]->GetTransparent());

	// ½½·Ô
	const Vec2Int slotSize = { 64, 64 };
	const int slotCount = 3;
	const int slotWidthPadding = 6;
	const int totalSlotWidth = slotCount * slotSize.x + (slotCount - 1) * slotWidthPadding;
	const int startX = GWinSizeX / 2 - totalSlotWidth / 2;
	const int y = GetPos().y - slotSize.y;
	for (int i = 0; i < slotCount; i++)
	{
		int x = startX + i * (slotSize.x + slotWidthPadding);

		::TransparentBlt(hdc,
			x,
			y,
			slotSize.x,
			slotSize.y,
			_sprites[1]->GetDC(),
			_sprites[1]->GetPos().x,
			_sprites[1]->GetPos().y,
			_sprites[1]->GetSize().x,
			_sprites[1]->GetSize().y,
			_sprites[1]->GetTransparent());
	}


}
