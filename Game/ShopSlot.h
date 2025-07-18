#pragma once
#include "UI.h"

class Item;
class Button;
class Font;

class ShopSlot : public UI, public enable_shared_from_this<ShopSlot>
{
	using Super = UI;
public:
	ShopSlot();
	virtual ~ShopSlot();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetItem(shared_ptr<Item> item) { _item = item; }
	shared_ptr<Item> GetItem() const { return _item; }

private:
	shared_ptr<Item> _item = nullptr;
	shared_ptr<Button> _button = nullptr;
	shared_ptr<Font> _font = nullptr;
};

