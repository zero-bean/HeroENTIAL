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
	// 디버깅
	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::Q)) {
		SetTargetZoom(1.5f, 4.0f); // 줌인
	}
	else if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::E)) {
		SetTargetZoom(1.0f, 4.0f); // 복귀
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

	// 1. 흔들림
	_shake.Update(TimeManager::GET_SINGLE()->GetDeltaTime());
	pos += _shake.GetOffset();

	// 2. 줌
	if (abs(_zoom - _targetZoom) > 0.01f)
		_zoom += (_targetZoom - _zoom) * _zoomSpeed * TimeManager::GET_SINGLE()->GetDeltaTime();
	

	// 3. 카메라 맵 이탈 방지
	pos.x = clamp(pos.x, screenX, _bgRange.x - screenX);
	pos.y = clamp(pos.y, screenY, _bgRange.y - screenY);

	// 4. 업데이트
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

void CameraComponent::ForceFocusTo(Vec2 targetPos, float zoom, float duration)
{
	_isForced = true;
	_forcedPos = pos;
	_forcedZoom = zoom;
	_forcedDuration = duration;
	_elapsed = 0.0f;

	_zoom = zoom; // 즉시 반영하거나 점진적으로 보간해도 됨
	_targetZoom = zoom;
}
