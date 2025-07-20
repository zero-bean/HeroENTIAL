#pragma once
#include "Scene.h"

class LobbyScene : public Scene
{
	using Super = Scene;
public:
	LobbyScene();
	virtual ~LobbyScene() override;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	void LoadResources();
	void LoadMap();
	void LoadTileMap();
	shared_ptr<Player> LoadPlayer();
	void LoadUI(shared_ptr<Player> player);
	void LoadNPC();
	void LoadSound();
	void LoadCamera();
};

