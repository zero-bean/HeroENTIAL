#pragma once
#include "Actor.h"
#include "CameraShake.h"

class CameraController : public Actor
{
public:
	CameraController();
	virtual ~CameraController() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override {}

public:
	// CameraController가 가진 맴버 설정 및 관리
	void SetTarget(shared_ptr<Actor> target) { _target = target; }
	shared_ptr<Actor> GetTarget() const { return _target; }

	void SetBackGroundRange(const Vec2 range) { _bgRange = range; }

	void SetTargetZoom(float zoom, float speed = 5.0f);
	float GetZoom() const { return _zoom; }

private:
	shared_ptr<Actor> _target = nullptr;

	Vec2 _bgRange = {};
	CameraShake _shake = {};

	float _zoom = 1.0f;         // 현재 줌
	float _targetZoom = 1.0f;   // 목표 줌
	float _zoomSpeed = 5.0f;    // 보간 속도
};

