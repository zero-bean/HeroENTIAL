#include "pch.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Actor.h"

BoxCollider::BoxCollider()
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
	pos.x -= coorPos.x + cameraPos.x - static_cast<float>(GWinSizeX / 2);
	pos.y -= coorPos.y + cameraPos.y - static_cast<float>(GWinSizeY / 2);

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

	auto self = dynamic_pointer_cast<BoxCollider>(shared_from_this());

	return CheckCollisionBox2Box(self, dynamic_pointer_cast<BoxCollider>(other));
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
