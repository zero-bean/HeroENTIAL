#pragma once

#include "Creature.h"

class Player;
class Flipbook;

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

	virtual TILE_TYPE GetTileType() const override { return TILE_TYPE::MONSTER; }

public:
	shared_ptr<Player> GetTarget() { return _target.expired() ? nullptr : _target.lock(); }
	void SetTarget(const shared_ptr<Player> target) { _target = target; }

	void SetRank(Rank rank) { _rank = rank; }

	bool MoveToTarget(const Vec2Int& targetCellPos, int dist = 1);

public:
	virtual void NotifiedPlayerOnDied() {}

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}
	virtual void TickAttack() override {}
	virtual void TickAttacked() override {}
	virtual void TickDeath() override;
	virtual void TickBirth() override;
	virtual void TickSkill() {}
	virtual void TickStunned() {}

	virtual void UpdateAnimation() override;

protected:
	virtual void DropItems() {}

protected:
	shared_ptr<Flipbook> _idle[2] = {};
	shared_ptr<Flipbook> _move[2] = {};
	shared_ptr<Flipbook> _attack[2] = {};
	shared_ptr<Flipbook> _attacked[2] = {};
	shared_ptr<Flipbook> _stunned[2] = {};
	shared_ptr<Flipbook> _death[2] = {};
	shared_ptr<Flipbook> _birth[2] = {};

	Rank _rank = Rank::Common;

	weak_ptr<Player> _target;
};

