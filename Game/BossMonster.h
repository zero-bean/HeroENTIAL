#pragma once
#include "Monster.h"

class BossPattern;

class BossMonster : public Monster
{
	using Super = Monster;
public:
	BossMonster();
	virtual ~BossMonster();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void AddPattern(shared_ptr<BossPattern> pattern);
	void ChangePattern(shared_ptr<BossPattern> pattern);
	void ClearPatterns();
	void InterruptPattern();
	void ResumePattern() {}

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}
	virtual void TickAttack() override {}
	virtual void TickAttacked() override {}
	virtual void TickDeath() override {}
	virtual void TickBirth() override {}
	virtual void TickStunned() override {}

protected:
	virtual void DropItems() override {}

protected:
	shared_ptr<BossPattern> _currentPattern = nullptr;
	vector<shared_ptr<BossPattern>> _patternList = {};
};

