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

	int GetSize() const { return _size; }
	
private:
	HFONT _hFont = nullptr;
	int _size = 0;
};

