#include "pch.h"
#include "SmashAttack.h"
#include "BossMonster.h"
#include "Player.h"
#include "Bullet.h"
#include "RedRectWarningEffect.h"
#include "Scene.h"
#include "BattleScene.h"

SmashAttack::SmashAttack(shared_ptr<BossMonster> owner) : Super(owner)
{
    _reach = 7;
    _coolTime = 1.f;
}

SmashAttack::~SmashAttack()
{
}

void SmashAttack::Begin()
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

    shared_ptr<Player> target = owner->GetTarget();
    // 적합한 대상을 찾지 못하면 대상을 지정 후, 패턴을 실행하지 않고 종료
    if (target == nullptr) {
        owner->SetTarget(scene->FindClosestPlayer(owner->GetCellPos()));
        _isFinished = true;
        return;
    }

    // 대상을 찾았으면 패턴 실행
    _phase = Phase::MoveToTarget;
    _isFinished = false;
}

void SmashAttack::Tick(float deltaTime)
{
    shared_ptr<BossMonster> owner = GetOwner();
    if (!owner) 
        return;

    shared_ptr<Player> player = owner->GetTarget();
    if (!player) 
        return;

    const Vec2 dir = player->GetPos() - owner->GetPos();
    const float dist = dir.Length();
    const float reach = static_cast<float>(GetReach()) * 32.f;

    switch (_phase)
    {
    case Phase::MoveToTarget:
    {
        if (dist <= reach)
        {
            // 다음 단계로 전환
            owner->SetState(ObjectState::Attack);
            _targetPos = owner->GetTarget()->GetCellPos();
            owner->SetPatternAnimation(L"Smash");
            _phase = Phase::Attack;

            // 경고 이펙트
            if (shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene()))
            {
                shared_ptr<RedRectWarningEffect> warning = make_shared<RedRectWarningEffect>();
                warning->SetCellPos(_targetPos, true);
                warning->SetSize({ 160.f, 160.f });
                warning->SetDuration(0.5f);
                scene->AddActor(warning);
            }
        }
        else
        {
            owner->SetDestPos(player->GetPos());
            owner->SetState(ObjectState::Move);
        }

        break;
    }
    case Phase::Attack:
    {
        if (owner->IsAnimationEnded())
        {
            // 사운드 출력
            SoundManager::GET_SINGLE()->Play(L"SFX_SMASH");

            // 공격 이펙트 생성 등 처리
            if (auto scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene()))
            {
                shared_ptr<Bullet> bullet = make_shared<Bullet>();
                bullet->SetCellPos(_targetPos, true);
                bullet->SetBulletType(BulletType::Transparent);
                bullet->SetTimer(0.1f);
                bullet->SetAttack(5);
                scene->AddActor(bullet);
            }
            _phase = Phase::Done;
        }
        break;
    }
    case Phase::Done:
    {
        _isFinished = true;
        break;
    }
    }
}
