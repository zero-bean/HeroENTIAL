#pragma once

#include "Component.h"

class BoxCollider;

class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider() override;

public:
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(shared_ptr<Collider> other);

public:
	ColliderType GetColliderType() const { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }

public:
	static bool CheckCollisionBox2Box(shared_ptr<BoxCollider> b1, shared_ptr<BoxCollider> b2);

	void SetCollisionLayer(COLLISION_LAYER_TYPE layer) { _collisionLayer = layer; }
	COLLISION_LAYER_TYPE GetCollisionLayer() const { return _collisionLayer; }

	void ResetCollisionFlag() { _collisionFlag = 0; }
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	void SetCollisionFlag(unsigned __int32 flag) { _collisionFlag = flag; }
	unsigned __int32 GetCollisionFlag() const { return _collisionFlag; }

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

public:
	unordered_set<shared_ptr<Collider>> _collisionMap;

protected:
	// ���� �����ΰ�?
	COLLISION_LAYER_TYPE _collisionLayer = CLT_OBJECT;
	// ������ �浹�� ���ΰ�?
	unsigned __int32 _collisionFlag = 0xFFFFFFFF; // ~(0)

};
