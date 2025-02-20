#pragma once

#include "ResourceBase.h"

struct Tile
{
	__int32 value = 0;
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

public:
	virtual void LoadFile(const wstring& path) override;
	virtual void SaveFile(const wstring& path) override;

public:
	Vec2Int GetMapSize() const { return _mapSize; }
	void SetMapSize(Vec2Int size);

	__int32 GetTileSize() const { return _tileSize; }
	void SetTileSize(__int32 size) { _tileSize = size; };

	shared_ptr<Tile> GetTileAt(Vec2Int pos);
	
	vector<vector<Tile>>& GetTiles() { return _tiles; };

private:
	Vec2Int _mapSize = {};
	__int32 _tileSize = {};
	vector<vector<Tile>> _tiles = {};
};

