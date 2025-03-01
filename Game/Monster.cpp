#include "pch.h"
#include "Monster.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "CameraComponent.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "Player.h"

Monster::Monster()
{
	_idle[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");
	_idle[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");

	_move[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");
	_move[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");

	_attack[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");
	_attack[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");

	_dead[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");
	_dead[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");

	_birth[DIR_RIGHT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");
	_birth[DIR_LEFT] = ResourceManager::GET_SINGLE()->GetFlipbook(L"");
}

Monster::~Monster()
{

}

void Monster::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Move);
	SetState(ObjectState::Idle);
}

void Monster::Tick()
{
	Super::Tick();
}

void Monster::Render(HDC hdc)
{
	Super::Render(hdc);

}