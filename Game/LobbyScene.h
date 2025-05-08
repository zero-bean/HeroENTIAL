#pragma once
#include "Scene.h"

class Actor;
class TilemapActor;
class Creature;
class Player;
class GameObject;
class Item;
class Potion;
class UI;

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
	void LoadMap();
	void LoadTileMap();
	shared_ptr<Player> LoadPlayer();
	void LoadNPC();
	void LoadUI();

};

