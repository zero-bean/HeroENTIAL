#include "pch.h"
#include "BoxCollider.h"
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

	if (!_showDebug)
		return;

	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
	float cameraZoom = SceneManager::GET_SINGLE()->GetCameraZoom();

	Vec2 pos = GetOwner()->GetPos();
	Vec2 renderPos = (pos - coorPos - cameraPos) * cameraZoom + Vec2(GWinSizeX / 2.0f, GWinSizeY / 2.0f);
	Vec2 scaledSize = _size * cameraZoom;

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);

	Utils::DrawRect(hdc, renderPos, static_cast<int>(scaledSize.x), static_cast<int>(scaledSize.y));

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
