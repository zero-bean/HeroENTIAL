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

	virtual bool ShouldAffectTilemap() const override { return false; }

public:
	void SetTimer(const float time) { _timer = time; }

	void SetAttack(__int32 attack) { _attack = attack; }
	__int32 GetAttack() const { return _attack; }

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}
	virtual void UpdateAnimation() override;

protected:
	__int32 _attack = 10;
	float _timer = 2.5f;
	Vec2 _dirVec = {};
};