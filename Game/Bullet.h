#pragma once

#include "Projectile.h"

class Collider;

enum class BulletType
{
	Basic,
	Circle,
};

class Bullet : public Projectile
{
	using Super = Projectile;
public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;
	virtual void OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;

private:
	virtual void TickIdle() override;
	virtual void TickMove() override {}

public:
	void SetBulletType(BulletType type);
	void SetDirVec(const Vec2 sp, const Vec2 lp);

	void OnDestroyed();

private:
	BulletType _type = BulletType::Basic;
};

