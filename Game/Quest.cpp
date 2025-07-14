#include "pch.h"
#include "Quest.h"
#include "QuestCondition.h"

Quest::Quest(const wstring& name, const wstring& desc)
    : _name(name), _desc(desc)
{

}

Quest::~Quest()
{

}

void Quest::SetActive()
{
    _state = ProgressState::Active;
    for (auto& cond : _conditions)
        cond->Reset();
}

void Quest::ResetProgress()
{
    _state = ProgressState::Inactive;
    for (auto& cond : _conditions)
        cond->Reset();
}

void Quest::SetFinished()
{
    _state = ProgressState::Finished;
}

void Quest::AddCondition(shared_ptr<QuestCondition> cond)
{
    _conditions.push_back(cond);
}

void Quest::OnNotify(EventType type, const wstring& param)
{
    if (_state != ProgressState::Active) 
        return;

    for (auto& cond : _conditions)
        cond->OnNotify(type, param);

    if (IsCompleted())
        _state = ProgressState::Completed;
}

bool Quest::IsCompleted() const
{
    for (auto& cond : _conditions)
    {
        if (!cond->IsCompleted()) 
            return false;
    }

    return true;
}
