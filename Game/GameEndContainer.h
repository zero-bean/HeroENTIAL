#pragma once
#include "UI.h"

class Sprite;

class GameEndContainer : public UI
{
	using Super = UI;
public:
	GameEndContainer();
	virtual ~GameEndContainer() override;

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
	shared_ptr<Sprite> _sprite;
};

