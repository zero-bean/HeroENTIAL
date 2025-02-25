#include "pch.h"
#include "SonicWave.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "DevScene.h"

SonicWave::SonicWave()
{
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

}

void SonicWave::Render(HDC hdc)
{
	Super::Render(hdc);


}

void SonicWave::TickIdle()
{
	shared_ptr<DevScene> scene = dynamic_pointer_cast<DevScene>(SceneManager::GET_SINGLE()->GetCurrentScene());
	if (scene == nullptr)
		return;

}

void SonicWave::TickMove()
{

}

void SonicWave::UpdateAnimation()
{

}
