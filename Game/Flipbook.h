#pragma once

#include "ResourceBase.h"

class Texture;

struct FlipbookInfo
{
	shared_ptr<Texture> texture = nullptr;
	wstring name = {};
	Vec2Int size = {};
	__int32 start = 0;
	__int32 end = 0;
	__int32 line = 0;
	float duration = 1.f;
	bool loop = true;
};

class Flipbook : public ResourceBase
{
public:
	Flipbook();
	virtual ~Flipbook();

public:
	void SetInfo(const FlipbookInfo& info) { _info = info; }
	const FlipbookInfo& GetInfo() { return _info; }

private:
	FlipbookInfo _info;
};

