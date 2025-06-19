#include "pch.h"
#include "SmashAttack.h"
#include "BossMonster.h"
#include "Scene.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "Player.h"

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
    _targetPos = target->GetCellPos();
    _phase = SmashPhase::Prepare;
    _isFinished = false;
}

void SmashAttack::Tick(float deltaTime)
{
    shared_ptr<BossMonster> owner = GetOwner();
    if (owner == nullptr) 
        return;

    shared_ptr<Player> player = owner->GetTarget();
    if (player == nullptr) 
        return;

    switch (_phase)
    {
    case SmashPhase::Prepare:
    {
        Vec2 dir = player->GetPos() - owner->GetPos();
        float dist = dir.Length();
        float reach = static_cast<float>(GetReach()) * 32.f;

        if (dist < reach)
        {
            owner->SetPatternAnimation(L"Smash");
            _phase = SmashPhase::Attack;
        }
        else
        {
            owner->SetState(ObjectState::Move); 
            owner->SetDestPos(player->GetPos());
        }

        break;
    }
    case SmashPhase::Attack:
    {
        if (owner->IsAnimationEnded())
        {
            
            if (shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene()))
            {
                const Vec2Int center = _targetPos;
                // TODO
            }

            _phase = SmashPhase::Done;
        }

        break;
    }
    case SmashPhase::Done:
        _isFinished = true;
        break;
    }
}


void SmashAttack::OnRangeReached()
{
    if (_phase == SmashPhase::Prepare)
        _phase = SmashPhase::Attack;
}
