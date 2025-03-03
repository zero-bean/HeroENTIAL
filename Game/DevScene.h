#pragma once

#include "Scene.h"
#include <type_traits>

class Actor;
class TilemapActor;
class Creature;
class Player;
class GameObject;
class UI;
class Monster;

struct PQNode
{
	PQNode(__int32 cost, Vec2Int pos) : cost(cost), pos(pos) { }

	bool operator<(const PQNode& other) const { return cost < other.cost; }
	bool operator>(const PQNode& other) const { return cost > other.cost; }

	__int32 cost;
	Vec2Int pos;
};

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

	template<typename T>
	shared_ptr<T> SpawnObjectAtRandomPos()
	{
		Vec2Int randPos = GetRandomEmptyCellPos();

		return SpawnMonster<T>(randPos);
	}

	Vec2Int GetRandomEmptyCellPos();

	weak_ptr<Player> FindClosestPlayer(Vec2Int pos);

	bool FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, __int32 maxDepth = 10);

private:
	shared_ptr<TilemapActor> _tilemapActor = nullptr;
	const __int32 DESIRED_COUNT = 3;
	__int32 _monsterCount = 0;

};

