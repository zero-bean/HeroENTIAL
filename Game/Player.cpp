#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "Flipbook.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "BattleScene.h"
#include "Bullet.h"
#include "Item.h"
#include "Inventory.h"

Player::Player()
{
	_flipbookIdle[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_IdleLeft");
	_flipbookIdle[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_IdleRight");

	_flipbookMove[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_MoveLeft");
	_flipbookMove[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_MoveRight");

	_flipbookAttack[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackRight1");
	_flipbookAttack[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackLeft1");

	_flipbookAttacked[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackedRight");
	_flipbookAttacked[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackedLeft");

	_stat.attack = 100;
	_stat.maxHp = 500;
	_stat.hp = 500;
	_stat.speed = 200;
}

Player::~Player()
{

}

void Player::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Move);
	SetState(ObjectState::Idle);

}

void Player::Tick()
{
	Super::Tick();

}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Player::OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
}

void Player::OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
}

void Player::TickIdle()
{
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	_keyPressed = true;
	Vec2Int deltaXY[4] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };

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

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::LEFT_MOUSE))
	{
		SetState(ObjectState::Attack);
	}

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::Z))
	{
		SceneManager::GET_SINGLE()->GetCurrentScene()->TryPickUpItem(GetCellPos());
	}
}

void Player::TickMove()
{
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

	Vec2 dir = _destPos - _pos;
	float distance = dir.Length();

	if (distance < 5.f)
	{
		_pos = _destPos;
		SetState(ObjectState::Idle);
		return;
	}

	// 이동 처리
	dir.Normalize();

	// 1프레임 최대 이동 거리
	const float MAX_MOVE_PER_TICK = 50.f;
	Vec2 move = dir * _stat.speed * deltaTime;
	if (move.Length() > MAX_MOVE_PER_TICK)
	{
		move.Normalize();
		move *= MAX_MOVE_PER_TICK;
	}

	// 남은 거리보다 이동량이 많으면 도착 처리
	if (move.Length() >= distance)
	{
		_pos = _destPos;
		SetState(ObjectState::Idle);
	}
	else
	{
		_pos += move;
	}
}

void Player::TickAttack()
{
	if (_flipbook == nullptr)
		return;

	shared_ptr<BattleScene> scene = dynamic_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
	{
		SetState(ObjectState::Idle);
		return;
	}

	if (UIManager::GET_SINGLE()->IsMouseInUIs())
	{
		SetState(ObjectState::Idle);
		return;
	}

	// TODO : Damage?
	if (IsAnimationEnded())
	{
		if (_weaponType == WeaponType::Sword)
		{
			shared_ptr<Bullet> bullet = scene->SpawnObject<Bullet>(_cellPos);
			Vec2 mousePos = InputManager::GET_SINGLE()->GetMousePos();
			Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
			Vec2 coordiPos = {
				mousePos.x + (cameraPos.x - static_cast<float>(GWinSizeX) / 2),
				mousePos.y + (cameraPos.y - static_cast<float>(GWinSizeY) / 2)
			};
			bullet->SetBulletType(BulletType::BladeStorm);
			bullet->SetDestPos(coordiPos);
			bullet->SetAttack(35);
			bullet->SetDirVec(GetPos(), coordiPos);
		}

		SetState(ObjectState::Idle);
	}
}

void Player::TickDeath()
{
	if (shared_ptr<BattleScene> scene = dynamic_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene()))
	{
		scene->MarkTileType(GetCellPos(), TILE_TYPE::EMPTY);
		scene->NotifyPlayerOnDied();
		scene->RemoveActor(shared_from_this());
	}
}

void Player::TickAttacked()
{
	if (IsAnimationEnded())
	{
		SetState(ObjectState::Idle);
	}
}

void Player::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		if (_keyPressed)
			SetFlipbook(_flipbookMove[_animDir]);
		else
			SetFlipbook(_flipbookIdle[_animDir]);
		break;
	case ObjectState::Move:
		SetFlipbook(_flipbookMove[_animDir]);
		break;
	case ObjectState::Attack:
		if (_weaponType == WeaponType::Sword)
			SetFlipbook(_flipbookAttack[_animDir]);
		break;
	case ObjectState::Attacked:
		SetFlipbook(_flipbookAttacked[_animDir]);
		break;
	}
}
