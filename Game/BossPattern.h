#pragma once

class BossMonster;

class BossPattern
{
public:
    BossPattern() {}
    virtual ~BossPattern() {}

public:
    virtual void Begin() {}
    virtual void Tick(float deltaTime) {}
    virtual void End() {}
    virtual void Interrupt() {}
};

