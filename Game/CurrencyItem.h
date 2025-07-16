#pragma once
#include "Item.h"

class CurrencyItem : public Item
{
	using Super = Item;
public:
	CurrencyItem();
	virtual ~CurrencyItem() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateAnimation() override;
};

