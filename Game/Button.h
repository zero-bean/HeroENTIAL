#pragma once
#include "UI.h"

class Sprite;

enum ButtonState
{
	BS_Default,
	//BS_Hovered,
	BS_Pressed,
	BS_Clicked,
	// ...
	BS_MaxCount
};

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void	SetSize(Vec2Int size) { _size = size; }
	shared_ptr<Sprite> GetSprite(ButtonState state) { return _sprites[state]; }

	void SetCurrentSprite(shared_ptr<Sprite> sprite) { _currentSprite = sprite; }
	void SetSprite(shared_ptr<Sprite> sprite, ButtonState state) { _sprites[state] = sprite; }
	void SetButtonState(ButtonState state);

protected:
	shared_ptr<Sprite> _currentSprite = nullptr;
	shared_ptr<Sprite> _sprites[BS_MaxCount] = {};
	ButtonState _state = BS_Default;
	// ...
	float _sumTime = 0.f;

public:
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
			{
				(owner->*func)();
			};
	}

	// 함수 포인터 + 함수 객체
	std::function<void(void)> _onClick = nullptr;
};


