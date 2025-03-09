#include "pch.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Actor.h"

BoxCollider::BoxCollider() : Collider(ColliderType::Box)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();


}

void BoxCollider::TickComponent()
{
	Super::TickComponent();


}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
	Vec2 pos = GetOwner()->GetPos();
	pos.x -= cameraPos.x - static_cast<float>(GWinSizeX / 2);
	pos.y -= cameraPos.y - static_cast<float>(GWinSizeY / 2);

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, pos, static_cast<int>(_size.x), static_cast<int>(_size.y));
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool BoxCollider::CheckCollision(shared_ptr<Collider> other)
{
	if (Super::CheckCollision(other) == false)
		return false;

	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionBox2Box(dynamic_pointer_cast<BoxCollider>(shared_from_this()), dynamic_pointer_cast<BoxCollider>(other));
	}

	return false;
}

RECT BoxCollider::GetRect()
{
	Vec2 pos = GetOwner()->GetPos();
	Vec2 size = GetSize();

	RECT rect =
	{
		static_cast<__int32>(pos.x - (size.x / 2)),
		static_cast<__int32>(pos.y - (size.y / 2)),
		static_cast<__int32>(pos.x + (size.x / 2)),
		static_cast<__int32>(pos.y + (size.y / 2))
	};

	return rect;
}
