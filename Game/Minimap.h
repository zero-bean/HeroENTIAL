#pragma once
#include "Component.h"

class Tilemap;
class Sprite;

class Minimap : public Component
{
	using Super = Component;
public:
	Minimap();
	virtual ~Minimap();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

public:
	void SetTilemap(shared_ptr<Tilemap> tilemap) { _tilemap = tilemap; }

private:
	bool GetColorByTileType(TILE_TYPE type, COLORREF& outColor);

private:
	shared_ptr<Tilemap> _tilemap = nullptr;
	shared_ptr<Sprite> _cover = nullptr;
	const __int32 _visibleRange = 8;
	const __int32 _tileSize = 8;
};

