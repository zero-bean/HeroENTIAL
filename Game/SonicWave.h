#pragma once

#include "Projectile.h"

class Creature;

class SonicWave : public Projectile
{
	using Super = Projectile;
public:
	SonicWave();
	virtual ~SonicWave();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};
	virtual void UpdateAnimation() override;

public:
	void SetDirectionVector(const Vec2 sp, const Vec2 lp) {
		directionVector = lp - sp;
		directionVector.Normalize();
	}

private:
	shared_ptr<Flipbook> _flipbookIdle = nullptr;
	weak_ptr<Creature> _target = {};
	float _sumTime = 0.f;
	Vec2 directionVector = {};
};

