#include "pch.h"
#include "Item.h"
#include "Inventory.h"
#include "Flipbook.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Player.h"
#include "DevScene.h"
#include "CollisionManager.h"
#include "SceneManager.h"

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

void Item::AddCollider()
{
	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->SetSize({ 32, 32 });
	shared_from_this()->AddComponent(collider);
	CollisionManager::GET_SINGLE()->AddCollider(collider);
}

void Item::OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
	shared_ptr<BoxCollider> another = dynamic_pointer_cast<BoxCollider>(other);

	auto player = static_pointer_cast<Player>(another->GetOwner());
	if (player)
	{
		SetCanPickedUp(true);
	}
}

void Item::OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
	shared_ptr<BoxCollider> another = dynamic_pointer_cast<BoxCollider>(other);

	auto player = static_pointer_cast<Player>(another->GetOwner());
	if (player && GetCanPickedUp())
	{
		SetCanPickedUp(false);
	}
}

void Item::UpdateAnimation()
{
	SetFlipbook(_flipbook);
}

void Item::PickedUp(shared_ptr<Player> player)
{
	shared_ptr<Item> item = dynamic_pointer_cast<Item>(shared_from_this());
	shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene)
		scene->PickUpItem(item, player);
}
