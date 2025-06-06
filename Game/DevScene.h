#pragma once
#include "Scene.h"
#include <type_traits>

class Actor;
class TilemapActor;
class Creature;
class Player;
class GameObject;
class Item;
class Potion;
class UI;
class Monster;

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
	void LoadMonster();
	void LoadBullet();
	void LoadEffect();
	void LoadItem();
	void LoadUI(shared_ptr<Player> player);

public:
	void MarkTileHasItem(const Vec2Int pos, const bool check);

	void PickUpItem(shared_ptr<Item> item, shared_ptr<Player> player);
	void DropItem(shared_ptr<Item> item, Vec2Int pos);

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

	template<typename T>
	shared_ptr<T> SpawnObjectAtRandomPos()
	{
		Vec2Int randPos = GetRandomEmptyCellPos();

		return SpawnMonster<T>(randPos);
	}

	Vec2Int GetRandomEmptyCellPos();
	Vec2Int GetClosestEmptyCellPos(const Vec2Int& center);

	weak_ptr<Player> FindClosestPlayer(Vec2Int pos);

	bool FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, __int32 maxDepth = 10);

private:
	const __int32 DESIRED_COUNT = 3;
	__int32 _monsterCount = 0;

};

