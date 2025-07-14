#pragma once

class QuestCondition
{
public:
    QuestCondition() {}
    virtual ~QuestCondition() {}

public:
    virtual void OnNotify(EventType type, const wstring& param) = 0;
    virtual bool IsCompleted() const = 0;
    virtual void Reset() = 0;
};

