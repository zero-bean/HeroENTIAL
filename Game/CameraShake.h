#pragma once

class CameraShake
{
public:
    void Start(ShakeType type);
    void Stop();
    void Update(float deltaTime);

    Vec2 GetOffset() const { return _offset; }
    bool IsShaking() const { return _isShaking; }

private:
    void ApplyShake(float deltaTime);

private:
    bool _isShaking = false;
    float _elapsed = 0.0f;
    float _duration = 0.0f;
    float _magnitude = 0.0f;
    float _frequency = 0.0f;

    Vec2 _offset = Vec2(0, 0);
};