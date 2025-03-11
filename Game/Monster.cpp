#include "pch.h"
#include "Monster.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "DevScene.h"
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

	shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_MONSTER);
	collider->ResetCollisionFlag();
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_BULLET);
	collider->SetSize(Vec2(16, 16) * GetScale());
	collider->SetCoorPos({ 0, -16 });
	AddComponent(collider);
	CollisionManager::GET_SINGLE()->AddCollider(collider);
}

void Monster::Tick()
{
	Super::Tick();
}

void Monster::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Monster::OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{
	shared_ptr<BoxCollider> b1 = dynamic_pointer_cast<BoxCollider>(collider);
	shared_ptr<BoxCollider> b2 = dynamic_pointer_cast<BoxCollider>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;
}

void Monster::OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other)
{

}

void Monster::TickDeath()
{
	if (_flipbook == nullptr)
		return;

	if (IsAnimationEnded()) {
		shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());

		if (scene == nullptr)
			return;

		/* 죽을 때, 이벤트 함수 추가할 것 */
		DropItems();
		/* */

		scene->RemoveActor(shared_from_this());
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
	case ObjectState::Death:
		SetFlipbook(_dead[_animDir]);
		break;
	case ObjectState::Birth:
		SetFlipbook(_birth[_animDir]);
		break;
	}

}
