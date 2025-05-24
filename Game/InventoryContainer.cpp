#include "pch.h"
#include "InventoryContainer.h"
#include "ResourceManager.h"
#include "Sprite.h"

InventoryContainer::InventoryContainer()
{
	SetSize({ 266, 266 });
	_sprites.resize(3);
	_sprites[0] = ResourceManager::GET_SINGLE()->GetSprite(L"Banner_Dungeon");
	_sprites[1] = ResourceManager::GET_SINGLE()->GetSprite(L"Inventory_AllSlot");
	_sprites[2] = ResourceManager::GET_SINGLE()->GetSprite(L"Inventory_Slot");
}

InventoryContainer::~InventoryContainer()
{

}

void InventoryContainer::BeginPlay()
{
	Super::BeginPlay();
}

void InventoryContainer::Tick()
{
	Super::Tick();
}

void InventoryContainer::Render(HDC hdc)
{
	Super::Render(hdc);

	// 인벤토리 컨테이너
	const Vec2Int containerSize = { 330, 340 };

	::StretchBlt(hdc,
		(__int32)_pos.x - containerSize.x / 2,
		(__int32)_pos.y - containerSize.y / 2 - 20,
		containerSize.x,
		containerSize.y,
		_sprites[0]->GetDC(),
		_sprites[0]->GetPos().x,
		_sprites[0]->GetPos().y,
		_sprites[0]->GetSize().x,
		_sprites[0]->GetSize().y,
		SRCCOPY);

	// 슬롯 커버
	::TransparentBlt(hdc,
		(__int32)_pos.x - _size.x / 2,
		(__int32)_pos.y - _size.y / 2,
		_size.x,
		_size.y,
		_sprites[1]->GetDC(),
		_sprites[1]->GetPos().x,
		_sprites[1]->GetPos().y,
		_sprites[1]->GetSize().x,
		_sprites[1]->GetSize().y,
		_sprites[1]->GetTransparent());

	// 슬롯
	const Vec2Int slotSize = { 64, 64 };

	for (int y = 0; y < 4; y++) 
	{
		int dy = 4 + (__int32)_pos.y - _size.y / 2 + (64 * y);

		for (int x = 0; x < 4; x++) 
		{
			int dx = 4 + (__int32)_pos.x - _size.x / 2 + (64 * x);

			::TransparentBlt(hdc,
				dx,
				dy,
				slotSize.x,
				slotSize.y,
				_sprites[2]->GetDC(),
				_sprites[2]->GetPos().x,
				_sprites[2]->GetPos().y,
				_sprites[2]->GetSize().x,
				_sprites[2]->GetSize().y,
				_sprites[2]->GetTransparent());
		}
	}
}
