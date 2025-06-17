#include "pch.h"
#include "BossMonster.h"
#include "BossPattern.h"


BossMonster::BossMonster()
{
	SetRank(Rank::Boss);
}

BossMonster::~BossMonster()
{
}

void BossMonster::BeginPlay()
{
	Super::BeginPlay();

}

void BossMonster::Tick()
{
	Super::Tick();

}

void BossMonster::Render(HDC hdc)
{
	Super::Render(hdc);

}

void BossMonster::AddPattern(const wstring& name, shared_ptr<BossPattern> pattern)
{
	if (_patterns.find(name) == _patterns.end())
		_patterns[name] = pattern;
}

void BossMonster::ChangePattern(shared_ptr<BossPattern> pattern)
{
	_currentPattern = pattern;
}

void BossMonster::ClearPatterns()
{
	_patterns.clear();
	_currentPattern = nullptr;
}

void BossMonster::TickIdle()
{
	if (_sequence.empty())
		return;

	const ObjectState nextState = _sequence.front();
	_sequence.pop();
	_sequence.push(nextState);
	SetState(nextState);
}

