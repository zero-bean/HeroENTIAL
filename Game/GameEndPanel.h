#pragma once
#include "Panel.h"

class GameEndContainer;
class Button;
class Font;

class GameEndPanel : public Panel, public enable_shared_from_this<GameEndPanel>
{
	using Super = Panel;
public:
	GameEndPanel();
	virtual ~GameEndPanel() override;

public:
	virtual void BeginPlay();
	virtual void Tick() override;
	virtual void Render(HDC hdc);

public:
	void SetOutputContent(const wstring content) { _content = content; }

private:
	shared_ptr<GameEndContainer> _container = nullptr;
	shared_ptr<Button> _button = {};
	shared_ptr<Font> _font = {};
	wstring _content = L"You Failed!";
};

