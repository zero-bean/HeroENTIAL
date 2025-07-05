#include "pch.h"
#include "Tilemap.h"
#include <iostream>
#include <fstream>

Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{
	
}

void Tilemap::LoadFile(const wstring& path)
{
	// C++ 스타일
	wifstream ifs;

	ifs.open(path);

	ifs >> _mapSize.x >> _mapSize.y;

	SetMapSize(_mapSize);

	for (__int32 y = 0; y < _mapSize.y; y++)
	{
		wstring line;
		ifs >> line;

		for (__int32 x = 0; x < _mapSize.x; x++)
		{
			int typeInt = line[x] - L'0';
			_tiles[y][x].type = static_cast<TILE_TYPE>(typeInt);
		}
	}

	ifs.close();
}

void Tilemap::SaveFile(const wstring& path)
{
	// C++ 스타일
	wofstream ofs;

	ofs.open(path);

	ofs << _mapSize.x << endl;
	ofs << _mapSize.y << endl;

	for (__int32 y = 0; y < _mapSize.y; y++)
	{
		for (__int32 x = 0; x < _mapSize.x; x++)
		{
			ofs << static_cast<int>(_tiles[y][x].type);
		}

		ofs << endl;
	}

	ofs.close();
}

void Tilemap::LoadMetadata(const wstring& metaPath)
{
	wifstream ifs;
	int x, y;
	wstring typeStr, meta;

	ifs.open(metaPath);

	while (ifs >> x >> y >> typeStr >> meta)
	{
		_tiles[y][x].type = ParseTileType(typeStr);
		_tiles[y][x].metadata = meta;
	}

	ifs.close();
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = vector<vector<Tile>>(size.y, vector<Tile>(size.x));

	for (__int32 y = 0; y < size.y; y++)
	{
		for (__int32 x = 0; x < size.x; x++)
		{
			_tiles[y][x] = Tile{};
		}
	}
}

Tile& Tilemap::GetTileAt(Vec2Int pos)
{
	return _tiles[pos.y][pos.x];
}

void Tilemap::UpdateTileType(const Vec2Int oldPos, const Vec2Int newPos, TILE_TYPE type)
{
	if (oldPos != newPos && IsPosInRange(oldPos)) {
		_tiles[oldPos.y][oldPos.x].type = TILE_TYPE::EMPTY;
	}

	if (IsPosInRange(newPos)) {
		_tiles[newPos.y][newPos.x].type = type;
	}
}

void Tilemap::RemoveTileType(Vec2Int pos)
{
	if (IsPosInRange(pos)) {
		_tiles[pos.y][pos.x].type = TILE_TYPE::EMPTY;
	}
}

bool Tilemap::IsPosInRange(const Vec2Int pos) const
{
	return pos.x >= 0 && pos.y >= 0 && pos.y < _mapSize.y && pos.x < _mapSize.x;
}

TILE_TYPE Tilemap::ParseTileType(const wstring& str)
{

	if (str == L"MONSTER")
		return TILE_TYPE::MONSTER;
	else if (str == L"NPC")
		return TILE_TYPE::NPC;
	else if (str == L"WALL")
		return TILE_TYPE::WALL;
	else if (str == L"PLAYER")
		return TILE_TYPE::PLAYER;
	else if (str == L"ITEM")
		return TILE_TYPE::ITEM;
	else if (str == L"OBJECT")
		return TILE_TYPE::OBJECT;

	return TILE_TYPE::EMPTY;
}
