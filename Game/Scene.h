#pragma once
#include <memory>

class Actor;
class GameObject;
class TilemapActor;
class Player;
class Item;

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

protected:
	virtual void OnPhaseEnter(ScenePhase phase) {}

public:
	virtual void AddActor(shared_ptr<Actor> actor);
	virtual void RemoveActor(shared_ptr<Actor> actor);

	virtual bool CanGo(Vec2Int cellPos);
	virtual Vec2 ConvertPos(Vec2Int cellPos);

public:
	shared_ptr<GameObject> GetGameObjectAt(const Vec2Int cellPos);
	Vec2Int GetClosestEmptyCellPos(const Vec2Int& center);

public:
	void NotifyObjectMoved(shared_ptr<GameObject> obj, const Vec2Int oldPos, const Vec2Int newPos);

public:
	void MarkTileType(const Vec2Int pos, const TILE_TYPE tileType);
	void PickUpItem(shared_ptr<Item> item, shared_ptr<Player> player);
	void DropItem(shared_ptr<Item> item, Vec2Int pos);
	void TryPickUpItem(const Vec2Int centerPos);

	void UpdateCellPos(shared_ptr<GameObject> obj);

public:
	template<typename T>
	shared_ptr<T> FindActor()
	{
		for (const auto& layer : _actors)
		{
			for (const auto& actor : layer)
			{
				if (shared_ptr<T> casted = dynamic_pointer_cast<T>(actor))
					return casted;
			}
		}

		return nullptr;
	}

private:
	void ProcessAddActor();
	void ProcessRemoveActor();

protected:
	queue<shared_ptr<Actor>> _addQueue;
	queue<shared_ptr<Actor>> _removeQueue;
	vector<shared_ptr<Actor>> _actors[LAYER_MAXCOUNT];
	shared_ptr<TilemapActor> _tilemapActor = nullptr;

	// Scene Update 로직 관련 변수
	vector<bool> _isLayerUpdateEnabled;
	ScenePhase _phase = ScenePhase::Normal;
	ScenePhase _prevPhase = ScenePhase::None;
	float _phaseElapsed = 0.f;
};

