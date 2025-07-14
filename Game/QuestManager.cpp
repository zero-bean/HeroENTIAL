#include "pch.h"
#include "QuestManager.h"
#include "Quest.h"
#include "KillMonsterCondition.h"

void QuestManager::Init()
{
    // 고블린 4마리 처치
    auto goblinQuest = make_shared<Quest>(L"Quest: Goblin Hunter", L"Hunt 4 goblins!");
    goblinQuest->AddCondition(make_shared<KillMonsterCondition>(L"Goblin", 4));
    _questList.push_back(goblinQuest);

    // 미노타우르스 처치
    auto bossQuest = make_shared<Quest>(L"Quest: Minotaur Hunter", L"Slave the minotaur!");
    bossQuest->AddCondition(make_shared<KillMonsterCondition>(L"Minotaur", 1));
    _questList.push_back(bossQuest);

    // 고블린 8마리 처치
    auto goblinQuest2 = make_shared<Quest>(L"Quest: Goblin Hunter Pro", L"Hunt 8 goblins!");
    goblinQuest2->AddCondition(make_shared<KillMonsterCondition>(L"Goblin", 8));
    _questList.push_back(goblinQuest2);

    // 미노타우르스 2회 처치
    auto bossQuest2 = make_shared<Quest>(L"Quest: Minotaur Hunter", L"Slave the minotaur! x2");
    bossQuest2->AddCondition(make_shared<KillMonsterCondition>(L"Minotaur", 2));
    _questList.push_back(bossQuest2);

    // 고블린 12마리 처치
    auto goblinQuest3 = make_shared<Quest>(L"Quest: Goblin Hunter Master", L"Hunt 12 goblins!");
    goblinQuest3->AddCondition(make_shared<KillMonsterCondition>(L"Goblin", 12));
    _questList.push_back(goblinQuest3);

    // 미노타우르스 3회 처치
    auto bossQuest3 = make_shared<Quest>(L"Quest: Minotaur Hunter", L"Slave the minotaur! x3");
    bossQuest3->AddCondition(make_shared<KillMonsterCondition>(L"Minotaur", 3));
    _questList.push_back(bossQuest3);
}

void QuestManager::Notify(EventType type, const wstring& param)
{
    for (shared_ptr<Quest>& quest : _questList)
    {
        if (quest->GetState() == ProgressState::Active)
            quest->OnNotify(type, param);
    }
}

const vector<shared_ptr<Quest>>& QuestManager::GetAllQuests() const
{
    return _questList;
}