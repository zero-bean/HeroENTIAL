#include "pch.h"
#include "Goblin.h"
#include "Flipbook.h"
#include "Player.h"
#include "Bullet.h"
#include "Potion.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "BattleScene.h"

Goblin::Goblin()
{
	SetGoblinType(_type);
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

void Goblin::SetGoblinType(GoblinType type)
{
	_type = type;

	switch (_type)
	{
	case GoblinType::Axe:
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
	case GoblinType::Bow:
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

void Goblin::TickIdle()
{
	shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

	if (_target.expired())
		_target = scene->FindClosestPlayer(GetCellPos());

	shared_ptr<Player> player = _target.lock();
	if (player == nullptr)
		return;

	Vec2Int dir = player->GetCellPos() - GetCellPos();
	__int32 dist = abs(dir.x) + abs(dir.y);


	if (_type == GoblinType::Axe)
	{
		if (dist == 1)
		{
			SetDir(GetLookAtDir(player->GetCellPos()));

			if (_waitAtkSec > 0.5f)
			{
				float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
				_waitAtkSec -= deltaTime;
				return;
			}

			SetState(ObjectState::Attack);
			return;
		}
	}
	else if (_type == GoblinType::Bow)
	{
		if (dist <= 8)
		{
			SetDir(GetLookAtDir(player->GetCellPos()));

			if (_waitAtkSec > 0.5f)
			{
				float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
				_waitAtkSec -= deltaTime;
				return;
			}

			SetState(ObjectState::Attack);
			return;
		}
	}

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

	if (IsAnimationEnded()) {
		shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
		if (scene == nullptr)
			return;

		switch (_type)
		{
		case GoblinType::Axe:
			_waitAtkSec = 1.f; // 공격 종료 시간
			break;
		case GoblinType::Bow:
			shared_ptr<Player> player = _target.lock();
			if (player == nullptr)
				break;

			shared_ptr<Bullet> bullet = scene->SpawnObject<Bullet>(_cellPos);
			bullet->SetBulletType(BulletType::Basic);
			bullet->SetAttack(50);
			bullet->SetDestPos(player->GetPos());
			bullet->SetDirVec(bullet->GetPos(), bullet->GetDestPos());

			_waitAtkSec = 0.7f; // 공격 종료 시간
			break;
		}

		SetState(ObjectState::Idle);
	}
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

void Goblin::DropItems()
{
	shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

	{
		shared_ptr<Potion> potion = scene->SpawnObject<Potion>(_cellPos);
		potion->SetScale(1);
		potion->SetPotionType(PotionType::Steak);
	}

	{
		shared_ptr<Potion> potion2 = scene->SpawnObject<Potion>({ _cellPos.x, _cellPos.y + 1 });
		potion2->SetScale(1);
		potion2->SetPotionType(PotionType::Sandwitch);
	}
}
