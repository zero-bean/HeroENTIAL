#pragma once
#include "BattleScene.h"

class Stage1 : public BattleScene
{
	using Super = BattleScene;
public:
	Stage1();
	virtual ~Stage1() override;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void LoadResources() override;
	virtual void LoadMap() override;
	virtual void LoadTileMap() override;
	virtual shared_ptr<Player> LoadPlayer() override;
	virtual void LoadUI(shared_ptr<Player> player) override;
	virtual void LoadSound() override;
	virtual void LoadCamera() override;
};

