#include "pch.h"
#include "Scene.h"
#include "TimeManager.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update()
{
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();

}
