#include "pch.h"
#include "QuestContainer.h"
#include "Sprite.h"

QuestContainer::QuestContainer()
{
	_sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Banner_Settings");
}

QuestContainer::~QuestContainer()
{
}

void QuestContainer::BeginPlay()
{
	Super::BeginPlay();
}

void QuestContainer::Tick()
{
	Super::Tick();
}

void QuestContainer::Render(HDC hdc)
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
