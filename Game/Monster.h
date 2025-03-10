#pragma once

#include "Creature.h"

class Player;
class Flipbook;
class Collider;

enum class Rank
{
	Common,
	Rare,
	Elite,
	Boss,
};

class Monster : public Creature
{
	using Super = Creature;
public:
	Monster();
	virtual ~Monster();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;
	virtual void OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;

public:
	void SetRank(Rank rank) { _rank = rank; }

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}
	virtual void TickAttack() override {}
	virtual void TickAttacked() override {}
	virtual void TickDeath() override;
	virtual void TickBirth() override;

	virtual void UpdateAnimation() override;

protected:
	virtual void DropItems() {}

protected:
	shared_ptr<Flipbook> _idle[2] = {};
	shared_ptr<Flipbook> _move[2] = {};
	shared_ptr<Flipbook> _attack[2] = {};
	shared_ptr<Flipbook> _attacked[2] = {};
	shared_ptr<Flipbook> _dead[2] = {};
	shared_ptr<Flipbook> _birth[2] = {};

	Rank _rank = Rank::Common;

	weak_ptr<Player> _target;
};

