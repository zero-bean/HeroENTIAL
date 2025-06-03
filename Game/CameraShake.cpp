#include "pch.h"
#include "CameraShake.h"

void CameraShake::Start(ShakeType type)
{
    _isShaking = true;
    _elapsed = 0.0f;
    _offset = Vec2(0, 0);

    switch (type)
    {
    case ShakeType::Explosion:
        _duration = 0.3f;
        _magnitude = 12.0f;
        _frequency = 60.0f;
        break;
    case ShakeType::Earthquake:
        _duration = 1.0f;
        _magnitude = 6.0f;
        _frequency = 25.0f;
        break;
    case ShakeType::HitRecoil:
        _duration = 0.15f;
        _magnitude = 8.0f;
        _frequency = 80.0f;
        break;
    case ShakeType::SubtlePulse:
        _duration = 1.5f;
        _magnitude = 2.0f;
        _frequency = 10.0f;
        break;
    }
}

void CameraShake::Stop()
{
    _isShaking = false;
    _elapsed = 0.0f;
    _offset = Vec2(0, 0);
}

void CameraShake::Update(float deltaTime)
{
    if (!_isShaking)
        return;

    _elapsed += deltaTime;

    if (_elapsed >= _duration)
    {
        Stop();
        return;
    }

    ApplyShake(deltaTime);
}

void CameraShake::ApplyShake(float deltaTime)
{
    float angle = (rand() % 360) * PI / 180.0f;
    float strength = sin(_elapsed * _frequency) * _magnitude;

    _offset.x = cos(angle) * strength;
    _offset.y = sin(angle) * strength;
}
