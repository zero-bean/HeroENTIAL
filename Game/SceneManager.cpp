#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DevScene.h"
#include "LobbyScene.h"

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

	shared_ptr<Scene> newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::DevScene:
		newScene = make_shared<DevScene>();
		break;
	case SceneType::LobbyScene:
		newScene = make_shared<LobbyScene>();
		break;
	}

	_scene.reset();

	_scene = newScene;
	_sceneType = sceneType;

	_scene->Init();
}

shared_ptr<Scene> SceneManager::GetCurrentScene()
{
	return _scene;
}
