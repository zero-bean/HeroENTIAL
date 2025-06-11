#pragma once
#include "BossPattern.h"

class SwingStormSkill : public BossPattern
{
    using Super = BossPattern;
public:
    SwingStormSkill(shared_ptr<BossMonster> owner);
    virtual ~SwingStormSkill() override;

public:
    virtual void Begin() override;
    virtual void Tick(float deltaTime) override;
    virtual void End() override { _isFinished = true; }
    virtual bool IsFinished() override { return _isFinished; }

public:
    virtual void OnRangeReached() override {}

private:
    void FireBulletsPhase1();
    void FireBulletsPhase2();

private:
    enum class Phase
    {
        None,
        Prepare,
        FirstSwing,
        SecondSwing,
        FinalSwing,
        Done
    };

private:
    Phase _phase = Phase::None;
    bool _isFinished = false;
};

