#include "pch.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Actor.h"

Collider::Collider(ColliderType colliderType) : _colliderType(colliderType)
{

}

Collider::~Collider()
{

}

void Collider::BeginPlay()
{

}

void Collider::TickComponent()
{

}

void Collider::Render(HDC hdc)
{

}

bool Collider::CheckCollision(shared_ptr<Collider> other)
{
	unsigned __int8 layer = other->GetCollisionLayer();
	if (_collisionFlag & (1 << layer))
		return true;

	return false;
}

// https://m.blog.naver.com/winterwolfs/10165506488
bool Collider::CheckCollisionBox2Box(shared_ptr<BoxCollider> b1, shared_ptr<BoxCollider> b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();
	RECT intersect = {};

	return ::IntersectRect(&intersect, &r1, &r2);
}

void Collider::AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag |= (1 << layer);
}

void Collider::RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag &= ~(1 << layer);
}
