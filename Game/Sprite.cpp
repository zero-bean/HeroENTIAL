#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(weak_ptr<Texture> texture, __int32 x, __int32 y, __int32 cx, __int32 cy)
	: _texture(texture), _x(x), _y(y), _cx(cx), _cy(cy)
{

}

Sprite::~Sprite()
{

}

HDC Sprite::GetDC() const
{
	if (auto tmp = _texture.lock())
		return tmp->GetDC();

	return nullptr;
}

__int32 Sprite::GetTransparent() const
{
	if (auto tmp = _texture.lock())
		return tmp->GetTransparent();

	return NULL;
}
