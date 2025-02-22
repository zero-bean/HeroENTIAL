#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "FlipbookActor.h"
#include "TilemapActor.h"


DevScene::DevScene()
{

}

DevScene::~DevScene()
{

}

void DevScene::Init()
{
	// TODO
	ResourceManager::GET_SINGLE()->LoadTexture(L"Coin", L"Sprite\\Item\\coin_gold.bmp");
	ResourceManager::GET_SINGLE()->LoadTexture(L"Stage-T01", L"Sprite\\Map\\test-01.bmp");

	ResourceManager::GET_SINGLE()->CreateSprite(L"Coin", ResourceManager::GET_SINGLE()->GetTexture(L"Coin"), 0, 0, 128, 16);
	ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-T01", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-T01"));

	LoadMap();

	{
	}

	Super::Init();
}

void DevScene::Update()
{
	Super::Update();

	// TODO
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

	// TODO
}

void DevScene::LoadMap()
{
	shared_ptr<Sprite> sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Stage-T01");

	shared_ptr<SpriteActor> background = make_shared<SpriteActor>();
	background->SetSprite(sprite);
	background->SetLayer(LAYER_BACKGROUND);
	const Vec2Int size = sprite->GetSize();
	background->SetPos(Vec2(size.x / 2, size.y / 2));

	AddActor(background);
}

bool DevScene::CanGo(Vec2Int cellPos)
{
	if (_tilemapActor == nullptr)
		return false;

	shared_ptr<Tilemap> tileMap = _tilemapActor->GetTilemap();
	if (tileMap == nullptr)
		return false;

	auto tile = tileMap->GetTileAt(cellPos);
	return tile->value != 1;
}

Vec2 DevScene::ConvertPos(Vec2Int cellPos)
{
	Vec2 ret = {};

	if (_tilemapActor == nullptr)
		return ret;

	shared_ptr<Tilemap> tileMap = _tilemapActor->GetTilemap();
	if (tileMap == nullptr)
		return ret;

	__int32 size = tileMap->GetTileSize();
	Vec2 pos = _tilemapActor->GetPos();

	ret.x = pos.x + cellPos.x * size + (size / 2);
	ret.y = pos.y + cellPos.y * size + (size / 2);

	return ret;
}
