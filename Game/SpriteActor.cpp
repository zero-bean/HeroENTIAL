#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneManager.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();


}

void SpriteActor::Tick()
{
	Super::Tick();


}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprite == nullptr)
		return;

	Vec2Int size = _sprite->GetSize();
	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();

	::BitBlt(hdc,
		(__int32)_pos.x - size.x / 2 - ((__int32)cameraPos.x - GWinSizeX / 2),
		(__int32)_pos.y - size.y / 2 - ((__int32)cameraPos.y - GWinSizeY / 2),
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		SRCCOPY); 
}