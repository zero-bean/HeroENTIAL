#include "pch.h"
#include "SmashAttack.h"
#include "BossMonster.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "Player.h"

SmashAttack::SmashAttack(shared_ptr<BossMonster> owner) : Super(owner)
{
    _reach = 3;
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
        _phase = SmashPhase::Prepare;
        _isFinished = false;
    }
}

void SmashAttack::Tick(float deltaTime)
{
    shared_ptr<BossMonster> owner = GetOwner();
    if (owner == nullptr) return;

    shared_ptr<Player> player = owner->GetTarget();
    if (player == nullptr) return;

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

            bool horizontal = abs(dir.x) > abs(dir.y);
            if (horizontal)
                owner->SetDir(dir.x < 0 ? DIR_LEFT : DIR_RIGHT);
            else
                owner->SetDir(dir.y < 0 ? DIR_UP : DIR_DOWN);

            const float speed = owner->GetStat().speed;
            switch (owner->GetDir())
            {
            case DIR_UP:    
                owner->SetPos(owner->GetPos() + Vec2(0, -speed * deltaTime)); 
                break;
            case DIR_DOWN:  
                owner->SetPos(owner->GetPos() + Vec2(0, +speed * deltaTime)); 
                break;
            case DIR_LEFT:  
                owner->SetPos(owner->GetPos() + Vec2(-speed * deltaTime, 0));
                break;
            case DIR_RIGHT:
                owner->SetPos(owner->GetPos() + Vec2(+speed * deltaTime, 0)); 
                break;
            }
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
                const vector<Vec2Int> area = {
                    center + Vec2Int(0, 0),
                    center + Vec2Int(1, 0),
                    center + Vec2Int(-1, 0),
                    center + Vec2Int(0, 1),
                    center + Vec2Int(0, -1),
                };

                for (const Vec2Int& cellPos : area)
                {
                    shared_ptr<Bullet> aoe = scene->SpawnObject<Bullet>(cellPos);
                    aoe->SetBulletType(BulletType::AOE);
                    aoe->SetAttack(30);
                    aoe->SetLifeTime(0.2f);
                    aoe->SetOwner(owner);
                }
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
