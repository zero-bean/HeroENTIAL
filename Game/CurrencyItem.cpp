#include "pch.h"
#include "CurrencyItem.h"

CurrencyItem::CurrencyItem()
{
	SetItemType(ItemType::Currency);
	UpdateAnimation();
}

CurrencyItem::~CurrencyItem()
{
}

void CurrencyItem::BeginPlay()
{
	Super::BeginPlay();
}

void CurrencyItem::Tick()
{
	Super::Tick();
}

void CurrencyItem::Render(HDC hdc)
{
	Super::Render(hdc);
}

void CurrencyItem::UpdateAnimation()
{
	switch (GetItemRarity())
	{
	case ItemRarity::Common:
		SetFlipbook(ResourceManager::GET_SINGLE()->GetFlipbook(L"Coin"));
		SetItemContent({ L"동전", L"소량의 재화를 획득할 수 있다." });
		SetObjectID(100);
		_itemCount = 100;
		break;
	}
}
