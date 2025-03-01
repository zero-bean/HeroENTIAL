#pragma once

#include "GameObject.h"

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
	virtual void TickIdle() override {}
	virtual void TickMove() override {}
	virtual void UpdateAnimation() override {}

protected:
};