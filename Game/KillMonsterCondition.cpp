#include "pch.h"
#include "KillMonsterCondition.h"

KillMonsterCondition::KillMonsterCondition(const wstring& name, int count)
    : _monsterName(name), _targetCount(count) 
{

}

KillMonsterCondition::~KillMonsterCondition()
{

}

void KillMonsterCondition::OnNotify(EventType type, const wstring& param)
{
    if (type == EventType::MonsterKilled && param == _monsterName)
        _currentCount++;
}
