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
	const __int32 scaledSize = _tilemap->GetTileSize() * _tilemap->GetScale();

	vector<vector<Tile>> tiles = _tilemap->GetTiles();

	shared_ptr<Sprite> spriteO = ResourceManager::GET_SINGLE()->GetSprite(L"TileO");
	shared_ptr<Sprite> spriteX = ResourceManager::GET_SINGLE()->GetSprite(L"TileX");
	Vec2Int size = spriteO->GetSize();
	Vec2 cameraPos = SceneManager::GET_SINGLE()->GetCameraPos();

	// 컬링 : 보여야 할 애들만 보여주기
	__int32 leftX = ((__int32)cameraPos.x - GWinSizeX / 2);
	__int32 leftY = ((__int32)cameraPos.y - GWinSizeY / 2);
	__int32 rightX = ((__int32)cameraPos.x + GWinSizeX / 2);
	__int32 rightY = ((__int32)cameraPos.y + GWinSizeY / 2);

	__int32 startX = static_cast<__int32>((leftX - _pos.x) / scaledSize);
	__int32 startY = static_cast<__int32>((leftY - _pos.y) / scaledSize);
	__int32 endX = static_cast<__int32>((rightX - _pos.x) / scaledSize);
	__int32 endY = static_cast<__int32>((rightY - _pos.y) / scaledSize);

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
					static_cast<int>(_pos.x + x * scaledSize - ((__int32)cameraPos.x - GWinSizeX / 2)),
					static_cast<int>(_pos.y + y * scaledSize - ((__int32)cameraPos.y - GWinSizeY / 2)),
					scaledSize,
					scaledSize,
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					tileSize,
					tileSize,
					spriteO->GetTransparent());
			}
			break;
			case 1:
				::TransparentBlt(hdc,
					static_cast<int>(_pos.x + x * scaledSize - ((__int32)cameraPos.x - GWinSizeX / 2)),
					static_cast<int>(_pos.y + y * scaledSize - ((__int32)cameraPos.y - GWinSizeY / 2)),
					scaledSize,
					scaledSize,
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					tileSize,
					tileSize,
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
		__int32 screenX = static_cast<__int32>(cameraPos.x - static_cast<float>(GWinSizeX / 2));
		__int32 screenY = static_cast<__int32>(cameraPos.y - static_cast<float>(GWinSizeY / 2));

		POINT mousePos = InputManager::GET_SINGLE()->GetMousePos();
		__int32 posX = mousePos.x + screenX;
		__int32 posY = mousePos.y + screenY;

		__int32 tileX = _tilemap->GetTileSize() * _tilemap->GetScale();
		__int32 tileY = _tilemap->GetTileSize() * _tilemap->GetScale();

		__int32 x = posX / tileX;
		__int32 y = posY / tileY;

		Tile& tile = _tilemap->GetTileAt({ x, y });

		if (tile.value == 0)
		{
			tile.value = 1;
		}
		else
		{
			tile.value = 0;
		}

	}

}
