#pragma once
#include "UI.h"

class Sprite;

class WarningBannerUI : public UI
{
	using Super = UI;
public:
	WarningBannerUI();
	virtual ~WarningBannerUI();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
	shared_ptr<Sprite> _sprite;
	float _scrollOffsetTop = 0.f;
	float _scrollOffsetBottom = 0.f;
	float _scrollSpeed = 100.f;
	__int32 _imageWidth = 1366;
	__int32 _imageHeight = 144;
};

