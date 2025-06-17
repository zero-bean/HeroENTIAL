#pragma once
#include "BossPattern.h"

class SmashAttack : public BossPattern
{
    using Super = BossPattern;
public:
    SmashAttack(shared_ptr<BossMonster> owner);
    virtual ~SmashAttack() override;

public:
    virtual void Begin() override;
    virtual void Tick(float deltaTime) override;
    virtual void End() override { _isFinished = true; }
    virtual bool IsFinished() override { return _isFinished; }

private:
    enum class SmashPhase
    {
        None,
        Move,
        Prepare,
        Attack,
        Done
    };

private:
    Vec2Int _targetPos = {};
    SmashPhase _phase = SmashPhase::None;
    float _elapsed = 0.f;
    float _prepareTime = 0.f;
    bool _isFinished = false;
};

