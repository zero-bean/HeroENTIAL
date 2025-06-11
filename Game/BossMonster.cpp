#include "pch.h"
#include "BossMonster.h"
#include "BossPattern.h"
#include "TimeManager.h"
#include "SceneManager.h"

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

	if (!_patternList.empty())
		ChangePattern(_patternList[0]);
}

void BossMonster::Tick()
{
	Super::Tick();

}

void BossMonster::Render(HDC hdc)
{
	Super::Render(hdc);

}

void BossMonster::AddPattern(shared_ptr<BossPattern> pattern)
{
	_patternList.push_back(pattern);
}

void BossMonster::ChangePattern(shared_ptr<BossPattern> pattern)
{
	if (_currentPattern)
		_currentPattern->End();

	if (!pattern)
		return;

	_currentPattern = pattern;
	_currentPattern->Begin();
}

void BossMonster::ClearPatterns()
{
	
}

void BossMonster::InterruptPattern()
{
	if (_currentPattern) 
		_currentPattern->Interrupt();
}

