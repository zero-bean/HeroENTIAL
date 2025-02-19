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
	if (_owner.expired() == true)
		return;

	shared_ptr<Actor> owner = _owner.lock();
	Vec2 pos = owner->GetPos();

	// TEMP
	pos.x = ::clamp(pos.x, 400.f, 3024.f - 400.f);
	pos.y = ::clamp(pos.y, 300.f, 2064.f - 300.f);

	SceneManager::GET_SINGLE()->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{

}
