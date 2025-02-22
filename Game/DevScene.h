#pragma once

#include "Scene.h"

class Actor;
class TilemapActor;
class Creature;
class Player;
class GameObject;
class UI;

class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene() override;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	void LoadMap();

public:
	bool CanGo(Vec2Int cellPos);
	Vec2 ConvertPos(Vec2Int cellPos);

private:
	class shared_ptr<TilemapActor> _tilemapActor = nullptr;
};

