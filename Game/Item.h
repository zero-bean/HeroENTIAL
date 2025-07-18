#pragma once
#include "GameObject.h"

class Actor;
class Collider;
class Player;

enum class ItemRarity
{
	Common,
	Rare,
	Unique,
	Lengendary,
};

struct ItemContent
{
	wstring name;
	wstring desc;
	wstring eft;
};

class Item : public GameObject
{
	using Super = GameObject;
public:
	Item();
	virtual ~Item() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
	
	virtual void Use() {}
	virtual void DisUse() {}
	
	virtual TILE_TYPE GetTileType() const override { return TILE_TYPE::ITEM; }

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}

	virtual void UpdateAnimation() override;

public:
	void SetOwner(shared_ptr<Actor> owner) { _owner = owner; }
	shared_ptr<Actor> GetOwner() { return _owner.lock(); }

	void SetItemType(ItemType type) { _itemType = type; }
	ItemType GetItemType() const { return _itemType; }

	int GetItemTypeIndex() { return static_cast<int>(_itemType); }

	void SetItemRarity(ItemRarity rarity) { _rarity = rarity; }
	ItemRarity GetItemRarity() const { return _rarity; }

	void SetItemContent(ItemContent itemContent) { _itemContent = itemContent; }
	ItemContent GetItemContent() const { return _itemContent; }

	void SetItemCount(unsigned __int32 count) { _itemCount = max(min(count, 999u), 0u); }
	void AddItemCount(unsigned __int32 count) { _itemCount = min(_itemCount + count, 999u); }
	unsigned __int32 GetItemCount() const { return _itemCount; }

	void SetPrice(unsigned __int32 price) { _price = price; }
	unsigned __int32 GetPrice() const { return _price; }

public:
	void SetOnClick(function<void()> callback) { _onEmptyCallback = callback; }

protected:
	weak_ptr<Actor> _owner;
	ItemRarity _rarity = ItemRarity::Common;
	ItemType _itemType = ItemType::MAX_COUNT;
	ItemContent _itemContent = {};
	unsigned __int32 _itemCount = 1;
	unsigned __int32 _price = 0;

protected:
	// ������ ������ 0���� �Ǹ�, ���Կ��� ���� ��û�ϴ� �ݹ� �Լ�
	function<void()> _onEmptyCallback = {};
	void NotifyOnEmpty() { if (_onEmptyCallback) _onEmptyCallback(); }
};

