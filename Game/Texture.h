#pragma once

#include "ResourceBase.h"

class Texture : public ResourceBase, public std::enable_shared_from_this<Texture>
{
public:
	Texture();
	virtual ~Texture();

public:
	shared_ptr<Texture> LoadBMP(HWND hwnd, const wstring& path);
	HDC GetDC() const { return _hdc; }

	void SetSize(const Vec2Int& size) { _size = size; }
	Vec2Int GetSize() const { return _size; }
	
	void SetTransparent(const unsigned __int32 transparent) { _transparent = transparent; }
	unsigned __int32 GetTransparent() const { return _transparent; }

private:
	HDC _hdc = {};
	HBITMAP _bitmap = {};
	Vec2Int _size = {};
	unsigned __int32 _transparent = RGB(255, 174, 201);
};

