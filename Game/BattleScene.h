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
class BossMonster;

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

protected:
	virtual void LoadResources() {};
	virtual void LoadMap() {};
	virtual void LoadTileMap() {};
	virtual void LoadPlayer() {};
	virtual void LoadUI() {};
	virtual void LoadSound() {};
	virtual void LoadCamera() {};
	void InitObjects();

protected:
	// ScenePhase ���� ���� ���
	virtual void OnPhaseEnter(ScenePhase newPhase) override;
	virtual void PlayBossIntroStart();
	virtual void PlayBossIntroEnd();

public:
	void NotifyPlayerOnDied();
	void NotifyMonsterOnDied();

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
		const Vec2Int p = GetClosestEmptyCellPos(pos);
		ret->SetCellPos(p, true);
		ret->SetScale(4);
		AddActor(ret);

		ret->BeginPlay();

		return ret;
	}

	template<typename T>
	shared_ptr<T> SpawnObjectAtRandomPos()
	{
		Vec2Int randPos = GetRandomEmptyCellPos();

		return SpawnObject<T>(randPos);
	}

	Vec2Int GetRandomEmptyCellPos();

	shared_ptr<Player> FindClosestPlayer(Vec2Int pos);

	bool FindPath(Vec2Int src, Vec2Int dest, vector<Vec2Int>& path, __int32 maxDepth = 10);

protected:
	__int32 _monsterCount = 0;
};

