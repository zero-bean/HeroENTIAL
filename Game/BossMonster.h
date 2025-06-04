#pragma once
#include "Monster.h"

class BossPattern;

class BossMonster : public Monster
{
public:
	BossMonster();
	virtual ~BossMonster();

	void BeginPlay() override;
	void Tick() override;

	void AddPattern(shared_ptr<BossPattern> pattern);
	void ChangePattern(shared_ptr<BossPattern> pattern);
	void ClearPatterns();

private:
	shared_ptr<BossPattern> _currentPattern;
	vector<std::shared_ptr<BossPattern>> _patternList;
};

