#pragma once

#include "Consumable.h"

class Player;

enum class PotionType
{
	Burger,
	Steak,
	Sandwitch
};

class Potion : public Consumable
{
	using Super = Consumable;
public:
	Potion();
	virtual ~Potion() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void Use() override;
	virtual void DisUse() override {}

	virtual void OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;
	virtual void OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;

public:
	void SetPotionType(PotionType type) { _type = type; }
	PotionType GetPotionType() const { return _type; }

private:
	virtual void TickIdle() override;
	virtual void TickMove() override {}

private:
	PotionType _type = PotionType::Burger;
	static std::unordered_map<PotionType, function<void(shared_ptr<Player>&)>> _effect;
};

