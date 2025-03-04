#pragma once

#include "GameObject.h"

class Flipbook;

class Projectile : public GameObject
{
	using Super = GameObject;
public:
	Projectile();
	virtual ~Projectile() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetTimer(const float time) { _timer = time; }

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}
	virtual void UpdateAnimation() override;

protected:
	float _timer = 3.f;
	Vec2 DirVec = {};
};