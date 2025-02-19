#pragma once

#include "ResourceBase.h"

class Texture;

class Sprite : public ResourceBase
{
public:
	Sprite(shared_ptr<Texture> texture, __int32 x, __int32 y, __int32 cx, __int32 cy);
	virtual ~Sprite();

public:
	HDC GetDC();
	__int32 GetTransparent();
	Vec2Int GetPos() { return Vec2Int(_x, _y); }
	Vec2Int GetSize() { return Vec2Int(_cx, _cy); }

private:
	shared_ptr<Texture> _texture = {};
	__int32 _x = 0;
	__int32 _y = 0;
	__int32 _cx = 0;
	__int32 _cy = 0;
};

