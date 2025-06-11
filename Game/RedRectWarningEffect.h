#pragma once
#include "Effect.h"
class RedRectWarningEffect : public Effect
{
	using Super = Effect;
public:
    RedRectWarningEffect();
    virtual ~RedRectWarningEffect() override;

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void Render(HDC hdc) override;

public:
    void SetSize(const Vec2& size) { _size = size; }
    void SetDuration(float time) { _duration = time; }

private:
    Vec2 _size = { 64.f, 64.f };
};

