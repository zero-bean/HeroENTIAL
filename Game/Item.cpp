#include "pch.h"
#include "Item.h"
#include "Flipbook.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Player.h"
#include "CollisionManager.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::BeginPlay()
{
	Super::BeginPlay();

}

void Item::Tick()
{
	Super::Tick();

}

void Item::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Item::OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{

	shared_ptr<BoxCollider> b1 = dynamic_pointer_cast<BoxCollider>(collider);
	shared_ptr<BoxCollider> b2 = dynamic_pointer_cast<BoxCollider>(other);

	auto player = static_pointer_cast<Player>(b2->GetOwner());
	if (player)
	{
		CollisionManager::GET_SINGLE()->RemoveCollider(b1);
		/* 인벤토리로 이동 */
		return;
	}
}

void Item::OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
}

void Item::UpdateAnimation()
{
	SetFlipbook(_flipbook);
}
