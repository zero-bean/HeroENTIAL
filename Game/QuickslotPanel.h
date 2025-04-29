#pragma once
#include "Panel.h"

class QuickslotContainer;

class QuickslotPanel : public Panel
{
	using Super = Panel;
public:
	QuickslotPanel();
	virtual ~QuickslotPanel() override;

public:
	virtual void BeginPlay();
	virtual void Tick() override;
	virtual void Render(HDC hdc);

private:
	shared_ptr<QuickslotContainer> _container = nullptr;

};

