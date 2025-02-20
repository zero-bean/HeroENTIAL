#pragma once

#include "Actor.h"

class Tilemap;

enum TILE_SIZE
{
	TILE_WIDTH = 63,
	TILE_HEIGHT = 63,
	TILE_SIZEX = 63,
	TILE_SIZEY = 63,
};

class TilemapActor : public Actor
{
	using Super = Actor;
public:
	TilemapActor();
	virtual ~TilemapActor();

public:
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

public:
	void TickPicking();

	void SetTilemap(shared_ptr<Tilemap> tilemap) { _tilemap = tilemap; }
	shared_ptr<Tilemap> GetTilemap() { return _tilemap; }

	void SetShowDebug(bool showDebug) { _showDebug = showDebug; }

protected:
	shared_ptr<Tilemap> _tilemap = nullptr;
	bool _showDebug = false;
};

