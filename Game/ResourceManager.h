#pragma once

class Texture;
class Sprite;
class Flipbook;
class Tilemap;

class ResourceManager
{
public:
	static ResourceManager* GET_SINGLE()
	{
		static ResourceManager instance;
		return &instance;
	}
	
private:
	ResourceManager() {}
	~ResourceManager() {}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

public:
	void Init(HWND hwnd, fs::path resourcePath) 
	{
		_hwnd = hwnd;
		_resourcePath = resourcePath;
	};

	const fs::path& GetResourcePath() { return _resourcePath; }

	shared_ptr<Texture> GetTexture(const wstring& key) { return _textures[key]; }
	shared_ptr<Texture> LoadTexture(const wstring& key, const wstring& path, unsigned __int32 transparent = RGB(255, 174, 201));

	shared_ptr<Sprite> GetSprite(const wstring& key) { return _sprites[key]; }
	shared_ptr<Sprite> CreateSprite(const wstring& key, shared_ptr<Texture> texture, __int32 x = 0, __int32 y = 0, __int32 cx = 0, __int32 cy = 0);

	shared_ptr<Flipbook> GetFlipbook(const wstring& key) { return _flipbooks[key]; }
	shared_ptr<Flipbook> CreateFlipbook(const wstring& key);

	shared_ptr<Tilemap> GetTilemap(const wstring& key) { return _tilemaps[key]; }
	shared_ptr<Tilemap> CreateTilemap(const wstring& key);
	void SaveTilemap(const wstring& key, const wstring& path);
	shared_ptr<Tilemap> LoadTilemap(const wstring& key, const wstring& path);

private:
	HWND _hwnd = nullptr;
	fs::path _resourcePath = {};

	unordered_map<wstring, shared_ptr<Texture>> _textures;
	unordered_map<wstring, shared_ptr<Sprite>> _sprites;
	unordered_map<wstring, shared_ptr<Flipbook>> _flipbooks;
	unordered_map<wstring, shared_ptr<Tilemap>> _tilemaps;

};

