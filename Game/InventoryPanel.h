#pragma once

#include "Panel.h"

class Inventory;
class InventoryContainer;
class InventoryTooltip;
class Slot;
class Button;

class InventoryPanel : public Panel, public enable_shared_from_this<InventoryPanel>
{
	using Super = Panel;
public:
	InventoryPanel();
	virtual ~InventoryPanel() override;

public:
	virtual void BeginPlay();
	virtual void Tick() override;
	virtual void Render(HDC hdc);

public:
	void SetInventory(shared_ptr<Inventory> inventory) { _inventory = inventory; }

	void OnClickEquitmentButton();
	void OnClickConsumableButton();
	void OnClickOthersButton();

private:
	void UpdateSlots(const ItemType idx);
	
	void DropDraggedItem();

private:
	shared_ptr<InventoryContainer> _container = nullptr;
	vector<shared_ptr<Button>> _buttons = {};
	vector<shared_ptr<Slot>> _slots = {};
	shared_ptr<InventoryTooltip> _tooltip = nullptr;
	weak_ptr<Inventory> _inventory = {};
};

