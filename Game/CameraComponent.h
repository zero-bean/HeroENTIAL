#pragma once
#include "Component.h"
#include "CameraShake.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent() override;

public:
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

public:
	// CameraComponent가 가진 맴버 설정 및 관리
	void SetBackGroundRange(const Vec2 range) { _bgRange = range; }

	void SetTargetZoom(float zoom, float speed = 5.0f);
	float GetZoom() const { return _zoom; }

public:
	// 외부에서 카메라에게 요청하는 기능
	void ForceFocusTo(Vec2 targetPos, float zoom, float duration);
	void ReleaseFocusing() { _isForced = false; }

private:
	Vec2 _bgRange = {};
	CameraShake _shake = {};

	float _zoom = 1.0f;         // 현재 줌
	float _targetZoom = 1.0f;   // 목표 줌
	float _zoomSpeed = 5.0f;    // 보간 속도

	bool _isForced = false;		// 카메라의 특정 위치 고정 여부
};

