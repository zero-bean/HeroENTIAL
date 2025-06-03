#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Sprite.h"

Button::Button()
{

}

Button::~Button()
{

}

void Button::BeginPlay()
{
	Super::BeginPlay();

	SetButtonState(BS_Default);
}

void Button::Tick()
{
	Super::Tick();

	POINT mousePos = InputManager::GET_SINGLE()->GetMousePos();
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	if (_state == BS_Clicked)
	{
		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			_sumTime = 0.f;
			SetButtonState(BS_Default);
		}
	}

	if (IsMouseInRect())
	{
		if (InputManager::GET_SINGLE()->GetButton(KeyType::LEFT_MOUSE))
		{
			SetButtonState(BS_Pressed);
			// OnPressed
		}
		else
		{
			if (_state == BS_Pressed)
			{
				SetButtonState(BS_Clicked);
				// OnClicked
				if (_onClick)
					_onClick();
			}
		}
	}
	else
	{
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_currentSprite)
	{
		::TransparentBlt(hdc,
			(__int32)_pos.x - _size.x / 2,
			(__int32)_pos.y - _size.y / 2,
			_size.x,
			_size.y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().x,
			_currentSprite->GetPos().y,
			_currentSprite->GetSize().x,
			_currentSprite->GetSize().y,
			_currentSprite->GetTransparent());
	}

	if (_currentCoverSprite)
	{
		::TransparentBlt(hdc,
			(__int32)_pos.x - _size.x / 2,
			(__int32)_pos.y - _size.y / 2,
			_size.x,
			_size.y,
			_currentCoverSprite->GetDC(),
			_currentCoverSprite->GetPos().x,
			_currentCoverSprite->GetPos().y,
			_currentCoverSprite->GetSize().x,
			_currentCoverSprite->GetSize().y,
			_currentCoverSprite->GetTransparent());
	}
}

void Button::SetButtonState(ButtonState state)
{
	_state = state;

	if (_sprites[state])
		SetCurrentSprite(_sprites[state]);

	if (_coverSprites[state])
		SetCurrentCoverSprite(_coverSprites[state]);
}