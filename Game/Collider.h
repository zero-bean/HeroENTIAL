#pragma once

#include "Component.h"

class BoxCollider;

class Collider : public Component
{
public:
	Collider();
	virtual ~Collider() override;

public:
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(shared_ptr<Collider> other);

public:
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

	void SetCoorPos(Vec2 pos) { coorPos = pos; }

public:
	struct WeakPtrHash
	{
		size_t operator()(const weak_ptr<Collider>& wp) const noexcept
		{
			if (auto sp = wp.lock())
				return hash<shared_ptr<Collider>>{}(sp);
			
			return 0; // expired weak_ptr은 0으로 해싱
		}
	};

	// Collider 클래스의 포인터를 비교하는 동등성 비교 함수
	struct WeakPtrEqual
	{
		bool operator()(const weak_ptr<Collider>& lhs, const weak_ptr<Collider>& rhs) const noexcept
		{
			return !lhs.owner_before(rhs) && !rhs.owner_before(lhs); // owner_less와 동일한 비교
		}
	};

	unordered_set<weak_ptr<Collider>, WeakPtrHash, WeakPtrEqual> _collisionMap;

protected:
	// 나는 누구인가?
	COLLISION_LAYER_TYPE _collisionLayer = CLT_OBJECT;
	// 누구랑 충돌할 것인가?
	unsigned __int32 _collisionFlag = 0x00000000;
	bool _showDebug = false;
	Vec2 coorPos = { 0, 0 };
};
