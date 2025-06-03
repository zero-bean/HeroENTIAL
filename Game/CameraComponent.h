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
	void SetBackGroundRange(const Vec2 range) { _bgRange = range; }

public:
	void SetTargetZoom(float zoom, float speed = 5.0f);
	float GetZoom() const { return _zoom; }

private:
	Vec2 _bgRange = {};
	CameraShake _shake = {};

	float _zoom = 1.0f;         // «ˆ¿Á ¡‹
	float _targetZoom = 1.0f;   // ∏Ò«• ¡‹
	float _zoomSpeed = 5.0f;    // ∫∏∞£ º”µµ
};

