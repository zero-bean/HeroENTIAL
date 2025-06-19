#include "pch.h"
#include "BossMonster.h"
#include "BossPattern.h"
#include "TimeManager.h"

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

	if (_currentPattern)
	{
		_currentPattern->Tick(TimeManager::GET_SINGLE()->GetDeltaTime());

		if (_currentPattern->IsFinished())
		{
			_currentPattern->End();

			SetCoolDown(_currentPattern->GetCoolTime());
			SetState(ObjectState::Idle);
			_currentPattern = nullptr;
		}
	}
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
	_coolDown -= TimeManager::GET_SINGLE()->GetDeltaTime();
	if (_coolDown > 0.f)
		return;

	// 보스 패턴 순서가 없다면 ..
	if (_sequence.empty())
		return;

	const ObjectState nextState = _sequence.front();
	_sequence.pop();
	_sequence.push(nextState);
	SetState(nextState);
}

void BossMonster::TickDeath()
{
	Super::TickDeath();

	ClearSequence();
}

