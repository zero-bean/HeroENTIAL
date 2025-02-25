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
	const Vec2Int scaledSize = info.size * _scale;
	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();

	::TransparentBlt(hdc,
		(__int32)_pos.x - scaledSize.x / 2 - ((__int32)cameraPos.x - GWinSizeX / 2),
		(__int32)_pos.y - scaledSize.y / 2 - ((__int32)cameraPos.y - GWinSizeY / 2),
		scaledSize.x,
		scaledSize.y,
		info.texture->GetDC(),
		(info.start + _idx) * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent());
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