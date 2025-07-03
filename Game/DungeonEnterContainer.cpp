#include "pch.h"
#include "DungeonEnterContainer.h"
#include "Sprite.h"

DungeonEnterContainer::DungeonEnterContainer()
{
	SetSize({ 1000, 300 });
	_sprites.resize(1);
	_sprites[0] = ResourceManager::GET_SINGLE()->GetSprite(L"Banner_Dungeon");
}

DungeonEnterContainer::~DungeonEnterContainer()
{

}

void DungeonEnterContainer::BeginPlay()
{
	Super::BeginPlay();
}

void DungeonEnterContainer::Tick()
{
	Super::Tick();
}

void DungeonEnterContainer::Render(HDC hdc)
{
	Super::Render(hdc);

	// 화면 중앙에 50% 투명한 검은 배경
	Utils::DrawRectTransparent(
		hdc,
		{ GWinSizeX / 2, GWinSizeY / 2 },
		static_cast<int>(GWinSizeX),
		static_cast<int>(GWinSizeY),
		RGB(0, 0, 0),
		128
	);

    ::StretchBlt(
        hdc,
        (__int32)_pos.x - GetSize().x / 2,
        (__int32)_pos.y - GetSize().y / 2,
        GetSize().x,
        GetSize().y,
        _sprites[0]->GetDC(),
        _sprites[0]->GetPos().x,
        _sprites[0]->GetPos().y,
        _sprites[0]->GetSize().x,
        _sprites[0]->GetSize().y,  
        SRCCOPY
    );
}
