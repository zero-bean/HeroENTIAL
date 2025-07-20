#pragma once
#include "UI.h"

class Tilemap;
class Sprite;
class Player;

class Minimap : public UI
{
	using Super = UI;
public:
	Minimap();
	virtual ~Minimap();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetTilemap(shared_ptr<Tilemap> tilemap) { _tilemap = tilemap; }
	void SetTarget(shared_ptr<Player> player) { _player = player; }

private:
	bool GetColorByTileType(TILE_TYPE type, COLORREF& outColor);

private:
	shared_ptr<Tilemap> _tilemap = nullptr;
	shared_ptr<Sprite> _cover = nullptr;
	shared_ptr<Player> _player = nullptr;
	const __int32 _visibleRange = 8;
	const __int32 _tileSize = 8;
};

