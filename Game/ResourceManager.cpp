#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Tilemap.h"

shared_ptr<Texture> ResourceManager::LoadTexture(const wstring& key, const wstring& path, unsigned __int32 transparent)
{
	if (_textures.find(key) != _textures.end())
		return _textures[key];

	fs::path fullPath = _resourcePath / path;

	shared_ptr<Texture> texture = make_shared<Texture>();
	texture->LoadBMP(_hwnd, fullPath.c_str());
	texture->SetTransparent(transparent);
	_textures.emplace(key, texture);

	return texture;
}

shared_ptr<Sprite> ResourceManager::CreateSprite(const wstring& key, shared_ptr<Texture> texture, __int32 x, __int32 y, __int32 cx, __int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	shared_ptr<Sprite> sprite = make_shared<Sprite>(texture, x, y, cx, cy);
	_sprites.emplace(key, sprite);

	return sprite;
}

shared_ptr<Flipbook> ResourceManager::CreateFlipbook(const wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())
		return _flipbooks[key];

	shared_ptr<Flipbook> flipbook = make_shared<Flipbook>();
	_flipbooks.emplace(key, flipbook);

	return flipbook;
}

shared_ptr<Tilemap> ResourceManager::CreateTilemap(const wstring& key)
{
	if (_tilemaps.find(key) != _tilemaps.end())
		return _tilemaps[key];

	shared_ptr<Tilemap> tilemap = make_shared<Tilemap>();
	_tilemaps.emplace(key, tilemap);

	return tilemap;
}

void ResourceManager::SaveTilemap(const wstring& key, const wstring& path)
{
	shared_ptr<Tilemap> tilemap = GetTilemap(key);

	fs::path fullPath = _resourcePath / path;
	tilemap->SaveFile(fullPath);
}

shared_ptr<Tilemap> ResourceManager::LoadTilemap(const wstring& key, const wstring& path)
{
	shared_ptr<Tilemap> tilemap = nullptr;

	if (_tilemaps.find(key) == _tilemaps.end())
		_tilemaps[key] = make_shared<Tilemap>();

	tilemap = _tilemaps[key];

	fs::path fullPath = _resourcePath / path;
	tilemap->LoadFile(fullPath);

	return tilemap;
}