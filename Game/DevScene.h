#pragma once

#include "Scene.h"
#include <type_traits>

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

	void LoadMap();
	void LoadTileMap();
	void LoadPlayer();
	void LoadEffect();

public:
	bool CanGo(Vec2Int cellPos);
	Vec2 ConvertPos(Vec2Int cellPos);

public:
	template<typename T>
	shared_ptr<T> SpawnObject(const Vec2Int pos)
	{
		auto isGameObject = std::is_convertible_v<shared_ptr<T>, shared_ptr<GameObject>>;
		assert(isGameObject);

		shared_ptr<T> ret = make_shared<T>();
		ret->SetCellPos(pos, true);
		ret->SetScale(4);
		AddActor(ret);

		ret->BeginPlay();

		return ret;
	}

private:
	shared_ptr<TilemapActor> _tilemapActor = nullptr;
};

