#pragma once
#include "Monster.h"

class Minotaur : public Monster
{
	using Super = Monster;
public:
	Minotaur();
	virtual ~Minotaur();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickAttack() override;
	virtual void TickAttacked() override;
	virtual void TickBirth() override;
	void TickSkill();
	virtual void UpdateAnimation() override;


	virtual void DropItems() override;

private:
	float _waitAtkSec = 0.f;

};

