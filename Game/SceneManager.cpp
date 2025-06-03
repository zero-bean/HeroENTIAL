#include "pch.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "Scene.h"
#include "LobbyScene.h"
#include "BattleScene.h"
#include "Stage1.h"

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
	UIManager::GET_SINGLE()->Clear();
	ResourceManager::GET_SINGLE()->Clear();
	_scene.reset();
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	shared_ptr<Scene> newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::LobbyScene:
		newScene = make_shared<LobbyScene>();
		break;
	case SceneType::BattleScene:
		newScene = make_shared<BattleScene>();
		break;
	case SceneType::Stage1:
		newScene = make_shared<Stage1>();
		break;
	}

	Clear();

	_scene = newScene;
	_sceneType = sceneType;
	
	_scene->Init();
}

shared_ptr<Scene> SceneManager::GetCurrentScene()
{
	return _scene;
}
