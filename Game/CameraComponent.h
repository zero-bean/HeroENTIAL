#pragma once

#include "Component.h"

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

private:
	Vec2 _bgRange = {};
};

