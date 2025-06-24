#include "pch.h"
#include "Monster.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "CollisionManager.h"

Monster::Monster()
{

}

Monster::~Monster()
{

}

void Monster::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Birth);

	shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_MYBULLET);
	collider->SetSize(Vec2(16, 16) * GetScale());
	collider->SetCoorPos({ 0, -16 });
	AddComponent(collider);
	CollisionManager::GET_SINGLE()->AddCollider(collider);
}

void Monster::Tick()
{
	Super::Tick();

	switch (_state)
	{
	case ObjectState::Skill:
		TickSkill();
		break;
	case ObjectState::Stunned:
		TickStunned();
		break;
	}
}

void Monster::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Monster::TickDeath()
{
	Super::TickDeath();

	if (_flipbook == nullptr)
		return;

	if (IsAnimationEnded()) {
		shared_ptr<BattleScene> scene = static_pointer_cast<BattleScene>(SceneManager::GET_SINGLE()->GetCurrentScene());

		if (scene == nullptr)
			return;

		scene->RemoveActor(shared_from_this());
		scene->NotifyMonsterOnDied();
		scene->MarkTileType(GetCellPos(), TILE_TYPE::EMPTY);
		DropItems();
	}
}

void Monster::TickBirth()
{
	if (_flipbook == nullptr)
		return;

	if (IsAnimationEnded())
		SetState(ObjectState::Idle);
}

void Monster::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_idle[_animDir]);
		break;
	case ObjectState::Move:
		SetFlipbook(_move[_animDir]);
		break;
	case ObjectState::Attack:
		SetFlipbook(_attack[_animDir]);
		break;
	case ObjectState::Attacked:
		SetFlipbook(_attacked[_animDir]);
		break;
	case ObjectState::Stunned:
		SetFlipbook(_stunned[_animDir]);
		break;
	case ObjectState::Death:
		SetFlipbook(_death[_animDir]);
		break;
	case ObjectState::Birth:
		SetFlipbook(_birth[_animDir]);
		break;
	}
}
