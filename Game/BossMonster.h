#pragma once
#include "Monster.h"

class BossPattern;
class Creature;
class Projectile;

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
	void AddPattern(const wstring& name, shared_ptr<BossPattern> pattern);
	void ChangePattern(shared_ptr<BossPattern> pattern);
	void ClearPatterns();
	void ResumePattern() {}

	queue<ObjectState>& GetSequence()  { return _sequence; }
	void AddSequence(const ObjectState state) { _sequence.push(state); }
	void ClearSequence() { while (!_sequence.empty()) { _sequence.pop();} }

public:
	virtual void SetPatternAnimation(const wstring& name) {};
	
	virtual void OnDamaged(shared_ptr<Creature> attacker);
	virtual void OnDamaged(shared_ptr<Projectile> attacker);

protected:
	void SetCoolDown(float time) { _coolDown = time; }

protected:
	virtual void TickIdle() override;
	virtual void TickMove() override {}
	virtual void TickAttack() override {}
	virtual void TickAttacked() override {}
	virtual void TickDeath() override;
	virtual void TickBirth() override {}
	virtual void TickStunned() override {}
	virtual void TickSkill() override {}

protected:
	virtual void DropItems() override {}

protected:
	shared_ptr<BossPattern> _currentPattern = nullptr;
	unordered_map<wstring, shared_ptr<BossPattern>> _patterns = {};
	queue<ObjectState> _sequence = {};
	float _coolDown = 0.f;
};

