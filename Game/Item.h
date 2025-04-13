#pragma once

#include "GameObject.h"

class Actor;
class Collider;
class Player;

enum class ItemType
{
	None,
	Equipment,
	Consumable,
	Others,
	MAX_COUNT
};

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

	virtual void AddCollider() override;
	
	virtual void Use() {}
	virtual void DisUse() {}

	virtual void OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;
	virtual void OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;
	
protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}

	virtual void UpdateAnimation() override;

public:
	void SetOwner(shared_ptr<Actor> owner) { _owner = owner; }
	shared_ptr<Actor> GetOwner() { return _owner.lock(); }

	void SetItemType(ItemType type) { _itemType = type; }
	ItemType GetItemType() const { return _itemType; }

	int GetItemTypeIndex() { return static_cast<int>(_itemType) - 1; }

	void SetItemRarity(ItemRarity rarity) { _rarity = rarity; }
	ItemRarity GetItemRarity() const { return _rarity; }

	void SetItemContent(ItemContent itemContent) { _itemContent = itemContent; }
	ItemContent GetItemContent() const { return _itemContent; }

	void SetItemCount(unsigned __int32 count) { _itemCount = min(count, 999u); }
	void AddItemCount(unsigned __int32 count) { _itemCount = min(_itemCount + count, 999u); }
	unsigned __int32 GetItemCount() const { return _itemCount; }

	void SetCanPickedUp(bool canPickedUp) { _canPickedUp = canPickedUp; }
	bool GetCanPickedUp() const { return _canPickedUp; }

	void PickedUp(shared_ptr<Player> player);

protected:
	weak_ptr<Actor> _owner;
	ItemRarity _rarity = ItemRarity::Common;
	ItemType _itemType = ItemType::None;
	ItemContent _itemContent = {};
	unsigned __int32 _itemCount = 1;
	bool _canPickedUp = false;
};

