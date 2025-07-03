#include "pch.h"
#include "Slider.h"

Slider::Slider()
{
}

Slider::~Slider()
{
}

void Slider::BeginPlay()
{
    Super::BeginPlay();

    UpdateRects();
}

void Slider::Tick()
{
    Super::Tick();

    POINT mousePos = InputManager::GET_SINGLE()->GetMousePos();
    if (PtInRect(&_thumbRect, mousePos))
    {
        // 마우스를 계속 누르고 있는 중이면 갱신
        if (InputManager::GET_SINGLE()->GetButton(KeyType::LEFT_MOUSE))
        {
            POINT mousePos = InputManager::GET_SINGLE()->GetMousePos();
            float ratio = (mousePos.x - _trackRect.left) / float(_trackRect.right - _trackRect.left);
            _value = std::clamp(ratio, 0.0f, 1.0f);

            UpdateRects(); // 썸 위치 갱신

            if (_onValueChanged)
                _onValueChanged(_value);
        }
    }
}

void Slider::Render(HDC hdc)
{
    Super::Render(hdc);

    // 트랙 바
    HBRUSH trackBrush = CreateSolidBrush(RGB(30, 30, 30));
    FillRect(hdc, &_trackRect, trackBrush);
    DeleteObject(trackBrush);

    // 썸
    HBRUSH thumbBrush = CreateSolidBrush(RGB(60, 60, 120));
    FillRect(hdc, &_thumbRect, thumbBrush);
    DeleteObject(thumbBrush);
}

void Slider::SetRange(float min, float max)
{
    _min = min; 
    _max = max;
    UpdateRects();
}

void Slider::SetValue(float value)
{
    _value = clamp(value, _min, _max);
    UpdateRects();
}

void Slider::UpdateRects()
{
    const Vec2 pos = GetPos();
    const Vec2Int size = GetSize();
    int halfW = static_cast<int>(size.x / 2);
    int halfH = static_cast<int>(size.y / 2);

    _trackRect.left = static_cast<LONG>(pos.x - halfW);
    _trackRect.right = static_cast<LONG>(pos.x + halfW);
    _trackRect.top = static_cast<LONG>(pos.y - halfH);
    _trackRect.bottom = static_cast<LONG>(pos.y + halfH);

    // 썸 위치는 현재 value 기준으로 계산
    float ratio = (_value - _min) / (_max - _min);
    int thumbWidth = 20;
    int thumbHeight = static_cast<int>(size.y);

    int thumbCenterX = static_cast<int>(_trackRect.left + ratio * (size.x));
    _thumbRect.left = thumbCenterX - thumbWidth / 2;
    _thumbRect.right = thumbCenterX + thumbWidth / 2;
    _thumbRect.top = _trackRect.top;
    _thumbRect.bottom = _trackRect.bottom;
}
