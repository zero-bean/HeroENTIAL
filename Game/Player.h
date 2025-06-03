#pragma once

#include "FlipbookActor.h"
#include "Creature.h"

class Flipbook;
class Inventory;
class Item;

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	virtual ~Player() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;
	virtual void OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;

	virtual TILE_TYPE GetTileType() const override { return TILE_TYPE::PLAYER; }

private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickAttack() override;
	virtual void TickDeath() override;
	virtual void TickBirth() override {}
	virtual void TickAttacked() override;
	void TickSkill() {};

	virtual void UpdateAnimation() override;

private:
	void SetWeaponType(WeaponType weaponType) { _weaponType = weaponType; }
	WeaponType GetWeaponType() const { return _weaponType; }

private:
	shared_ptr<Flipbook> _flipbookIdle[2] = {};
	shared_ptr<Flipbook> _flipbookMove[2] = {};
	shared_ptr<Flipbook> _flipbookAttack[2] = {};
	shared_ptr<Flipbook> _flipbookAttacked[2] = {};

	bool _keyPressed = false;
	WeaponType _weaponType = WeaponType::Sword;
};

