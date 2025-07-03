#include "pch.h"
#include "SettingsContainer.h"
#include "Sprite.h"

SettingsContainer::SettingsContainer()
{
	_sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Banner_Settings");
}

SettingsContainer::~SettingsContainer()
{
}

void SettingsContainer::BeginPlay()
{
	Super::BeginPlay();
}

void SettingsContainer::Tick()
{
	Super::Tick();
}

void SettingsContainer::Render(HDC hdc)
{
	Super::Render(hdc);

	::StretchBlt(hdc,
		(__int32)_pos.x - _size.x / 2,
		(__int32)_pos.y - _size.y / 2,
		_size.x,
		_size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		SRCCOPY);
}
