#include "pch.h"
#include "Scene.h"
#include "Effect.h"
#include "TimeManager.h"
#include "SceneManager.h"

Effect::Effect()
{
    _layer = LAYER_EFFECT;
}

Effect::~Effect()
{
}

void Effect::BeginPlay()
{
    Super::BeginPlay();

}

void Effect::Tick()
{
    Super::Tick();

    _elapsed += TimeManager::GET_SINGLE()->GetDeltaTime();

    if (_autoDestroy && _elapsed >= _duration)
    {
        if (shared_ptr<Scene> scene = SceneManager::GET_SINGLE()->GetCurrentScene())
            scene->RemoveActor(shared_from_this());
    }
}

void Effect::Render(HDC hdc)
{
    Super::Render(hdc);
}
