#include "pch.h"
#include "WarningBannerUI.h"
#include "Sprite.h"

WarningBannerUI::WarningBannerUI()
{
	_sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Effect_Warning");
	_isVisible = true;
}

WarningBannerUI::~WarningBannerUI()
{
}

void WarningBannerUI::BeginPlay()
{
	_imageWidth = _sprite->GetSize().x;
	_imageHeight = _sprite->GetSize().y;
	
	Super::BeginPlay();
}

void WarningBannerUI::Tick()
{
	Super::Tick();

	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	_scrollOffsetTop -= _scrollSpeed * deltaTime;
	if (_scrollOffsetTop <= -_imageWidth)
		_scrollOffsetTop += _imageWidth;

	_scrollOffsetBottom += _scrollSpeed * deltaTime;
	if (_scrollOffsetBottom >= _imageWidth)
		_scrollOffsetBottom -= _imageWidth;
}

void WarningBannerUI::Render(HDC hdc)
{
    Super::Render(hdc);
    if (!GetVisible())
        return;

    // 상단
    for (int i = 0; i < 2; ++i)
    {
        float x = -_scrollOffsetTop + (i - 1) * _imageWidth;
        ::StretchBlt(
            hdc,
            static_cast<__int32>(x),
            0,
            _imageWidth,
            _imageHeight,
            _sprite->GetDC(),
            _sprite->GetPos().x,
            _sprite->GetPos().y,
            _imageWidth,
            _imageHeight,
            SRCCOPY
        );
    }

    // 하단
    for (int i = 0; i < 2; ++i)
    {
        float x = -_scrollOffsetBottom + i * _imageWidth;
        ::StretchBlt(
            hdc,
            static_cast<__int32>(x),
            GWinSizeY - _imageHeight,
            _imageWidth,
            _imageHeight,
            _sprite->GetDC(),
            _sprite->GetPos().x,
            _sprite->GetPos().y,
            _imageWidth,
            _imageHeight,
            SRCCOPY
        );
    }
}
