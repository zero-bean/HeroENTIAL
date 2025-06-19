#pragma once

class BossMonster;

class BossPattern
{
public:
    BossPattern(shared_ptr<BossMonster> owner) : _owner(owner) {}
    virtual ~BossPattern() {}

public:
    virtual void Begin() {}
    virtual void Tick(float deltaTime) {}
    virtual void End() {}
    virtual bool IsFinished() = 0;

public:
    void SetReach(const int reach) { _reach = reach; }
    int GetReach() const { return _reach; }
    virtual void OnRangeReached() {};

    float GetCoolTime() const { return _coolTime; }

protected:
    shared_ptr<BossMonster> GetOwner() const { return _owner.lock(); }
    void SetOwner(const shared_ptr<BossMonster> owner) { _owner = owner; }

protected:
    weak_ptr<BossMonster> _owner;
    int _reach = 0;
    float _coolTime = 0.f;
};

