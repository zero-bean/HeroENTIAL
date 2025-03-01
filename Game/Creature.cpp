#include "pch.h"
#include "Creature.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "DevScene.h"

Creature::Creature()
{

}

Creature::~Creature()
{

}

void Creature::BeginPlay()
{
	Super::BeginPlay();
}

void Creature::Tick()
{
	Super::Tick();

	switch (_state) 
	{
	case ObjectState::Attack:
		TickAttack();
		break;
	case ObjectState::Attacked:
		TickAttacked();
		break;
	case ObjectState::Death:
		TickDeath();
		break;
	case ObjectState::Birth:
		TickBirth();
		break;
	}
}

void Creature::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Creature::OnDamaged(shared_ptr<Creature> attacker)
{
	if (!attacker)
		return;

	Stat& attackerStat = attacker->GetStat();
	Stat& stat = GetStat();

	__int32 damage = attackerStat.attack - stat.defence;
	if (damage <= 0)
		return;

	stat.hp = max(0, stat.hp - damage);
	if (stat.hp == 0)
	{
		auto scene = SceneManager::GET_SINGLE()->GetCurrentScene();
		if (scene)
		{
			scene->RemoveActor(shared_from_this());
		}
	}
}
