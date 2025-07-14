#pragma once
#include "Panel.h"

class QuestContainer;
class QuestSlot;
class Button;

class QuestPanel : public Panel, public enable_shared_from_this<QuestPanel>
{
	using Super = Panel;
public:
	QuestPanel();
	virtual ~QuestPanel() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	void Refresh();
	void OnScrollUp();
	void OnScrollDown();

private:
	shared_ptr<QuestContainer> _container = nullptr;
	vector<shared_ptr<Button>> _buttons = {};
	vector<shared_ptr<QuestSlot>> _slots = {};
	int _scrollOffset = 0;
	const int _slotHeight = 100;
	const int _visibleSlotCount = 4;
	const int _panelHeight = _slotHeight * _visibleSlotCount;
};

