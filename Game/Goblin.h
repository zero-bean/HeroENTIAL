#pragma once

#include "Monster.h"

enum class GoblinType
{
	Axe,
	Bow,
};

class Goblin : public Monster
{
	using Super = Monster;
public:
	Goblin();
	virtual ~Goblin();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetGoblinType(GoblinType type);

private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickAttack() override;
	virtual void TickAttacked() override;

	virtual void DropItems() override;

private:
	GoblinType _type = GoblinType::Axe;
	float _waitAtkSec = 0.f;
};

