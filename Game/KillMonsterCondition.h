#pragma once
#include "QuestCondition.h"
#include "IObjective.h"

class KillMonsterCondition : public QuestCondition
{
	using Super = QuestCondition;
public:
    KillMonsterCondition(const wstring& name, int count);
    virtual ~KillMonsterCondition() override;

public:
    void OnNotify(EventType type, const wstring& param) override;
    bool IsCompleted() const override { return _currentCount >= _targetCount; }
    void Reset() override { _currentCount = 0; }

private:
    wstring _monsterName = {};
    int _targetCount = INT_MAX;
    int _currentCount = 0;
};

