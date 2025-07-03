#pragma once
#include "UI.h"

class Slider : public UI
{
	using Super = UI;
public:
    Slider();
    virtual ~Slider();

public:
    virtual void BeginPlay() override;
    virtual void Tick() override;
    virtual void Render(HDC hdc) override;
  
public:
    void SetRange(float min, float max);
    void SetValue(float value);
    float GetValue() const { return _value; }

    void SetOnValueChanged(function<void(float)> func) { _onValueChanged = func; }

private:
    void UpdateRects();

private:
    float _min = 0.0f;
    float _max = 1.0f;
    float _value = 1.0f;
    RECT _trackRect = {};
    RECT _thumbRect = {};

    function<void(float)> _onValueChanged;
};

