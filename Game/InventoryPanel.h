#pragma once

#include "Panel.h"

class Inventory;
class InventorySlot;
class InventoryContainer;
class InventoryTooltip;
class Button;

struct DragState
{
public:
	void BeginDrag(shared_ptr<InventorySlot> slot)
	{
		active = true;
		this->slot = slot;
	}

	void EndDrag()
	{
		active = false;
		slot = nullptr;
	}

	bool IsDrag() const { return active; }

	shared_ptr<InventorySlot> GetSlot() const { return slot; }

private:
	bool active = false;
	shared_ptr<InventorySlot> slot = nullptr;
};

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
	
	void DropDraggedItem();

private:
	bool _isActivated = true;
	DragState _drag = {};
	shared_ptr<InventoryContainer> _container = nullptr;
	vector<shared_ptr<Button>> _buttons = {};
	vector<shared_ptr<InventorySlot>> _slots = {};
	shared_ptr<InventoryTooltip> _tooltip = nullptr;
	weak_ptr<Inventory> _inventory = {};
};

