#pragma once

#include "Actor.h"

class Tilemap;

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

