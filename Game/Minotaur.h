#pragma once
#include "BossMonster.h"

class Minotaur : public BossMonster
{
	using Super = BossMonster;
public:
	Minotaur();
	virtual ~Minotaur() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void SetPatternAnimation(const wstring& name) override;

private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickAttack() override;
	virtual void TickSkill() override;
	virtual void TickAttacked() override {}
	virtual void TickDeath() override;
	virtual void TickBirth() override {}
	virtual void TickStunned() override {}

private:
	virtual void DropItems() override {}

private:
	shared_ptr<Flipbook> _smash[2] = {};
	shared_ptr<Flipbook> _stab[2] = {};
	shared_ptr<Flipbook> _prepare[2] = {};
	shared_ptr<Flipbook> _swing[2] = {};
};

