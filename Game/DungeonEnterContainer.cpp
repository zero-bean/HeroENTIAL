#include "pch.h"
#include "DungeonEnterContainer.h"
#include "Sprite.h"
#include "ResourceManager.h"
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
