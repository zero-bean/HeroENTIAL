#include "pch.h"
#include "Stage1.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "TilemapActor.h"
#include "SpriteActor.h"
#include "Player.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "Inventory.h"
#include "CameraComponent.h"
#include "BoxCollider.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::Init()
{
	ResourceManager::GET_SINGLE()->LoadFont(L"DungeonFont", L"Font\\DungeonFont.ttf", L"DungeonFont", 24);
	LoadMap();
	LoadTileMap();
	shared_ptr<Player> player = LoadPlayer();

	Super::Init();
}

void Stage1::Update()
{
	Super::Update();

	// TODO
	float deltaTime = TimeManager::GET_SINGLE()->GetDeltaTime();
}

void Stage1::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Stage1::LoadMap()
{
	ResourceManager::GET_SINGLE()->LoadTexture(L"Stage-01", L"Sprite\\Map\\Stage-01.bmp");
	ResourceManager::GET_SINGLE()->CreateSprite(L"Stage-01", ResourceManager::GET_SINGLE()->GetTexture(L"Stage-01"));
	shared_ptr<Sprite> sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Stage-01");
	shared_ptr<SpriteActor> background = make_shared<SpriteActor>();
	background->SetSprite(sprite);
	background->SetLayer(LAYER_BACKGROUND);
	const Vec2Int size = sprite->GetSize();
	background->SetPos(Vec2(size.x / 2, size.y / 2));
	AddActor(background);
}

void Stage1::LoadTileMap()
{
	// TilemapActor - TickPicking¿¡ »ç¿ë
	ResourceManager::GET_SINGLE()->LoadTexture(L"Tile_CanMove", L"Sprite\\Map\\Tile-CanMove.bmp");
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileO", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 0, 0, 16, 16);
	ResourceManager::GET_SINGLE()->CreateSprite(L"TileX", ResourceManager::GET_SINGLE()->GetTexture(L"Tile_CanMove"), 16, 0, 32, 16);

	shared_ptr<TilemapActor> actor = make_shared<TilemapActor>();
	AddActor(actor);

	_tilemapActor = actor;
	{
		shared_ptr<Tilemap> tilemap = ResourceManager::GET_SINGLE()->CreateTilemap(L"Tilemap_STAGE1");
		tilemap->SetMapSize({ 92, 124 });
		tilemap->SetTileSize(16);
		tilemap->SetScale(3);

		ResourceManager::GET_SINGLE()->LoadTilemap(L"Tilemap_STAGE1", L"Tilemap\\Tilemap_STAGE1.txt");

		_tilemapActor->SetTilemap(tilemap);
		_tilemapActor->SetShowDebug(true);
	}
}

shared_ptr<Player> Stage1::LoadPlayer()
{
	Super::LoadPlayer();

	shared_ptr<Player> player = make_shared<Player>();
	player->SetCellPos({ 56,120 }, true);
	AddActor(player);

	shared_ptr<CameraComponent> camera = make_shared<CameraComponent>();
	camera->SetBackGroundRange({ 1472, 1984 });
	player->AddComponent(camera);

	shared_ptr<BoxCollider> collider = make_shared<BoxCollider>();
	collider->SetCollisionLayer(COLLISION_LAYER_TYPE::CLT_PLAYER);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_WALL);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_NPC);
	collider->AddCollisionFlagLayer(COLLISION_LAYER_TYPE::CLT_OBJECT);
	collider->SetSize({ 50, 50 });
	CollisionManager::GET_SINGLE()->AddCollider(collider);
	player->AddComponent(collider);

	shared_ptr<Inventory> inventory = make_shared<Inventory>();
	player->AddComponent(inventory);

	return player;
}

void Stage1::LoadMonster()
{
}
