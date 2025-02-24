#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"

CameraComponent::CameraComponent()
{

}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::BeginPlay()
{

}

void CameraComponent::TickComponent()
{

	shared_ptr<Actor> owner = _owner.lock();
	Vec2 pos = owner->GetPos();

	const float screenX = GWinSizeX / 2;
	const float screenY = GWinSizeY / 2;

	// TEMP
	pos.x = ::clamp(pos.x, screenX, _bgRange.x - screenX);
	pos.y = ::clamp(pos.y, screenY, _bgRange.y - screenY);

	SceneManager::GET_SINGLE()->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{

}
