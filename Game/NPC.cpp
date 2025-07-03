#include "pch.h"
#include "NPC.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Flipbook.h"
#include "Player.h"
#include "Font.h"

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
	_font = ResourceManager::GET_SINGLE()->GetFont(L"DungeonFont32");

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

	if (_font)
	{
		Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
		float cameraZoom = SceneManager::GET_SINGLE()->GetCameraZoom();
		Vec2 screenCenter = Vec2(GWinSizeX / 2.0f, GWinSizeY / 2.0f);
		Vec2 renderPos = (_pos - cameraPos) * cameraZoom + screenCenter;

		SIZE roleSize;
		GetTextExtentPoint32(hdc, _roleText.c_str(), static_cast<int>(_roleText.length()), &roleSize);
		Vec2 rolePos = { renderPos.x - roleSize.cx / 2.0f, renderPos.y - 70.0f };
		Utils::DrawTextColored(hdc, rolePos, _roleText, _font->GetHandle(), RGB(155, 255, 155));

		SIZE interSize;
		GetTextExtentPoint32(hdc, _interactText.c_str(), static_cast<int>(_interactText.length()), &interSize);
		Vec2 interactPos = { renderPos.x - interSize.cx / 2.0f, renderPos.y - 100.0f };
		Utils::DrawTextColored(hdc, interactPos, _interactText, _font->GetHandle(), RGB(255, 255, 255));
	}
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
