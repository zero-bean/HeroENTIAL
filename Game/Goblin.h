#pragma once

#include "Monster.h"

enum class MonsterType
{
	Axe,
	Bow,
};

class Goblin : public Monster
{
	using Super = Monster;
public:
	Goblin(MonsterType type = MonsterType::Axe, Rank rank = Rank::Common);
	virtual ~Goblin();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickAttack() override;
	virtual void TickAttacked() override;

	virtual void DropItems() override {}

private:
	MonsterType _type = MonsterType::Axe;
	float _waitAtkSec = 0.f;
};

