#pragma once

#include "UI.h"

class Sprite;

class Panel : public UI
{
	using Super = UI;
public:
	Panel();
	virtual ~Panel();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

public:
	vector<shared_ptr<UI>> GetChildren() const { return _children; }
	void AddChild(shared_ptr<UI> ui);
	bool RemoveChild(shared_ptr<UI> ui);

protected:
	vector<shared_ptr<UI>> _children;
};

