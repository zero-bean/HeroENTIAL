#pragma once

#include "Item.h"

enum class ConsumableType
{
	None,
	Potion,
	Buff,
	Currency,
	Special
};

class Consumable : public Item
{
	using Super = Item;
public:
	Consumable();
	virtual ~Consumable() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void Use() override {}
	virtual void DisUse() override {}

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}

};

