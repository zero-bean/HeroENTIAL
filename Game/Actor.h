#pragma once

class Actor : public enable_shared_from_this<Actor>
{
public: 
	Actor();
	virtual ~Actor();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

public:
	void SetPos(const Vec2& pos) { _pos = pos; }
	Vec2 GetPos() const { return _pos; }

	void SetLayer(const LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() const { return _layer; }

private:
	Vec2 _pos = { 0,0 };
	Vec2 _destPos = { 0, 0 };
	LAYER_TYPE _layer = LAYER_TYPE::LAYER_OBJECT;

};

