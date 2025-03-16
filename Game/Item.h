#pragma once

#include "GameObject.h"

class Actor;
class Collider;

enum class ItemRarity
{
	Common,
	Rare,
	Unique,
	Lengendary,
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

	virtual void OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;
	virtual void OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;

protected:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}

	virtual void UpdateAnimation() override;

public:
	void SetOwner(weak_ptr<Actor> owner) { _owner = owner; }
	shared_ptr<Actor> GetOwner() { return _owner.lock(); }

	void SetItemRarity(ItemRarity rarity) { _rarity = rarity; }
	ItemRarity GetItemRarity() const { return _rarity; }

	void SetItemCount(unsigned __int32 count) { if (count <= 999) _itemCount = count; }
	unsigned __int32 GetItemCount() const { return _itemCount; }

protected:
	weak_ptr<Actor> _owner;
	ItemRarity _rarity = ItemRarity::Common;
	unsigned __int32 _itemCount = 0;
};

