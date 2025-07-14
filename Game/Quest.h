#pragma once
#include "IObjective.h"

class QuestCondition;

class Quest : public IObjective {
    using Super = IObjective;
public:
    Quest(const wstring& name, const wstring& desc);
    ~Quest() override;

public:
    void SetActive() override;
    void ResetProgress() override;
    void SetFinished();
    void AddCondition(shared_ptr<QuestCondition> cond);
    void OnNotify(EventType type, const wstring& param) override;
    bool IsCompleted() const override;

public:
    ProgressType GetType() const override { return ProgressType::Quest; }
    wstring GetName() const override { return _name; }
    wstring GetDescription() const override { return _desc; }
    ProgressState GetState() const override { return _state; }

private:
    wstring _name = {};
    wstring _desc = {};
    ProgressState _state = ProgressState::Inactive;
    vector<shared_ptr<QuestCondition>> _conditions = {};
};

