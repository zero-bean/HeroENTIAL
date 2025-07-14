#pragma once

class IEventData {
public:
    virtual ~IEventData() {}
};

class IObjective
{
public:
    IObjective() {}
    virtual ~IObjective() {}

public:
    virtual ProgressState GetState() const = 0;
    virtual void SetActive() = 0;
    virtual void ResetProgress() = 0;
    virtual void OnNotify(EventType type, const wstring& parama) = 0;
    virtual bool IsCompleted() const = 0;

public:
    virtual ProgressType GetType() const = 0;
    virtual wstring GetName() const = 0;
    virtual wstring GetDescription() const = 0;
};
