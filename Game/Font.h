#pragma once
#include "ResourceBase.h"

class Font : public ResourceBase
{
	using Super = ResourceBase;
public:
	Font(const wstring& fontName, int size);
	~Font();

public:
	HFONT GetHandle() const { return _hFont; }

private:
	HFONT _hFont = nullptr;
};

