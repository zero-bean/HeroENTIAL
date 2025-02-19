#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneManager::Clear()
{
	_scene.reset();
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	std::unique_ptr<Scene> newScene;

	switch (sceneType)
	{
	case SceneType::DevScene:
		newScene = std::make_unique<DevScene>();
		break;
	}

	_scene = std::move(newScene);
	_sceneType = sceneType;

	_scene->Init();
}

Scene* SceneManager::GetCurrentScene() const
{
	return _scene.get();
}
