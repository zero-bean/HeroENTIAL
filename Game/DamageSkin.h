#pragma once
#include "GameObject.h"

class Font;

class DamageSkin : public GameObject
{
    using Super = GameObject;
public:
    DamageSkin();
    virtual ~DamageSkin();

public:
    virtual void Tick() override;
    virtual void Render(HDC hdc) override;

public:
    void SetDamage(int value) { _text = to_wstring(value); }
    void SetColor(COLORREF color) { _color = color; }
    void SetFont(shared_ptr<Font> font) { _font = font; }
    void SetTimer(float timer) { _timer = timer; }

protected:
    void OnDestroyed();

private:
    shared_ptr<Font> _font;
    wstring _text;        
    float _floatSpeed = 10.f;
    float _timer = 1.5f;
    COLORREF _color = RGB(255, 255, 0);
};

