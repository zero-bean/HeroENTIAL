#pragma once
#include "Panel.h"

class DungeonEnterContainer;
class Button;
class Font;

class DungeonEnterPanel : public Panel, public enable_shared_from_this<DungeonEnterPanel>
{
	using Super = Panel;
public:
	DungeonEnterPanel();
	virtual ~DungeonEnterPanel() override;

public:
	virtual void BeginPlay();
	virtual void Tick() override;
	virtual void Render(HDC hdc);

private:
	void SetButtonFunction(const int idx);

private:
	shared_ptr<DungeonEnterContainer> _container = nullptr;
	vector<shared_ptr<Button>> _buttons = {};
	shared_ptr<Font> _font = {};
};

