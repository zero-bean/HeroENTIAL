#pragma once

#include "Consumable.h"

class Player;

enum class PotionType
{
	None,
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

	virtual void UpdateAnimation() override;

	virtual void Use() override;
	virtual void DisUse() override {}

public:
	void SetPotionType(PotionType type);
	PotionType GetPotionType() const { return _type; }

private:
	PotionType _type = PotionType::None;
	static std::unordered_map<PotionType, function<void(shared_ptr<Player>&)>> _effect;
};

