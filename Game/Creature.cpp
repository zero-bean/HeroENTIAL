#include "pch.h"
#include "Creature.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Flipbook.h"
#include "Projectile.h"
#include "CameraComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "DevScene.h"
#include "HPbar.h"
#include "DamageSkin.h"

Creature::Creature()
{

}

Creature::~Creature()
{

}

void Creature::BeginPlay()
{
	Super::BeginPlay();

	_hpBar = make_shared<HPbar>();
	_hpBar->SetOwner(dynamic_pointer_cast<Creature>(shared_from_this()));
	UIManager::GET_SINGLE()->AddUI(_hpBar);
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
		SetState(ObjectState::Death);
	else
		SetState(ObjectState::Attacked);
}

void Creature::OnDamaged(shared_ptr<Projectile> projectile)
{
	if (!projectile)
		return;

	__int32 attack = projectile->GetAttack();
	Stat& stat = GetStat();

	__int32 damage = attack - stat.defence;
	if (damage <= 0)
		return;

	stat.hp = max(0, stat.hp - damage);
	if (stat.hp == 0)
		SetState(ObjectState::Death);
	else
		SetState(ObjectState::Attacked);

	// 피격 데미지 이펙트 추가
	shared_ptr<DamageSkin> dmg = make_shared<DamageSkin>();
	dmg->SetDamage(stat.attack);
	dmg->SetPos(GetPos() + Vec2(0, -60));
	dmg->SetFont(ResourceManager::GET_SINGLE()->GetFont(L"DungeonFont"));
	dmg->SetColor(RGB(255, 80, 80));
	SceneManager::GET_SINGLE()->GetCurrentScene()->AddActor(dmg);
}
