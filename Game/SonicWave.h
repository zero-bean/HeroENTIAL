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
	void SetDirVec(const Vec2 sp, const Vec2 lp) 
	{
		DirVec = lp - sp;
		DirVec.Normalize();
	}

private:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};

private:
	weak_ptr<Creature> _target = {};
};

