#include "pch.h"
#include "QuestManager.h"
#include "Quest.h"
#include "KillMonsterCondition.h"

void QuestManager::Init()
{
    // ��� 4���� óġ
    auto goblinQuest = make_shared<Quest>(L"Quest: Goblin Hunter", L"Hunt 4 goblins!");
    goblinQuest->AddCondition(make_shared<KillMonsterCondition>(L"Goblin", 4));
    _questList.push_back(goblinQuest);

    // �̳�Ÿ�츣�� óġ
    auto bossQuest = make_shared<Quest>(L"Quest: Minotaur Hunter", L"Slave the minotaur!");
    bossQuest->AddCondition(make_shared<KillMonsterCondition>(L"Minotaur", 1));
    _questList.push_back(bossQuest);

    // ��� 8���� óġ
    auto goblinQuest2 = make_shared<Quest>(L"Quest: Goblin Hunter Pro", L"Hunt 8 goblins!");
    goblinQuest2->AddCondition(make_shared<KillMonsterCondition>(L"Goblin", 8));
    _questList.push_back(goblinQuest2);

    // �̳�Ÿ�츣�� 2ȸ óġ
    auto bossQuest2 = make_shared<Quest>(L"Quest: Minotaur Hunter", L"Slave the minotaur! x2");
    bossQuest2->AddCondition(make_shared<KillMonsterCondition>(L"Minotaur", 2));
    _questList.push_back(bossQuest2);

    // ��� 12���� óġ
    auto goblinQuest3 = make_shared<Quest>(L"Quest: Goblin Hunter Master", L"Hunt 12 goblins!");
    goblinQuest3->AddCondition(make_shared<KillMonsterCondition>(L"Goblin", 12));
    _questList.push_back(goblinQuest3);

    // �̳�Ÿ�츣�� 3ȸ óġ
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