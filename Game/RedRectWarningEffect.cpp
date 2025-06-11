#include "pch.h"
#include "RedRectWarningEffect.h"
#include "SceneManager.h"

RedRectWarningEffect::RedRectWarningEffect()
{
}

RedRectWarningEffect::~RedRectWarningEffect()
{
}

void RedRectWarningEffect::BeginPlay()
{
	Super::BeginPlay();
}

void RedRectWarningEffect::Tick()
{
	Super::Tick();

}

void RedRectWarningEffect::Render(HDC hdc)
{

	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
	Vec2 renderPos = _pos - (cameraPos - Vec2(GWinSizeX / 2, GWinSizeY / 2));

    Utils::DrawRectTransparent(hdc, renderPos, static_cast<int>(_size.x), static_cast<int>(_size.y), RGB(255, 0, 0), 128);
}
