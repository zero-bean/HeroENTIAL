#include "pch.h"
#include "Minimap.h"
#include "Tilemap.h"
#include "Player.h"
#include "Sprite.h"

Minimap::Minimap()
{
	_cover = ResourceManager::GET_SINGLE()->GetSprite(L"Banner_Minimap");
}

Minimap::~Minimap()
{
}

void Minimap::BeginPlay()
{
	Super::BeginPlay();


}

void Minimap::TickComponent()
{
	Super::TickComponent();


}

void Minimap::Render(HDC hdc)
{
	shared_ptr<Player> player = dynamic_pointer_cast<Player>(GetOwner());
	if (!player || !_tilemap)
		return;
	
	Super::Render(hdc);

	const int startX = GWinSizeX - GMinimapSizeX - 10;
	const int startY = 5;
	const Vec2Int center = player->GetCellPos();

	::BitBlt(hdc,
		startX - 5,
		0,
		180,
		180,
		_cover->GetDC(),
		_cover->GetPos().x,
		_cover->GetPos().y,
		SRCCOPY);

	for (int dy = -_visibleRange; dy <= _visibleRange; ++dy)
	{
		for (int dx = -_visibleRange; dx <= _visibleRange; ++dx)
		{
			const Vec2Int tilePos = { center.x + dx , center.y + dy };
			if (!_tilemap->IsPosInRange(tilePos))
				continue;

			const Tile& tile = _tilemap->GetTileAt(tilePos);
			COLORREF color;

			int localX = dx + _visibleRange;
			int localY = dy + _visibleRange;

			RECT rect;
			rect.left = startX + localX * _tileSize;
			rect.top = startY + localY * _tileSize;
			rect.right = rect.left + _tileSize;
			rect.bottom = rect.top + _tileSize;

			if (GetColorByTileType(tile.type, color))
			{
				HBRUSH brush = CreateSolidBrush(color);
				FillRect(hdc, &rect, brush);
				DeleteObject(brush);
			}
		}
	}
}

bool Minimap::GetColorByTileType(TILE_TYPE type, COLORREF& outColor)
{
	switch (type)
	{
	case TILE_TYPE::EMPTY:
		outColor = RGB(30, 30, 30);
		return true;
	case TILE_TYPE::WALL:
		outColor = RGB(100, 100, 100);
		return false;
	case TILE_TYPE::OBJECT:
		outColor = RGB(60, 60, 60);
		return true;
	case TILE_TYPE::PLAYER:
		outColor = RGB(255, 0, 0);
		return true;
	case TILE_TYPE::MONSTER:
		outColor = RGB(255, 100, 100);
		return true;
	case TILE_TYPE::PROJECTILE:
		outColor = RGB(255, 255, 0);
		return true;
	case TILE_TYPE::NPC:
		outColor = RGB(0, 255, 255);
		return true;
	case TILE_TYPE::ITEM:
		outColor = RGB(0, 255, 0);
		return true;
	default:
		return false;
	}
}

