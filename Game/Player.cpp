#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Flipbook.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "DevScene.h"
#include "Bullet.h"

Player::Player()
{
	_flipbookIdle[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_IdleLeft");
	_flipbookIdle[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_IdleRight");

	_flipbookMove[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_MoveLeft");
	_flipbookMove[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_MoveRight");

	_flipbookAttack[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackRight1");
	_flipbookAttack[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Player_AttackLeft1");

	_stat.attack = 100;
	_stat.hp = 500;
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
		case DIR_RIGHT:
			_pos.x += 200 * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= 200 * deltaTime;
			break;
		case DIR_UP:
			_pos.y -= 200 * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += 200 * deltaTime;
			break;
		}
	}
}

void Player::TickAttack()
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
			shared_ptr<Bullet> bullet = scene->SpawnObject<Bullet>(_cellPos);
			Vec2 mousePos = InputManager::GET_SINGLE()->GetMousePos();
			Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
			Vec2 coordiPos = {
				mousePos.x + (cameraPos.x - static_cast<float>(GWinSizeX) / 2),
				mousePos.y + (cameraPos.y - static_cast<float>(GWinSizeY) / 2)
			};
			bullet->SetBulletType(BulletType::BladeStorm);
			bullet->SetPos(GetPos());
			bullet->SetDestPos(coordiPos);
			bullet->SetScale(3.f);
			bullet->SetAttack(35);
			bullet->SetDirVec(GetPos(), coordiPos);

			shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
			collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_BULLET);
			collider->ResetCollisionFlag();
			collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
			collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
			collider->SetSize({ 80, 80 });

			bullet->AddComponent(collider);
			CollisionManager::GET_SINGLE()->AddCollider(collider);
		}

		SetState(ObjectState::Idle);
	}
}

void Player::TickDeath()
{
	shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	
	if (scene)
		scene->RemoveActor(shared_from_this());
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
	}
}
