#include "pch.h"
#include "Item.h"
#include "Inventory.h"
#include "Flipbook.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Scene.h"

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

void Item::UpdateAnimation()
{
	SetFlipbook(_flipbook);
}
