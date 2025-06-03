#pragma once

class UI
{
public:
	UI();
	virtual ~UI();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

public:
	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() const { return _pos; }

	void SetSize(Vec2Int size) { _size = size; }
	Vec2Int GetSize() const { return _size; }

	virtual void SetVisible(bool visible) { _isVisible = visible; }
	bool GetVisible() const { return _isVisible; }

	RECT GetRect();
	bool IsMouseInRect();

protected:
	bool _isVisible = false;
	Vec2	_pos = { 400, 300 };
	Vec2Int _size = { 150, 150 };
};

