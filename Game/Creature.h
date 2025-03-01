#pragma once

#include "GameObject.h"

class Flipbook;
class Collider;
class BoxCollider;

struct Stat
{
	__int32 hp = 100;
	__int32 maxHp = 100;
	__int32 attack = 10;
	__int32 defence = 0;
	float speed = 0;
};

class Creature : public GameObject
{
	using Super = GameObject;
public:
	Creature();
	virtual ~Creature() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}
	virtual void TickAttack() {}
	virtual void TickDeath() {}
	virtual void TickBirth() {}
	virtual void TickAttacked() {}

	virtual void UpdateAnimation() override {}

public:
	virtual void OnDamaged(shared_ptr<Creature> attacker);

	bool IsDead() const { return _stat.hp <= 0; }

	void SetStat(Stat stat) { _stat = stat; }
	Stat& GetStat() { return _stat; }

protected:
	Stat _stat;
};