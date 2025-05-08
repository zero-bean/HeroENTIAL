#pragma once
#include "UI.h"

class Sprite;

class DungeonEnterContainer : public UI
{
	using Super = UI;
public:
	DungeonEnterContainer();
	virtual ~DungeonEnterContainer() override;

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
	vector<shared_ptr<Sprite>> _sprites;
};

