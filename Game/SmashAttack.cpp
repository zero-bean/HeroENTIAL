#include "pch.h"
#include "SmashAttack.h"
#include "BossMonster.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "Player.h"

SmashAttack::SmashAttack(shared_ptr<BossMonster> owner) : Super(owner)
{
}

SmashAttack::~SmashAttack()
{
}

void SmashAttack::Begin()
{
    shared_ptr<BossMonster> owner = GetOwner();
    if (owner == nullptr)
        return;

    if (shared_ptr<Player> target = owner->GetTarget())
    {
        _targetPos = target->GetCellPos();
        _phase = SmashPhase::Move;
        _elapsed = 0.f;
        _prepareTime = 1.f;
        _isFinished = false;
    }
}

void SmashAttack::Tick(float deltaTime)
{
    shared_ptr<BossMonster> owner = GetOwner();
    if (owner == nullptr)
        return;

    _elapsed += deltaTime;

    switch (_phase)
    {
    case SmashPhase::Move:
        if (owner->MoveToTarget(_targetPos))
        {
            _phase = SmashPhase::Prepare;
            _elapsed = 0.f;
        }
        break;
    case SmashPhase::Prepare:
        if (_elapsed >= _prepareTime)
        {
            // 여기서 실제 내려찍기 연출 가능
            _phase = SmashPhase::Attack;
            _elapsed = 0.f;
        }
        break;
    case SmashPhase::Attack:
        if (_elapsed >= _smashDuration)
        {
            // 공격 판정 처리: _targetPos에 플레이어 있으면 데미지
            shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
            if (scene)
            {
                shared_ptr<Player> player = scene->GetPlayer();
                if (player && player->GetCellPos() == _targetPos)
                {
                    player->OnDamaged(owner->GetStat().attack);
                }
            }

            _phase = SmashPhase::Done;
            _elapsed = 0.f;
        }
        break;
    case SmashPhase::Done:
        _isFinished = true;
        break;
    }
}
