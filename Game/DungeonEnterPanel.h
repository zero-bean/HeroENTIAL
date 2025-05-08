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

public:
	void SetIsActivated(bool isActivated) { _isActivated = isActivated; }
	bool GetIsActivated() const { return _isActivated; }

private:
	void SetButtonFunction();

private:
	bool _isActivated = false;
	shared_ptr<DungeonEnterContainer> _container = nullptr;
	vector<shared_ptr<Button>> _buttons = {};
	shared_ptr<Font> _font = {};
};

