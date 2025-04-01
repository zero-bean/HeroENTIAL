#pragma once

#include "Panel.h"

class Inventory;
class InventorySlot;
class InventoryContainer;
class InventoryTooltip;
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
	void UpdateSlots(const int idx);

private:
	bool _isActivated = true;
	weak_ptr<Inventory> _inventory = {};
	shared_ptr<InventoryContainer> _container = nullptr;
	shared_ptr<InventoryTooltip> _tooltip = nullptr;
	vector<shared_ptr<Button>> _buttons = {};
	vector<shared_ptr<InventorySlot>> _slots = {};
};

