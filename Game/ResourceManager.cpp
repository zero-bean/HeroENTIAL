#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"

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
