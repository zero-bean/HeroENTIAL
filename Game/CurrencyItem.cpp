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
		SetItemContent({ L"����", L"�ҷ��� ��ȭ�� ȹ���� �� �ִ�." });
		SetObjectID(100);
		_itemCount = 100;
		break;
	}
}
