#include "pch.h"
#include "Monster.h"
#include "DevScene.h"
#include "SceneManager.h"

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
}

void Monster::Tick()
{
	Super::Tick();
}

void Monster::Render(HDC hdc)
{
	Super::Render(hdc);

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
