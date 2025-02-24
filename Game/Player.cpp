#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "DevScene.h"

Player::Player()
{
	_flipbookIdle[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_IdleLeft");
	_flipbookIdle[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_IdleRight");
	_flipbookIdle[DIR_UP] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_IdleLeft");
	_flipbookIdle[DIR_DOWN] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_IdleRight");

	_flipbookMove[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_MoveLeft");
	_flipbookMove[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_MoveRight");
	_flipbookMove[DIR_UP] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_MoveLeft");
	_flipbookMove[DIR_DOWN] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_MoveRight");

	_flipbookAttack[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackRight1");
	//_flipbookAttack[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackRight2");
	_flipbookAttack[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackLeft1");
	//_flipbookAttack[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackLeft2");
	_flipbookAttack[DIR_UP] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackUp1");
	//_flipbookAttack[DIR_UP] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackUp");
	_flipbookAttack[DIR_DOWN] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackDown1");
	//_flipbookAttack[DIR_DOWN] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackDown2");


	_stat.attack = 100;
}

Player::~Player()
{

}

void Player::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Move);
	SetState(ObjectState::Idle);

	SetCellPos({ 5, 5 }, true);
}

void Player::Tick()
{
	Super::Tick();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Player::TickIdle()
{
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	_keyPressed = true;
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	if (InputManager::GET_SINGLE()->GetButton(KeyType::W))
	{
		SetDir(DIR_UP);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Move);
		}
	}
	else  if (InputManager::GET_SINGLE()->GetButton(KeyType::S))
	{
		SetDir(DIR_DOWN);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Move);
		}
	}
	else if (InputManager::GET_SINGLE()->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Move);
		}
	}
	else if (InputManager::GET_SINGLE()->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);

		Vec2Int nextPos = _cellPos + deltaXY[_dir];
		if (CanGo(nextPos))
		{
			SetCellPos(nextPos);
			SetState(ObjectState::Move);
		}
	}
	else
	{
		_keyPressed = false;
		if (_state == ObjectState::Idle) {
			UpdateAnimation();
		}
	}

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::KEY_1))
	{
		SetWeaponType(WeaponType::Sword);
	}
}

void Player::TickMove()
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
		switch (_dir)
		{
		case DIR_UP:
			_pos.y -= 200 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 200 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 200 * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += 200 * deltaTime;
			break;
		}
	}
}

void Player::TickSkill()
{
	if (_flipbook == nullptr)
		return;

	// TODO : Damage?
	if (IsAnimationEnded())
	{
		shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
		if (scene == nullptr)
			return;

		if (_weaponType == WeaponType::Sword)
		{
			shared_ptr<Creature> creature = scene->GetCreatureAt(GetFrontCellPos());
			if (creature)
			{
				//scene->SpawnObject<HitEffect>(GetFrontCellPos());
				creature->OnDamaged(dynamic_pointer_cast<Creature>(shared_from_this()));
			}
		}

		SetState(ObjectState::Idle);
	}
}

void Player::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		if (_keyPressed)
			SetFlipbook(_flipbookMove[_dir]);
		else
			SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::Move:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	case ObjectState::Skill:
		if (_weaponType == WeaponType::Sword)
			SetFlipbook(_flipbookAttack[_dir]);
		break;
	}
}