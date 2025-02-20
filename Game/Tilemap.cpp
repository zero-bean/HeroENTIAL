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
	{
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
				_tiles[y][x].value = line[x] - L'0';
			}
		}

		ifs.close();
	}
}

void Tilemap::SaveFile(const wstring& path)
{
	// C++ 스타일
	{
		wofstream ofs;

		ofs.open(path);

		ofs << _mapSize.x << endl;
		ofs << _mapSize.y << endl;

		for (__int32 y = 0; y < _mapSize.y; y++)
		{
			for (__int32 x = 0; x < _mapSize.x; x++)
			{
				ofs << _tiles[y][x].value;
			}

			ofs << endl;
		}

		ofs.close();
	}
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = vector<vector<Tile>>(size.y, vector<Tile>(size.x));

	for (__int32 y = 0; y < size.y; y++)
	{
		for (__int32 x = 0; x < size.x; x++)
		{
			_tiles[y][x] = Tile{ 0 };
		}
	}
}

Tile& Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y >= _mapSize.y)
		return;

	return _tiles[pos.y][pos.x];
}
