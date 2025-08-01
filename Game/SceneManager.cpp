#include "pch.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "Scene.h"
#include "LobbyScene.h"
#include "BattleScene.h"
#include "Stage1.h"
#include "Stage2.h"

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	if (_sceneChangeRequested)
	{
		_sceneChangeRequested = false;
		ChangeScene(_nextSceneType);
	}

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
	ResourceManager::GET_SINGLE()->Clear();
	UIManager::GET_SINGLE()->Clear();
	CollisionManager::GET_SINGLE()->Clear();
	SoundManager::GET_SINGLE()->Clear();
	_scene.reset();
}

void SceneManager::RequestToChangeScene(SceneType newSceneType)
{
	_sceneChangeRequested = true;
	_nextSceneType = newSceneType;
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
	case SceneType::Stage2:
		newScene = make_shared<Stage2>();
		break;
	default:
		assert(false && "Invalid SceneType");
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