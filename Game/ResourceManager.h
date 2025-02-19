#pragma once

class Texture;
class Sprite;

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
	void Init(HWND hwnd, fs::path resourcePath);
	void Clear();

	const fs::path& GetResourcePath() { return _resourcePath; }

	shared_ptr<Texture> GetTexture(const wstring& key) { return _textures[key]; }
	shared_ptr<Texture> LoadTexture(const wstring& key, const wstring& path, unsigned __int32 transparent = RGB(255, 0, 255));

	shared_ptr<Sprite> GetSprite(const wstring& key) { return _sprites[key]; }
	shared_ptr<Sprite> CreateSprite(const wstring& key, shared_ptr<Texture> texture, __int32 x = 0, __int32 y = 0, __int32 cx = 0, __int32 cy = 0);

private:
	HWND _hwnd;
	fs::path _resourcePath;

	unordered_map<wstring, shared_ptr<Texture>> _textures;
	unordered_map<wstring, shared_ptr<Sprite>> _sprites;
};

