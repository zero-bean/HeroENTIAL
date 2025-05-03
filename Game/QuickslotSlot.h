#pragma once

#include "Slot.h"

class QuickslotSlot : public Slot
{
	using Super = Slot;
public:
	QuickslotSlot();
	virtual ~QuickslotSlot();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void UseItem();
};