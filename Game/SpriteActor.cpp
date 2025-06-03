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
	float cameraZoom = SceneManager::GET_SINGLE()->GetCameraZoom();

	Vec2 screenCenter = Vec2(GWinSizeX / 2.0f, GWinSizeY / 2.0f);
	Vec2 renderPos = (_pos - cameraPos) * cameraZoom + screenCenter;

	int drawW = static_cast<int>(size.x * cameraZoom);
	int drawH = static_cast<int>(size.y * cameraZoom);

	::StretchBlt(
		hdc,
		static_cast<int>(renderPos.x - drawW / 2),
		static_cast<int>(renderPos.y - drawH / 2),
		drawW,
		drawH,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		size.x,
		size.y,
		SRCCOPY
	);
}