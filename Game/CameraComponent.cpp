#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "InputManager.h"

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
	// µð¹ö±ë
	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::Q)) {
		SetTargetZoom(1.5f, 4.0f); // ÁÜÀÎ
	}
	else if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::E)) {
		SetTargetZoom(1.0f, 4.0f); // º¹±Í
	}
	else if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::KEY_1)) {
		_shake.Start(ShakeType::Earthquake);
	}
	else if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::KEY_2)) {
		_shake.Start(ShakeType::Explosion);
	}
	else if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::KEY_3)) {
		_shake.Start(ShakeType::HitRecoil);
	}
	else if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::KEY_4)) {
		_shake.Start(ShakeType::SubtlePulse);
	}

	shared_ptr<Actor> owner = _owner.lock();
	if (!owner) return;

	const float screenX = static_cast<float>(GWinSizeX / 2);
	const float screenY = static_cast<float>(GWinSizeY / 2);
	Vec2 pos = owner->GetPos();

	// 1. Èçµé¸²
	_shake.Update(TimeManager::GET_SINGLE()->GetDeltaTime());
	pos += _shake.GetOffset();

	// 2. ÁÜ
	if (abs(_zoom - _targetZoom) > 0.01f)
		_zoom += (_targetZoom - _zoom) * _zoomSpeed * TimeManager::GET_SINGLE()->GetDeltaTime();
	

	// 3. Ä«¸Þ¶ó ¸Ê ÀÌÅ» ¹æÁö
	pos.x = clamp(pos.x, screenX, _bgRange.x - screenX);
	pos.y = clamp(pos.y, screenY, _bgRange.y - screenY);

	// 4. ¾÷µ¥ÀÌÆ®
	SceneManager::GET_SINGLE()->SetCameraPos(pos);
	SceneManager::GET_SINGLE()->SetCameraZoom(_zoom);
}



void CameraComponent::Render(HDC hdc)
{

}

void CameraComponent::SetTargetZoom(float zoom, float speed)
{
	_targetZoom = zoom;
	_zoomSpeed = speed;
}
