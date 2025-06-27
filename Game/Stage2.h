#pragma once
#include "BattleScene.h"

class Stage2 : public BattleScene
{
	using Super = BattleScene;
public:
	Stage2();
	virtual ~Stage2() override;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void LoadResources() override;
	virtual void LoadMap() override;
	virtual void LoadTileMap() override;
	virtual void LoadPlayer() override;
	virtual void LoadUI() override;
	virtual void LoadCamera() override;
};

