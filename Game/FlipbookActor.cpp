#include "pch.h"
#include "FlipbookActor.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "TimeManager.h"
#include "SceneManager.h"

FlipbookActor::FlipbookActor()
{

}

FlipbookActor::~FlipbookActor()
{

}

void FlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookActor::Tick()
{
	Super::Tick();

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	if (info.loop == false && _idx == info.end)
		return;

	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	_sumTime += deltaTime;

	__int32 frameCount = (info.end - info.start + 1);
	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
	float cameraZoom = SceneManager::GET_SINGLE()->GetCameraZoom();

	Vec2Int baseSize = info.size * _scale;
	Vec2Int drawSize = Vec2Int(
		static_cast<int>(baseSize.x * cameraZoom),
		static_cast<int>(baseSize.y * cameraZoom));
	Vec2 screenCenter = Vec2(GWinSizeX / 2.0f, GWinSizeY / 2.0f);
	Vec2 renderPos = (_pos - cameraPos) * cameraZoom + screenCenter;

	::TransparentBlt(
		hdc,
		static_cast<int>(renderPos.x - drawSize.x / 2),
		static_cast<int>(renderPos.y - drawSize.y / 2),
		drawSize.x,
		drawSize.y,
		info.texture->GetDC(),
		(info.start + _idx) * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent()
	);
}


void FlipbookActor::SetFlipbook(shared_ptr<Flipbook> flipbook)
{
	if (flipbook && _flipbook == flipbook)
		return;

	_flipbook = flipbook;
	Reset();
}

void FlipbookActor::Reset()
{
	_sumTime = 0.f;
	_idx = 0;
}

bool FlipbookActor::IsAnimationEnded()
{
	if (_flipbook == nullptr)
		return true;

	const FlipbookInfo& info = _flipbook->GetInfo();
	if (info.loop == false && _idx == info.end)
		return true;

	return false;
}