#pragma once
#include "UI.h"

class Sprite;

class QuestContainer : public UI
{
	using Super = UI;
public:
	QuestContainer();
	virtual ~QuestContainer() override;

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

private:
	shared_ptr<Sprite> _sprite = nullptr;
};

