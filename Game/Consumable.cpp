#include "pch.h"
#include "Consumable.h"
#include "SceneManager.h"
#include "Scene.h"

Consumable::Consumable()
{
	SetItemType(ItemType::Consumable);
}

Consumable::~Consumable()
{
}

void Consumable::BeginPlay()
{
	Super::BeginPlay();

}

void Consumable::Tick()
{
	Super::Tick();

}

void Consumable::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Consumable::Use()
{
	Super::Use();


}

