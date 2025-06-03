#pragma once

#include "ResourceBase.h"

struct Tile
{
	TILE_TYPE type = TILE_TYPE::EMPTY;
	wstring metadata = {};
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

public:
	virtual void LoadFile(const wstring& path) override;
	virtual void SaveFile(const wstring& path) override;
	
	void LoadMetadata(const wstring& path);
	//void SaveMetadata(const wstring& path);

public:
	Vec2Int GetMapSize() const { return _mapSize; }
	void SetMapSize(Vec2Int size);

	__int32 GetTileSize() const { return _tileSize; }
	void SetTileSize(__int32 size) { _tileSize = size; };

	__int32 GetScale() const { return _scale; }
	void SetScale(__int32 scale) { _scale = scale; };

	Tile& GetTileAt(Vec2Int pos);
	
	vector<vector<Tile>>& GetTiles() { return _tiles; };

public:
	void UpdateTileType(const Vec2Int oldPos, const Vec2Int newPos, TILE_TYPE type);
	void RemoveTileType(const Vec2Int pos);
	bool IsPosInRange(const Vec2Int pos) const;

private:
	TILE_TYPE ParseTileType(const wstring& str);

private:
	Vec2Int _mapSize = {};
	__int32 _tileSize = 0;
	__int32 _scale = 1;
	vector<vector<Tile>> _tiles = {};
};

