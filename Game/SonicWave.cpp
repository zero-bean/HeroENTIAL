#include "pch.h"
#include "SonicWave.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Scene.h"
#include "DevScene.h"
#include "Texture.h"
#include "Flipbook.h"

SonicWave::SonicWave()
{
	_flipbookIdle = ResourceManager::GET_SINGLE()->GetFlipbook(L"SonicWave_Red");
}

SonicWave::~SonicWave()
{
}

void SonicWave::BeginPlay()
{
	Super::BeginPlay();

	UpdateAnimation();
}

void SonicWave::Tick()
{
	Super::Tick();

	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
	_pos.y += 250 * directionVector.y * deltaTime;
	_pos.x += 250 * directionVector.x * deltaTime;
	_sumTime += deltaTime;

	if (_sumTime <= 5.f)
		return;

	shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

	scene->RemoveActor(shared_from_this());
}

void SonicWave::Render(HDC hdc)
{
	Super::Render(hdc);
}

void SonicWave::UpdateAnimation()
{
	SetFlipbook(_flipbookIdle);
}
