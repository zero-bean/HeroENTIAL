#include "pch.h"
#include "Creature.h"
#include "BossMonster.h"
#include "Projectile.h"
#include "DamageSkin.h"
#include "BattleScene.h"
#include "BossPattern.h"

BossMonster::BossMonster()
{
	SetRank(Rank::Boss);
}

BossMonster::~BossMonster()
{
}

void BossMonster::BeginPlay()
{
	Super::BeginPlay();
}

void BossMonster::Tick()
{
	if (_currentPattern)
	{
		if (_currentPattern->IsFinished())
		{
			_currentPattern->End();

			SetCoolDown(_currentPattern->GetCoolTime());
			SetState(ObjectState::Idle);
			_currentPattern = nullptr;
			return;
		}

		_currentPattern->Tick(TimeManager::GET_SINGLE()->GetDeltaTime());
	}

	Super::Tick(); 
}


void BossMonster::Render(HDC hdc)
{
	Super::Render(hdc);

}

void BossMonster::AddPattern(const wstring& name, shared_ptr<BossPattern> pattern)
{
	if (_patterns.find(name) == _patterns.end())
		_patterns[name] = pattern;
}

void BossMonster::ChangePattern(shared_ptr<BossPattern> pattern)
{
	_currentPattern = pattern;
}

void BossMonster::ClearPatterns()
{
	_patterns.clear();
	_currentPattern = nullptr;
}

void BossMonster::OnDamaged(shared_ptr<Creature> attacker)
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
}

void BossMonster::OnDamaged(shared_ptr<Projectile> projectile)
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

	// 피격 데미지 이펙트 추가
	shared_ptr<DamageSkin> dmg = make_shared<DamageSkin>();
	dmg->SetDamage(damage);
	dmg->SetPos(GetPos() + Vec2(0, -60));
	dmg->SetFont(ResourceManager::GET_SINGLE()->GetFont(L"DungeonFont"));
	dmg->SetColor(RGB(255, 80, 80));
	SceneManager::GET_SINGLE()->GetCurrentScene()->AddActor(dmg);
}

void BossMonster::TickIdle()
{
	_coolDown -= TimeManager::GET_SINGLE()->GetDeltaTime();
	if (_coolDown > 0.f)
		return;

	// 보스 패턴이 정해지지 않았다면 대기 상태
	if (_sequence.empty())
		return;

	// 패턴 반복
	const ObjectState nextState = _sequence.front();
	_sequence.pop();
	_sequence.push(nextState);
	SetState(nextState);
}

void BossMonster::TickDeath()
{
	Super::TickDeath();

	ClearSequence();

	if (IsAnimationEnded())
		GameManager::GET_SINGLE()->GetQuestSystem()->Notify(EventType::MonsterKilled, L"Minotaur");
}

