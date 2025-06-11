#pragma once

#include "FlipbookActor.h"

class GameObject : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	GameObject();
	virtual ~GameObject() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void AddCollider(const Vec2 size) {}

	// 타일맵 정보 관련
	virtual TILE_TYPE GetTileType() const { return TILE_TYPE::EMPTY; }
	virtual bool ShouldAffectTilemap() const { return true; }

protected:
	virtual void TickIdle() {}
	virtual void TickMove() {}

	virtual void UpdateAnimation() {}

public:
	void SetState(ObjectState state);
	ObjectState GetState() const { return _state; }

	Dir GetDir() const { return _dir; }
	void SetDir(Dir dir);

	bool HasReachedDest();
	bool CanGo(Vec2Int cellPos);
	Dir GetLookAtDir(Vec2Int cellPos);

	void SetCellPos(Vec2Int cellPos, bool teleport = false);
	Vec2Int GetCellPos() const { return _cellPos; }
	Vec2Int GetFrontCellPos();

	__int64 GetObjectID() const { return _objectID; }
	void SetObjectID(__int64 id) { _objectID = id; }

protected:
	__int64 _objectID = 0;
	Vec2Int _cellPos = {};
	Vec2 _speed = {};
	Dir _dir = DIR_RIGHT;
	Dir _animDir = DIR_RIGHT;
	ObjectState _state = ObjectState::Idle;
};

