#include "pch.h"
#include "NPC.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Flipbook.h"
#include "Player.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

NPC::NPC()
{
	_idle[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_IdleLeft");
	_idle[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_IdleRight");

	_move[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_MoveLeft");
	_move[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_MoveRight");

	_axing[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_AxeLeft");
	_axing[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_AxeRight");

	_hammering[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_HammerLeft");
	_hammering[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_HammerRight");

	_idle_Holding[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_HoldIdleLeft");
	_idle_Holding[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_HoldIdleRight");

	_move_Holding[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_HoldMoveLeft");
	_move_Holding[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"Pawn_HoldMoveRight");
}

NPC::~NPC()
{
}

void NPC::BeginPlay()
{
	Super::BeginPlay();


}

void NPC::Tick()
{
	Super::Tick();

	if (isPlayerOverlapped && InputManager::GET_SINGLE()->GetButtonDown(KeyType::Z))
	{
		if (_onActivate)
			_onActivate();
	}
	else if (!isPlayerOverlapped)
	{
		if (_onDeactivate)
			_onDeactivate();
	}
}

void NPC::Render(HDC hdc)
{
	Super::Render(hdc);
}

void NPC::OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
	shared_ptr<Player> player = dynamic_pointer_cast<Player>(other->GetOwner());

	if (player && !isPlayerOverlapped)
		isPlayerOverlapped = true;
}

void NPC::OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
	shared_ptr<Player> player = dynamic_pointer_cast<Player>(other->GetOwner());

	if (player && isPlayerOverlapped)
		isPlayerOverlapped = false;
}

void NPC::AddCollider(const Vec2 size)
{
	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_NPC);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->SetSize(size);
	AddComponent(collider);
	CollisionManager::GET_SINGLE()->AddCollider(collider);
}

void NPC::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_idle[_animDir]);
		break;
	case ObjectState::Move:
		SetFlipbook(_move[_animDir]);
		break;
	}
}
