#pragma once

#include "Scene.h";

class SceneManager
{
public:
	static SceneManager* GET_SINGLE()
	{
		static SceneManager instance;
		return &instance;
	}

private:
	SceneManager() {}
	~SceneManager() {}

	SceneManager(const SceneManager&) = delete;
	SceneManager operator=(const SceneManager&) = delete;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Clear();

public:
	void ChangeScene(SceneType sceneType);
	Scene* GetCurrentScene() const; 

public:
	Vec2 GetCameraPos() const { return _cameraPos; }
	void SetCameraPos(const Vec2& pos) { _cameraPos = pos; }

private:
	unique_ptr<Scene> _scene;
	SceneType _sceneType = SceneType::None;
	
private:
	Vec2 _cameraPos = { 400, 300 };
};

