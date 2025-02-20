#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "InputManager.h"


TilemapActor::TilemapActor()
{

}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();

	//TickPicking();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tilemap == nullptr)
		return;

	if (_showDebug == false)
		return;

	const Vec2Int mapSize = _tilemap->GetMapSize();
	const __int32 tileSize = _tilemap->GetTileSize();

	vector<vector<Tile>>& tiles = _tilemap->GetTiles();

	shared_ptr<Sprite> spriteO = ResourceManager::GET_SINGLE()->GetSprite(L"TileO");
	shared_ptr<Sprite> spriteX = ResourceManager::GET_SINGLE()->GetSprite(L"TileX");
	Vec2Int size = spriteO->GetSize();
	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();

	// 컬링 : 보여야 할 애들만 보여주기
	__int32 leftX = ((__int32)cameraPos.x - GWinSizeX / 2);
	__int32 leftY = ((__int32)cameraPos.y - GWinSizeY / 2);
	__int32 rightX = ((__int32)cameraPos.x + GWinSizeX / 2);
	__int32 rightY = ((__int32)cameraPos.y + GWinSizeY / 2);

	__int32 startX = (leftX - _pos.x) / TILE_SIZEX;
	__int32 startY = (leftY - _pos.y) / TILE_SIZEY;
	__int32 endX = (rightX - _pos.x) / TILE_SIZEX;
	__int32 endY = (rightY - _pos.y) / TILE_SIZEY;

	for (__int32 y = startY; y <= endY; y++)
	{
		for (__int32 x = startX; x <= endX; x++)
		{
			if (x < 0 || x >= mapSize.x)
				continue;
			if (y < 0 || y >= mapSize.y)
				continue;
			// 왼쪽 상단 모서리를 기준으로 맞추자
			switch (tiles[y][x].value)
			{
			case 0:
			{
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((__int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * TILE_SIZEY - ((__int32)cameraPos.y - GWinSizeY / 2),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent());
			}
			break;
			case 1:
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((__int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * TILE_SIZEY - ((__int32)cameraPos.y - GWinSizeY / 2),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent());
				break;
			}
		}
	}

}

void TilemapActor::TickPicking()
{
	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::LEFT_MOUSE))
	{
		Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();
		__int32 screenX = cameraPos.x - GWinSizeX / 2;
		__int32 screenY = cameraPos.y - GWinSizeY / 2;

		POINT mousePos = InputManager::GET_SINGLE()->GetMousePos();
		__int32 posX = mousePos.x + screenX;
		__int32 posY = mousePos.y + screenY;

		__int32 x = posX / TILE_SIZEX;
		__int32 y = posY / TILE_SIZEY;

		auto tile = _tilemap->GetTileAt({ x, y });
		if (tile->value = 0)
		{
			tile->value = 1;
		}

	}

}
