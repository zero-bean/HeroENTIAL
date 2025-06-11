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
    enum class Phase
    {
        None,
        MoveToTarget,
        Attack,
        Done
    };

private:
    Vec2Int _targetPos = {};
    Phase _phase = Phase::None;
    bool _isFinished = false;
    bool _animationPlayed = false;
};

