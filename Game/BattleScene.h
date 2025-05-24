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

class BattleScene : public Scene
{
	using Super = Scene;
public:
	BattleScene();
	virtual ~BattleScene() override;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	virtual void MarkTileHasItem(const Vec2Int pos, const bool check);
	virtual void PickUpItem(shared_ptr<Item> item, shared_ptr<Player> player);
	virtual void DropItem(shared_ptr<Item> item, Vec2Int pos);

protected:
	virtual void LoadMap() {};
	virtual void LoadTileMap() {};
	virtual shared_ptr<Player> LoadPlayer() { return nullptr; }
	virtual void LoadMonster() {};
	virtual void LoadBullet() {};
	virtual void LoadEffect() {};
	virtual void LoadItem() {};
	virtual void LoadUI(shared_ptr<Player> player) {};

	virtual void InitObjects();

protected:
	ObjectConfig ParseObjectConfig(const wstring& meta);
	Rank ParseRank(const wstring& rankStr);
	
	void SpawnObjectFromTile(const Vec2Int& pos, TILE_TYPE type, const std::wstring& meta);
	void SpawnMonster(const Vec2Int pos, const ObjectConfig& config);

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

	shared_ptr<Player> FindClosestPlayer(Vec2Int pos);

	bool FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, __int32 maxDepth = 10);

protected:
	const __int32 DESIRED_COUNT = 3;
	__int32 _monsterCount = 0;
};

