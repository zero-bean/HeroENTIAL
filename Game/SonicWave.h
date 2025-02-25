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
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void UpdateAnimation() override;

private:
	weak_ptr<Creature> _target = {};
};

