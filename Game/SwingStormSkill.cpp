#include "pch.h"
#include "SwingStormSkill.h"
#include "SmashAttack.h"
#include "BossMonster.h"
#include "Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "BattleScene.h"
#include "SceneManager.h"

SwingStormSkill::SwingStormSkill(shared_ptr<BossMonster> owner) : Super(owner)
{
	_reach = 1000;
	_coolTime = 1.f;
}

SwingStormSkill::~SwingStormSkill()
{
}

void SwingStormSkill::Begin()
{
	shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

	shared_ptr<BossMonster> owner = GetOwner();
	// 실행할 몬스터가 존재하지 않으면 바로 종료
	if (owner == nullptr) {
		_isFinished = true;
		return;
	}

	// 패턴 시작
    owner->SetPatternAnimation(L"Prepare");
	_phase = Phase::Prepare;
	_isFinished = false;
}

void SwingStormSkill::Tick(float deltaTime)
{
	shared_ptr<BossMonster> owner = GetOwner();
	if (owner == nullptr)
		return;

    switch (_phase)
    {
    case Phase::Prepare:
        if (owner->IsAnimationEnded())
        {
            _phase = Phase::FirstSwing;
            owner->SetPatternAnimation(L"Swing");
        }
        break;
    case Phase::FirstSwing:
        if (owner->IsAnimationEnded())
        {
            FireBulletsPhase1();
            _phase = Phase::SecondSwing;
            owner->SetPatternAnimation(L"Prepare");
            owner->SetPatternAnimation(L"Swing");
        }
        break;
    case Phase::SecondSwing:
        if (owner->IsAnimationEnded())
        {
            FireBulletsPhase2();
            _phase = Phase::FinalSwing;
            owner->SetPatternAnimation(L"Prepare");
            owner->SetPatternAnimation(L"Swing");
        }
        break;
    case Phase::FinalSwing:
        if (owner->IsAnimationEnded())
        {
            FireBulletsPhase1();
            FireBulletsPhase2();
            _phase = Phase::Done;
        }
        break;
    case Phase::Done:
        _isFinished = true;
        break;
    }
}

void SwingStormSkill::FireBulletsPhase1()
{
    const Vec2 center = GetOwner()->GetPos();
    vector<float> angles = { 0.f, 45.f, 90.f, 135.f, 180.f, 225.f, 270.f, 315.f };

    for (float angle : angles)
    {
        if (shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene()))
        {
            shared_ptr<Bullet> bullet = make_shared<Bullet>();
            bullet->SetCellPos(GetOwner()->GetCellPos(), true);
            bullet->SetBulletType(BulletType::Cutter);
            bullet->SetTimer(7.f);
            bullet->SetAttack(GetOwner()->GetStat().attack / 5);
            bullet->SetDirVec(Utils::FromAngleDeg(angle));
            scene->AddActor(bullet);
        }
    }
}

void SwingStormSkill::FireBulletsPhase2()
{
    const Vec2 center = GetOwner()->GetPos();
    vector<float> angles = { 0.f, 45.f, 90.f, 135.f, 180.f, 225.f, 270.f, 315.f };

    for (float angle : angles)
    {
        if (shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene()))
        {
            shared_ptr<Bullet> bullet = make_shared<Bullet>();
            bullet->SetCellPos(GetOwner()->GetCellPos(), true);
            bullet->SetBulletType(BulletType::Cutter);
            bullet->SetTimer(7.f);
            bullet->SetAttack(GetOwner()->GetStat().attack / 5);
            bullet->SetDirVec(Utils::FromAngleDeg(angle + 22.5f));
            scene->AddActor(bullet);
        }
    }
}
