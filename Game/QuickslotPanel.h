#pragma once
#include "Panel.h"

class QuickslotContainer;
class QuickslotSlot;
class Inventory;

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

public:
	void SetSlotsOwnerPtr(shared_ptr<Inventory> inventory);

private:
	shared_ptr<QuickslotContainer> _container = nullptr;
	vector<shared_ptr<QuickslotSlot>> _slots = {};
};

