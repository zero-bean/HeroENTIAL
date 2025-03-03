#include "pch.h"
#include "Goblin.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Flipbook.h"
#include "DevScene.h"

Goblin::Goblin(MonsterType type, Rank rank) : _type(type)
{
	SetRank(rank);

	switch (_type)
	{
	case MonsterType::Axe:
		_idle[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Right_Idle");
		_idle[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Left_Idle");

		_move[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Right_Move");
		_move[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Left_Move");

		_attack[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Right_Attack");
		_attack[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Left_Attack");

		_attacked[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Right_Attacked");
		_attacked[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Left_Attacked");

		_dead[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Right_Death");
		_dead[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Left_Death");

		_birth[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Right_Birth");
		_birth[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Axe_Left_Birth");
		break;
	case MonsterType::Bow:
		_idle[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Right_Idle");
		_idle[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Left_Idle");

		_move[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Right_Move");
		_move[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Left_Move");

		_attack[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Right_Attack");
		_attack[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Left_Attack");

		_attacked[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Right_Attacked");
		_attacked[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Left_Attacked");

		_dead[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Right_Death");
		_dead[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Left_Death");

		_birth[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Right_Birth");
		_birth[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Goblin_Bow_Left_Birth");
		break;
	}
}

Goblin::~Goblin()
{

}

void Goblin::BeginPlay()
{
	Super::BeginPlay();
}

void Goblin::Tick()
{
	Super::Tick();


}

void Goblin::Render(HDC hdc)
{
	Super::Render(hdc);


}

void Goblin::TickIdle()
{
	shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

	if (_target.expired())
		_target = scene->FindClosestPlayer(GetCellPos());

	shared_ptr<Player> player = _target.lock();
	if (player == nullptr)
		return;

	Vec2Int dir = player->GetCellPos() - GetCellPos();
	__int32 dist = abs(dir.x) + abs(dir.y);

	if (dist == 1)
	{
		SetDir(GetLookAtDir(player->GetCellPos()));
		SetState(ObjectState::Skill);
		_waitAtkSec = 0.5f; // 공격 종료 시간
	}
	else
	{
		vector<Vec2Int> path;
		if (scene->FindPath(GetCellPos(), player->GetCellPos(), OUT path))
		{
			if (path.size() > 1)
			{
				Vec2Int nextPos = path[1];
				if (scene->CanGo(nextPos))
				{
					SetCellPos(nextPos);
					SetState(ObjectState::Move);
				}
			}
			else
				SetCellPos(path[0]);
		}
	}
}

void Goblin::TickMove()
{
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	Vec2 dir = (_destPos - _pos);

	if (dir.Length() < 5.f)
	{
		SetState(ObjectState::Idle);
		_pos = _destPos;
	}
	else
	{
		bool horizontal = abs(dir.x) > abs(dir.y);

		if (horizontal)
			SetDir(dir.x < 0 ? DIR_LEFT : DIR_RIGHT);
		else
			SetDir(dir.y < 0 ? DIR_UP : DIR_DOWN);

		switch (_dir)
		{
		case DIR_UP:
			_pos.y -= 100 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 100 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 100 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 100 * deltaTime;
			break;
		}
	}
}

void Goblin::TickAttack()
{
	if (_flipbook == nullptr)
		return;

	if (_waitAtkSec > 0)
	{
		float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
		_waitAtkSec = max(0, _waitAtkSec - deltaTime);
		return;
	}

	shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

	switch (_type)
	{
	case MonsterType::Axe:
		break;
	case MonsterType::Bow:
		break;
	}

	SetState(ObjectState::Idle);
}

void Goblin::TickAttacked()
{
	if (_flipbook == nullptr)
		return;

	if (IsAnimationEnded())
	{
		SetState(ObjectState::Idle);
	}
}
